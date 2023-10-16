export enum Mode {IDLE, COOLING};

export type ModeLabels = 'IDLE' | 'COOLING';

export default interface ReportRequest {
  temp: {
    aq: number;
    ext: number;
  };
  he: {
    on: boolean;
    pw: number;
  };
  le: {
    on: boolean;
    pw: number;
  };
  md: Mode;
}
