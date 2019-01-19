CREATE TABLE cart_wall_entity (
       wall_id   serial PRIMARY KEY,
       name      text
);

CREATE TABLE user_account (
       id            SERIAL PRIMARY KEY,
       email         varchar(100) NOT NULL,
       password_salt varchar(8) NOT NULL,
       password_hash varchar(128) NOT NULL
) INHERITS (cart_wall_entity);

CREATE TABLE station (
       id serial PRIMARY KEY
) INHERITS (cart_wall_entity);

CREATE TABLE show (
       id SERIAL PRIMARY KEY,
       owner integer NOT NULL REFERENCES station (id) ON DELETE CASCADE
) INHERITS (cart_wall_entity);

CREATE TABLE cart_wall (
       id   serial PRIMARY KEY,
       owner integer NOT NULL REFERENCES cart_wall_entity (wall_id) ON DELETE CASCADE
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
       title	varchar(20) NOT NULL,
       wall     integer NOT NULL REFERENCES cart_wall (id) ON DELETE CASCADE,
       page     integer,
       x        integer,
       y        integer,
       theme    integer NOT NULL REFERENCES cart_theme(id),
       PRIMARY KEY(wall, page, x, y),
       CONSTRAINT page_valid_range CHECK (page >= 0 AND page <=7),
       CONSTRAINT x_valid_range CHECK (x >= 0 AND x <= 3),
       CONSTRAINT y_valid_range CHECK (y >= 0 AND y <= 3)
);
