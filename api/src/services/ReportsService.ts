import { getDatabase } from 'firebase-admin/database';

import ReportRequest from '../types/ReportRequest';
import Report from '../models/Report';
import Notification from '../models/Notification';
import { getTimeDifference } from '../utils/time';
import { sendTempNotification } from './NotificationService';

const saveReport = (report: ReportRequest) =>
  new Promise<String>((resolve, reject) => {
    const newReport: Report = {
      aquariumTemp: report.aqTemp,
      externalTemp: report.extTemp,
      cooler: {
        lowEnergy: {
          state: report.leCooler.state,
          power: report.leCooler.power,
        },
        highEnergy: {
          state: report.heCooler.state,
          power: report.heCooler.power,
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
  } catch (err) {
    console.error('Error saving report', err);
    throw err;
  }

  if (Number(report.aqTemp) > Number(process.env.TEMPERATURE_LIMIT)) {
    await handleNotification(uid, report.aqTemp);
  }
};
