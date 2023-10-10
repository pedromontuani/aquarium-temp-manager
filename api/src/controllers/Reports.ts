import { Router, Request } from 'express';
import removeHeaders from '../middlewares/removeHeaders';

const router: Router = Router();

router.post('/', removeHeaders, async (req: Request<{ test: string }>, res) => {
    console.log(req.body);
    res.send();
});


export default router;