import Cron from 'node-cron';
import { checkDeviceStatus } from 'src/services/DeviceStatus';

export default () => {
    const minutes = process.env.DEVICE_STATUS_CHECK_INTERVAL_MINUTES;

    return Cron.schedule(`*/${minutes} * * * *`, checkDeviceStatus);
}