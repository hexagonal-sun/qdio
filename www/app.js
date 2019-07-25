var createError = require('http-errors');
var express = require('express');
var expressSession = require('express-session');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var userAuthRouter = require('./routes/userAuth');
var dashboardRouter = require('./routes/dashboard');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'pug');

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
app.use('/jquery', express.static(path.join(__dirname, 'node_modules',
                                            'jquery', 'dist')));

app.use('/bootstrap', express.static(path.join(__dirname, 'node_modules',
                                               'bootstrap', 'dist')));

app.use('/sha3', express.static(path.join(__dirname, 'node_modules',
                                          'js-sha3', 'src')));

app.use('/feather', express.static(path.join(__dirname, 'node_modules',
                                             'feather-icons', 'dist')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/userAuth', userAuthRouter);
app.use('/dashboard', dashboardRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
