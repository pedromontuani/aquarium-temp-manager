import { getDatabase } from 'firebase-admin/database';

import ReportRequest from '../types/ReportRequest';
import Parameters from '../models/Parameters';
import errorNotify from '../utils/errorNotify';
import { getCoolerMode } from '../utils/coolerMode';

export const updateParameters = async (report: ReportRequest) => {
  const parameters: Parameters = {
    water: {
      temperature: report.temp.aq,
      // TODO: implemet other parameters
    },
    ambient: {
      temperature: report.temp.ext,
      // TODO: implemet other parameters
    },
    cooler: {
      mode: getCoolerMode(report.md),
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

  try {
    await getDatabase().ref('parameters').set(parameters);
    console.log('Parameters updated');
  } catch (err) {
    errorNotify('Error updating parameters', err);
  }
};
