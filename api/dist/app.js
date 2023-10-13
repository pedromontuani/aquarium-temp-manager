"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
require("express-async-errors");
const express_1 = __importDefault(require("express"));
const cors_1 = __importDefault(require("cors"));
const morgan_1 = __importDefault(require("morgan"));
const helmet_1 = __importDefault(require("helmet"));
const firebase_admin_1 = __importDefault(require("firebase-admin"));
const firebase_admin_credentials_json_1 = __importDefault(require("./config/firebase-admin-credentials.json"));
const controllers_1 = require("./controllers");
exports.default = () => {
    firebase_admin_1.default.initializeApp({
        credential: firebase_admin_1.default.credential.cert(firebase_admin_credentials_json_1.default),
        databaseURL: process.env.DATABASE_URL,
    });
    const app = (0, express_1.default)();
    app.use((0, morgan_1.default)('tiny'));
    app.use((0, cors_1.default)());
    app.use((0, helmet_1.default)());
    app.use(express_1.default.json());
    app.use('/reports', controllers_1.Reports);
    app.use('/aquarium', controllers_1.AquariumManager);
    return app;
};
