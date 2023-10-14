import Cron from 'node-cron';
import { deleteOldReports } from '../services/ReportsService';

export default () => {
  const hour = process.env.DELETE_REPORTS_JOB_HOUR;

  return Cron.schedule(`0 ${hour} * * *`, deleteOldReports);
};
