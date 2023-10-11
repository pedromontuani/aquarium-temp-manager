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
  lowEnergy: {
    state: boolean;
    power: number;
  };
  highEnergy: {
    state: boolean;
    power: number;
  };
}

export default interface Parameters {
    water: WaterParameters;
    ambient: AmbientParameters;
    cooler: Cooler;
    timestamp: number;
}
