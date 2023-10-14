import { getDatabase } from 'firebase-admin/database';
import { getTimeDifference } from '../utils/time';
import DeviceStatus from 'src/models/DeviceStatus';
import { sendOfflineNotification } from './NotificationService';

export const updateDeviceStatus = async (status: boolean) => {
  try {
    const ref = getDatabase().ref('deviceStatus');

    const deviceStatus: DeviceStatus = {
      status,
      timestamp: Date.now(),
    };

    await ref.set(deviceStatus);

    console.log(`Device status updated - ${new Date().toString()}`);
  } catch (err) {
    console.error('Error updating device status', err);
    throw err;
  }
};

export const checkDeviceStatus = async () => {
  try {
    const ref = getDatabase().ref('deviceStatus');
    const data = await ref.once('value');

    const notifyAndReport = async () => {
      sendOfflineNotification();
      await updateDeviceStatus(false);
    };

    if (data.exists()) {
      const status: DeviceStatus = data.val();
      const lastUpdate = new Date(status.timestamp);
      const timeDifference = getTimeDifference(lastUpdate, new Date());

      if (timeDifference > Number(process.env.NOTIFICATIONS_INTERVAL_MINUTES)) {
        await notifyAndReport();
      }
    } else {
      await notifyAndReport();
    }
    console.log(`Device status checked - ${new Date().toString()}`);
  } catch (err) {
    console.error('Error checking device status', err);
  }
};
