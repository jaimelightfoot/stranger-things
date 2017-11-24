const express = require('express')
const app = express()
var path = require('path');

var bodyParser = require('body-parser')
app.use( bodyParser.json() );       // to support JSON-encoded bodies
app.use(bodyParser.urlencoded({     // to support URL-encoded bodies
  extended: true
}));

app.set('views', __dirname);
app.set('view engine', 'hbs');

app.use('/', index);
