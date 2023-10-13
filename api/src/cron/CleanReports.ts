import Cron from 'node-cron';
import { deleteOldReports } from '../services/ReportsService';

export default () => {
    Cron.schedule('0 2 * * *', deleteOldReports).start();
}