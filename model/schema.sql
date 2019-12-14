CREATE TABLE user_account (
       id            SERIAL PRIMARY KEY,
       name          text NOT NULL,
       email         varchar(100) NOT NULL,
       password_salt varchar(8) NOT NULL,
       password_hash varchar(128) NOT NULL
);

CREATE TABLE station (
       id serial PRIMARY KEY,
       name text NOT NULL
);

CREATE TABLE show (
       id    serial PRIMARY KEY,
       name  text NOT NULL,
       owner integer NOT NULL REFERENCES station (id) ON DELETE CASCADE
);

CREATE TABLE cart_wall (
       id            serial PRIMARY KEY,
       name          text,
       station_owner integer REFERENCES station (id) ON DELETE CASCADE,
       show_owner    integer REFERENCES show (id) ON DELETE CASCADE,
       user_owner    integer REFERENCES user_account (id) ON DELETE CASCADE,
       CONSTRAINT single_owner CHECK (num_nonnulls(station_owner, show_owner, user_owner) = 1)
);

CREATE TABLE audio_file (
       id            serial PRIMARY KEY,
       name          text,
       location      text NOT NULL,
       station_owner integer REFERENCES station (id) ON DELETE CASCADE,
       show_owner    integer REFERENCES show (id) ON DELETE CASCADE,
       user_owner    integer REFERENCES user_account (id) ON DELETE CASCADE,
       CONSTRAINT single_owner CHECK (num_nonnulls(station_owner, show_owner, user_owner) = 1)
);

CREATE TABLE user_show (
       show_id  integer NOT NULL REFERENCES show(id) ON DELETE CASCADE,
       user_id  integer NOT NULL REFERENCES user_account(id) ON DELETE CASCADE,
       PRIMARY KEY(show_id, user_id)
);

create table colour (
       id   serial PRIMARY KEY,
       name text,
       hex  varchar(7) NOT NULL
);

INSERT INTO colour(name, hex) VALUES ('RED', '#ff0000'),
                                     ('ORANGE', '#ffcc00'),
                                     ('YELLOW', '#ffff00'),
                                     ('GREEN', '#00ff00'),
                                     ('BLUE', '#0000ff'),
                                     ('FUCHSIA', '#ff00ff'),
                                     ('GREY', '#808080'),
                                     ('BLACK', '#000000'),
                                     ('WHITE', '#ffffff');

CREATE TABLE cart_theme (
       id          serial PRIMARY KEY,
       name        text,
       bg_colour   integer NOT NULL REFERENCES colour(id),
       text_colour integer NOT NULL REFERENCES colour(id)
);

CREATE TABLE cart (
       title	text NOT NULL,
       wall     integer NOT NULL REFERENCES cart_wall (id) ON DELETE CASCADE,
       page     integer NOT NULL,
       x        integer NOT NULL,
       y        integer NOT NULL,
       theme    integer NOT NULL REFERENCES cart_theme(id),
       file     integer NOT NULL REFERENCES audio_file(id),
       PRIMARY KEY(wall, page, x, y),
       CONSTRAINT page_valid_range CHECK (page >= 0 AND page <=7),
       CONSTRAINT x_valid_range CHECK (x >= 0 AND x <= 4),
       CONSTRAINT y_valid_range CHECK (y >= 0 AND y <= 3)
);
