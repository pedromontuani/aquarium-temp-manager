import { Mode, ModeLabels } from "../types/ReportRequest";

export const getCoolerMode = (mode: Mode): ModeLabels => {
  if (mode === Mode.IDLE) {
    return 'IDLE';
  }

  return 'COOLING';
};
