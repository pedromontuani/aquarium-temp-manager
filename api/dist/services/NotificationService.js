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
exports.sendTempNotification = void 0;
const messaging_1 = require("firebase-admin/messaging");
const TEMPERATURE_TOPIC = 'temperature';
const sendTempNotification = (currentTemp) => __awaiter(void 0, void 0, void 0, function* () {
    try {
        yield (0, messaging_1.getMessaging)().sendToTopic(TEMPERATURE_TOPIC, {
            notification: {
                title: 'Temperature Alert',
                body: `The current temperature is ${currentTemp}°C`,
            },
        });
        console.log(`Notification sent - ${new Date().toString()}`);
    }
    catch (err) {
        console.error('Error sending notification', err);
        throw err;
    }
});
exports.sendTempNotification = sendTempNotification;
