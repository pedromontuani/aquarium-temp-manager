import { ModeLabels } from "../types/ReportRequest";

export default interface Report {
    aquariumTemp: number;
    externalTemp: number;
    mode: ModeLabels;
    cooler: {
        lowEnergy: {
            state: boolean;
            power: number;
        },
        highEnergy: {
            state: boolean;
            power: number;
        },
    },
    timestamp: number;
}