import 'express-async-errors';
import express from 'express';
import cors from 'cors';
import morgan from 'morgan';
import helmet from 'helmet';

import admin, { ServiceAccount } from 'firebase-admin';

import serviceAccount from './config/firebase-admin-credentials.json';
import { AquariumManager, Reports } from './controllers';

import CronJobs from './cron';

export default () => {
  admin.initializeApp({
    credential: admin.credential.cert(serviceAccount as ServiceAccount),
    databaseURL: process.env.DATABASE_URL,
  });

  const app = express();

  app.use(morgan('tiny'));
  app.use(cors());
  app.use(helmet());
  app.use(express.json());

  app.use('/reports', Reports);
  app.use('/aquarium', AquariumManager);

  CronJobs();

  return app;
};
