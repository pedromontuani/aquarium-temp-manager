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
exports.updateParameters = void 0;
const database_1 = require("firebase-admin/database");
const updateParameters = (report) => __awaiter(void 0, void 0, void 0, function* () {
    const parameters = {
        water: {
            temperature: report.temp.aq,
            // TODO: implemet other parameters
        },
        ambient: {
            temperature: report.temp.ext,
            // TODO: implemet other parameters
        },
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
    try {
        yield (0, database_1.getDatabase)().ref('parameters').set(parameters);
        console.log('Parameters updated');
    }
    catch (err) {
        console.error('Error updating parameters', err);
    }
});
exports.updateParameters = updateParameters;
