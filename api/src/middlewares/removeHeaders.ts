import { Response, Request, NextFunction } from 'express';

export default (_: Request, res: Response, next: NextFunction) =>  {
    res.removeHeader("x-powered-by");
    res.removeHeader("set-cookie");
    res.removeHeader("Date");
    res.removeHeader("Connection");
    res.removeHeader('Transfer-Encoding');
    res.removeHeader('X-Powered-By');
    next();
}