"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.handleTemperatureReport = void 0;
const database_1 = require("firebase-admin/database");
const time_1 = require("../utils/time");
const NotificationService_1 = require("./NotificationService");
const saveReport = (report) => new Promise((resolve, reject) => {
    const newReport = {
        aquariumTemp: report.temp.aq,
        externalTemp: report.temp.ext,
        cooler: {
            lowEnergy: {
                state: report.le.on,
                power: report.le.pw,
            },
            highEnergy: {
                state: report.he.on,
                power: report.he.pw,
            },
        },
        timestamp: Date.now(),
    };
    const key = (0, database_1.getDatabase)()
        .ref('reports')
        .push(newReport, (error) => {
        if (error) {
            reject(error);
        }
    }).key;
    if (key) {
        resolve(key);
    }
    else {
        reject();
    }
});
const handleNotification = (reportUid, temperature) => __awaiter(void 0, void 0, void 0, function* () {
    const ref = (0, database_1.getDatabase)().ref('notifications').child('lastNotification');
    const data = yield ref.once('value');
    if (data.exists()) {
        const notification = data.val();
        const sentAt = new Date(notification.sentAt);
        const timeDifference = (0, time_1.getTimeDifference)(sentAt, new Date());
        if (timeDifference < Number(process.env.NOTIFICATIONS_INTERVAL_MINUTES)) {
            return;
        }
    }
    yield (0, NotificationService_1.sendTempNotification)(temperature);
    const newNotification = {
        sentAt: Date.now(),
        reportUid,
    };
    return ref.set(newNotification);
});
const handleTemperatureReport = (report) => __awaiter(void 0, void 0, void 0, function* () {
    let uid;
    try {
        uid = yield saveReport(report);
        console.log(`Report saved - ${new Date().toString()}`);
    }
    catch (err) {
        console.error('Error saving report', err);
        throw err;
    }
    if (Number(report.temp.aq) > Number(process.env.TEMPERATURE_LIMIT)) {
        yield handleNotification(uid, report.temp.aq);
    }
});
exports.handleTemperatureReport = handleTemperatureReport;
