import { Router, Request, Response } from 'express';
import { Client } from 'pg';

const router = Router();

router.get('/getCartWalls', async (_req : Request, res : Response) => {
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

router.get('/getCarts/:cartWallId', async (req : Request, res : Response) => {
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

router.get('/themes', async (_req : Request, res : Response) => {
    const client = new Client({
        database: 'qdio'
    });

    try {
        await client.connect();

        const query = 'SELECT * FROM cart_theme';
        const qRes = await client.query(query);

        res.send(qRes.rows);

        await client.end();
    } catch (e) {
        console.log(e);
        return res.status(500).send(e);
    }
});

export default router;
