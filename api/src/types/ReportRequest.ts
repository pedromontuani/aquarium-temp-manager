export default interface ReportRequest {
    aqTemp: number;
    extTemp: number;
    heCooler: {
        state: boolean;
        power: number;
    },
    leCooler: {
        state: boolean;
        power: number;
    },
}