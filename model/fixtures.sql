INSERT INTO user_account values (0, 'matt', 'matt@qdio.co.uk', '7eb78e95', '896b3c4230284af4e86fd78241c75ae57cf8f21bed1275cebf002b284e033d96');
INSERT INTO user_account values (1, 'james', 'james@qdio.co.uk', '7eb78e95', '896b3c4230284af4e86fd78241c75ae57cf8f21bed1275cebf002b284e033d96');

INSERT INTO show VALUES (0, 'Matts Show'),
                        (1, 'James Show'),
                        (2, 'And the other show!');

INSERT INTO user_show VALUES (0, 0),
                             (1, 1),
                             (2, 0),
                             (2, 1);
