CREATE TABLE show (
       id      serial PRIMARY KEY,
       title   varchar(50) UNIQUE NOT NULL
);

CREATE TABLE cart (
       title	varchar(20) NOT NULL,
       show     integer REFERENCES show (id) ON DELETE CASCADE,
       page     integer,
       x        integer,
       y        integer,
       PRIMARY KEY(page, x, y),
       CONSTRAINT page_valid_range CHECK (page >= 0 AND page <=7),
       CONSTRAINT x_valid_range CHECK (x >= 0 AND x <= 3),
       CONSTRAINT y_valid_range CHECK (y >= 0 AND y <= 3)
);

CREATE TABLE user_account (
       id            serial PRIMARY KEY,
       name	     varchar(20) UNIQUE NOT NULL,
       email         varchar(100) NOT NULL,
       password_salt varchar(8) NOT NULL,
       password_hash varchar(128) NOT NULL
);

CREATE TABLE user_show (
       show_id  integer REFERENCES show(id) ON DELETE CASCADE,
       user_id  integer REFERENCES user_account(id) ON DELETE CASCADE,
       PRIMARY KEY(show_id, user_id)
);
