var express = require('express');
var router = express.Router();
var auth = require('basic-auth');

/* GET home page. */
router.get('/', function(req, res, next) {
  const auth = {login: 'LOGIN_HERE', password: 'PASSWORD_HERE'}

  const b64auth = (req.headers.authorization || '').split(' ')[1] || ''
  const [login, password] = new Buffer(b64auth, 'base64').toString().split(':')

  // Verify login and password are set and correct
  if (!login || !password || login !== auth.login || password !== auth.password) {
    res.set('WWW-Authenticate', 'Basic realm="nope"') 
    res.status(401).send('upside down')
    return
  }

  res.render('index', { title: 'Stranger Objects' });
});

module.exports = router;
