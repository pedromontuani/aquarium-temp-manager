"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.default = (_, res, next) => {
    res.removeHeader("x-powered-by");
    res.removeHeader("set-cookie");
    res.removeHeader("Date");
    res.removeHeader("Connection");
    res.removeHeader('Transfer-Encoding');
    res.removeHeader('X-Powered-By');
    next();
};
