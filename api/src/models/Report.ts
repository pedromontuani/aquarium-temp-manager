import { ModeLabels } from '../types/ReportRequest';

export default interface Report {
  aquariumTemp: number;
  externalTemp: number;
  mode: ModeLabels;
  cooler: {
    lowEnergy: {
      state: boolean;
    };
    highEnergy: {
      state: boolean;
    };
  };
  timestamp: number;
}
