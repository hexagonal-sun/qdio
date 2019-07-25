var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/home', (req, res, next) => {
    res.render('home', {
        cur: req.originalUrl
    });
});

module.exports = router;
