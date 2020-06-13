var createError = require('http-errors');
import express from 'express';
var expressSession = require('express-session');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var userAuthRouter = require('./routes/userAuth');
let cartRouter = require('./routes/carts');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(expressSession({
    secret: 'foobarbaz',
    resave: false,
    saveUninitialized: false
}))

app.use(express.static(path.join(__dirname, 'public')));
app.use('/userAuth', userAuthRouter);
app.use('/carts', cartRouter);

export default app;
