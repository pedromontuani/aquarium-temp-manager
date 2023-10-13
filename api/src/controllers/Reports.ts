import { Router, Request, Response, RequestHandler } from 'express';
import removeHeaders from '../middlewares/removeHeaders';
import ReportRequest from '../types/ReportRequest';
import { handleTemperatureReport } from '../services/ReportsService';
import { updateParameters } from '../services/ParametersService';

const router: Router = Router();

router.post(
  '/',
  removeHeaders,
  async (req: Request<any, any, ReportRequest>, res: Response) => {
    try {
      await handleTemperatureReport(req.body);
      await updateParameters(req.body);
      res.send();
    } catch (err) {
      console.log(err);
      res.status(500).send(); 
    }
  }
);

export default router;
