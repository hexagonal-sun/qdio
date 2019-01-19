INSERT INTO user_account(name, email, password_salt, password_hash) values
       ('matt', 'matt@qdio.co.uk', '7eb78e95',
        '896b3c4230284af4e86fd78241c75ae57cf8f21bed1275cebf002b284e033d96'),
       ('james', 'james@qdio.co.uk', '7eb78e95',
        '896b3c4230284af4e86fd78241c75ae57cf8f21bed1275cebf002b284e033d96');

INSERT INTO station(name) VALUES ('Qdio Show');

INSERT INTO show(owner, name) VALUES (1, 'Matts Show'),
                                     (1, 'James Show'),
                                     (1, 'And the other show!');

INSERT INTO user_show VALUES (1, 1),
                             (2, 2),
                             (3, 1),
                             (3, 2);
