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

insert into cart_wall(user_owner, name) values (1, 'Matts cart wall'),
                                               (2, 'james cart wall');
insert into cart_wall(station_owner, name) values (1, 'Qdio show cart wall');
insert into cart_wall(show_owner, name) values (1, 'Matts show cart wall'),
                                               (2, 'james show cart wall');

insert into cart_theme(name, bg_colour, text_colour) values
          ('default', 1, 5),
          ('Ad', 3, 6),
          ('Jingle', 4, 6),
          ('News', 2, 1),
          ('Bed', 6, 2);

insert into cart values ('Matt 1', 4, 0, 0, 0, 1),
                        ('Matt 2', 4, 0, 1, 0, 2),
                        ('Matt 3', 4, 0, 2, 0, 3),
                        ('Matt 4', 4, 0, 3, 0, 4),
                        ('Matt 5', 4, 0, 4, 0, 5);
