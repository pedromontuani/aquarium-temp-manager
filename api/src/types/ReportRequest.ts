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
}
