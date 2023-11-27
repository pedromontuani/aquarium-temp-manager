import { ModeLabels } from '../types/ReportRequest';

export interface WaterParameters {
  temperature: number;
  ph?: number;
  turbidity?: number;
  ammonia?: number;
}

export interface AmbientParameters {
  temperature: number;
  humidity?: number;
  light?: number;
}

export interface Cooler {
  mode: ModeLabels;
  lowEnergy: {
    state: boolean;
  };
  highEnergy: {
    state: boolean;
  };
}

export default interface Parameters {
  water: WaterParameters;
  ambient: AmbientParameters;
  cooler: Cooler;
  timestamp: number;
}
