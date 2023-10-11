import {getDatabase} from 'firebase-admin/database';

import ReportRequest from "../types/ReportRequest";
import Parameters from '../models/Parameters';

export const updateParameters = async (report: ReportRequest) => {
    const parameters: Parameters = {
        water: {
            temperature: report.aqTemp,
            // TODO: implemet other parameters
        },
        ambient: {
            temperature: report.extTemp,
            // TODO: implemet other parameters
        },
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
        
    }

    try {
        await getDatabase().ref('parameters').set(parameters);
        console.log('Parameters updated');
    } catch(err) {
        console.error('Error updating parameters', err);
    }
}