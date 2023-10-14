import { getDatabase } from 'firebase-admin/database';

import ReportRequest from '../types/ReportRequest';
import Report from '../models/Report';
import Notification from '../models/Notification';
import { getTimeDifference } from '../utils/time';
import { sendTempNotification } from './NotificationService';
import { updateDeviceStatus } from './DeviceStatus';

const saveReport = (report: ReportRequest) =>
  new Promise<String>((resolve, reject) => {
    const newReport: Report = {
      aquariumTemp: report.temp.aq,
      externalTemp: report.temp.ext,
      cooler: {
        lowEnergy: {
          state: report.le.on,
          power: report.le.pw,
        },
        highEnergy: {
          state: report.he.on,
          power: report.he.pw,
        },
      },
      timestamp: Date.now(),
    };

    const key = getDatabase()
      .ref('reports')
      .push(newReport, (error) => {
        if (error) {
          reject(error);
        }
      }).key;

    if (key) {
      resolve(key);
    } else {
      reject();
    }
  });

const handleNotification = async (reportUid: String, temperature: number) => {
  const ref = getDatabase().ref('notifications').child('lastNotification');
  const data = await ref.once('value');

  if (data.exists()) {
    const notification: Notification = data.val();
    const sentAt = new Date(notification.sentAt);
    const timeDifference = getTimeDifference(sentAt, new Date());

    if (timeDifference < Number(process.env.NOTIFICATIONS_INTERVAL_MINUTES)) {
      return;
    }
  }

  await sendTempNotification(temperature);

  const newNotification: Notification = {
    sentAt: Date.now(),
    reportUid,
  };

  return ref.set(newNotification);
};

export const handleTemperatureReport = async (report: ReportRequest) => {
  let uid: String;
  try {
    uid = await saveReport(report);
    console.log(`Report saved - ${new Date().toString()}`);
    await updateDeviceStatus(true).catch(() => null);
  } catch (err) {
    console.error('Error saving report', err);
    throw err;
  }

  if (Number(report.temp.aq) > Number(process.env.TEMPERATURE_LIMIT)) {
    await handleNotification(uid, report.temp.aq);
  }
};

export const deleteOldReports = async () => {
  try {
    const ref = getDatabase().ref('reports');

    const itemsToDelete = ref
      .orderByChild('timestamp')
      .endAt(
        Date.now() -
          Number(process.env.REPORTS_RETENTION_DAYS) * 24 * 60 * 60 * 1000
      );

    const data = await itemsToDelete.once('value');

    const updates: { [key: string]: null } = {};

    data.forEach((item) => {
      updates[`${item.key}`] = null;
    });

    await ref.update(updates);

    const numObjects = data.numChildren();

    console.log(`${numObjects} old reports deleted - ${new Date().toString()}`);
  } catch (err) {
    console.error('Error deleting old reports', err);
  }
};
