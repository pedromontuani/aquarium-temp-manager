import CheckDevicesStatus from "./CheckDevicesStatus";
import CleanReports from "./CleanReports"

export default () => {
    CleanReports().start();
    CheckDevicesStatus().start();
}