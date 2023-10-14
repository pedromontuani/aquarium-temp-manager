import { getMessaging } from 'firebase-admin/messaging';
import errorNotify from '../utils/errorNotify';

const TEMPERATURE_TOPIC = 'temperature';

const sendNotification = async (
  topic: string,
  title: string,
  message: string
) => {
  await getMessaging().sendToTopic(topic, {
    notification: {
      title: title,
      body: message,
    },
  });
};

export const sendTempNotification = async (currentTemp: number) => {
  try {
    await sendNotification(
      TEMPERATURE_TOPIC,
      'Temperature Alert',
      `The current temperature is ${currentTemp}°C`
    );
    console.log(`Notification sent - ${new Date().toString()}`);
  } catch (err) {
    errorNotify('Error sending notification', err);
    throw err;
  }
};

export const sendOfflineNotification = async () => {
    try {
        await sendNotification(
            TEMPERATURE_TOPIC,
            'Sensors are offline',
            `The sensors are offline. Please check the aquarium.`
        );
        console.log(`Notification sent - ${new Date().toString()}`);
    } catch(err) {
        errorNotify('Error sending notification', err);
        throw err;
    }
};