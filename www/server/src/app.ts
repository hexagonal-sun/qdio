import express from 'express';
import expressSession from 'express-session';
import path from 'path';
import logger from 'morgan';

import userAuthRouter from './routes/userAuth';
import cartRouter from './routes/carts';

let app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(expressSession({
    secret: 'foobarbaz',
    resave: false,
    saveUninitialized: false
}))

app.use(express.static(path.join(__dirname, 'public')));
app.use('/userAuth', userAuthRouter);
app.use('/carts', cartRouter);

export default app;
