import { Router, Request, Response } from 'express';
import { Client } from 'pg';

const router = Router();

router.post('/findUser', async (req : Request, res : Response) => {
    const client = new Client({
        database: 'qdio'
    });

    try {
        await client.connect();

        const query = 'SELECT * FROM find_user($1) AS f(user_id integer, salt varchar)';
        const qRes = await client.query(query, [req.body.username]);

        res.send(qRes.rows[0]);

        await client.end();
    } catch (e) {
        console.log(e);
        return res.status(500).send(e);
    }
});

router.post('/userLogin', async (req : Request, res : Response) => {
    const client = new Client({
        database: 'qdio'
    });

    try {
        await client.connect();

        const query = 'SELECT user_login($1, $2)';

        const qRes = await client.query(query,
                                        [req.body.uid, req.body.hash]);

        let loginSuccessful = qRes.rows[0].user_login;

        if (!req.session)
            throw Error('Session not found in request');

        if (loginSuccessful)
            req.session.uid = req.body.uid;

        res.send(loginSuccessful);

        await client.end();

    } catch (e) {
        console.log(e);
        return res.status(500).send();
    }
});

export default router;
