var express = require('express');
var pg = require('pg');
var router = express.Router();

router.get('/getCartWalls', async (req, res, next) => {
    const { Client } = require('pg');
    const client = new Client({
        database: 'qdio'
    });

    try {
        await client.connect();

        const query = 'SELECT * FROM get_cartwalls_for_user($1)';
        const qRes = await client.query(query, [1]);

        res.send(qRes.rows);

        await client.end();
    } catch (e) {
        console.log(e);
        return res.status(500).send(e);
    }
});

router.get('/getCarts/:cartWallId', async (req, res, next) => {
    const { Client } = require('pg');
    const client = new Client({
        database: 'qdio'
    });

    try {
        await client.connect();

        const query = 'SELECT * FROM get_carts_for_cartwall($1)';
        const qRes = await client.query(query, [req.params.cartWallId]);

        res.send(qRes.rows);

        await client.end();
    } catch (e) {
        console.log(e);
        return res.status(500).send(e);
    }
});

module.exports = router;
