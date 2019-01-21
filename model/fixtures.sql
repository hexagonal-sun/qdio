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
          ('default', 5, 9),
          ('Ad', 3, 8),
          ('Jingle', 2, 8),
          ('News', 6, 8),
          ('Bed', 4, 8);

insert into audio_file(name,location,show_owner) values
                      ('Virgin bed', 'virgin.mp3', 1),
                      ('Saw bed', 'saw.m4a', 1);

insert into audio_file(name,location,station_owner) values                      
                      ('survival', 'survival.mp3', 1),
                      ('inside', 'inside.mp3', 1),
                      ('cheesy 80s', 'cheesy_80s.mp3', 1),
                      ('breakdown', 'breakdown_bed.mp3', 1),
                      ('Quiz Bed', 'quiz_bed.mp3', 1),
                      ('News Bed', 'news_bed.mp3', 1),
                      ('News intro', 'news_intro.mp3', 1);

insert into cart values ('Virgin Bed',      4, 0, 0, 0, 1, 1),
                        ('Saw Bed',         4, 0, 1, 0, 2, 2),
                        ('Survival',        3, 0, 0, 0, 1, 3),
                        ('Inside',          3, 0, 1, 0, 2, 4),
                        ('Cheesy 80s',      3, 0, 2, 0, 2, 5),
                        ('Breakdown & Bed', 3, 0, 3, 0, 2, 6),
                        ('Quiz Bed',        3, 0, 4, 0, 3, 7),
                        ('News Bed',        3, 0, 0, 3, 4, 8),
                        ('News Intro',      3, 0, 1, 3, 4, 9);

