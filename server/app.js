var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var request = require('request');

var index = require('./routes/index');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'hbs');

app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', index);

app.post('/message', function(req, res) {
  if (!req.body.message) {
    res.error("oh no");
  }

  var headers = {
    'User-Agent':       'Super Agent/0.0.1',
    'Content-Type':     'application/application/json',
    'X-AIO-Key':        'REPLACE_WITH_AIO_KEY'
  }

  var options = {
    url: 'https://io.adafruit.com/api/v2/USERNAME_HERE/feeds/alph/data',
    method: 'POST',
    headers: headers,
    form: {'value': req.body.message.toLowerCase()}
  }

  request(options, function (error, response, body) {
    if (!error && response.statusCode == 200) {
        console.log(body)
    }
  })

  res.redirect('/');
});

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
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

app.listen(3000, () => console.log('Example app listening on port 3000!'))

module.exports = app;
