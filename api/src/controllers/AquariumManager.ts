import { Router } from 'express';
import removeHeaders from '../middlewares/removeHeaders';

const router: Router = Router();

router.get('/night-mode', removeHeaders, async (req, res) => {
    const currentDate = new Date();
    console.log(currentDate.getHours());
    if (currentDate.getHours() >= 18 || currentDate.getHours() <= 6) {
        res.send("true");
    } else {
        res.send("false");
    }
});


export default router;