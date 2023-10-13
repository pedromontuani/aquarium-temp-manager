"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.getTimeDifference = void 0;
const getTimeDifference = (x, y) => {
    let diff = (x.getTime() - y.getTime()) / 1000;
    diff /= 60;
    return Math.abs(Math.round(diff));
};
exports.getTimeDifference = getTimeDifference;
