var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
    if (req.session.uid)
    {
        return res.redirect('/dashboard/home/')
    }

    res.render('index');
});

module.exports = router;
