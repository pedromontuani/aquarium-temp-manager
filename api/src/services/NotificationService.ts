import {getMessaging} from 'firebase-admin/messaging'

const TEMPERATURE_TOPIC = 'temperature';

export const sendTempNotification = async (currentTemp: number) => {
    try {
        await getMessaging().sendToTopic(TEMPERATURE_TOPIC, {
            notification: {
                title: 'Temperature Alert',
                body: `The current temperature is ${currentTemp}°C`,
            },
        })
        console.log(`Notification sent - ${new Date().toString()}`);
    } catch (err) {
        console.error('Error sending notification', err);
        throw err;
    }
    
}