
export default interface Report {
    aquariumTemp: number;
    externalTemp: number;
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