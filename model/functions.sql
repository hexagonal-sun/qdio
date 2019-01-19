-- Given a username, find the corresponding userid in and password
-- salt the database.
--
-- Returns a tuple of userid and password has.  An error is raised if
-- no user can be found.
CREATE OR REPLACE FUNCTION find_user(uname varchar)
RETURNS RECORD
AS $$
DECLARE
    ret RECORD;
BEGIN
   SELECT id, password_salt
       FROM user_account
       WHERE name = uname
       INTO ret;

   IF NOT FOUND THEN
       RAISE 'User % not found', uname;
   END IF;

   RETURN ret;
END;
$$ LANGUAGE plpgsql;

-- For a given userId, set the password hash and salt, effevtively
-- resetting the password for that user.
CREATE OR REPLACE FUNCTION update_password(user_id VARCHAR,
                                           hash    VARCHAR,
                                           salt    VARCHAR)
RETURNS VOID
AS $$
BEGIN
   UPDATE user_account
       SET password_hash = hash,
           password_salt = salt
       WHERE id = user_id;
END;
$$ LANGUAGE plpgsql;

-- For a given user id and password hash, see whether these match in
-- the database.
--
-- Returns true if a match was found and the user can be logged in,
-- false otherwise.
CREATE OR REPLACE FUNCTION user_login(user_id INTEGER,
                                      hash    VARCHAR)
RETURNS BOOLEAN
AS $$
BEGIN
   PERFORM id
       FROM user_account
       WHERE id = user_id AND password_hash = hash;

   RETURN FOUND;
END;
$$ LANGUAGE plpgsql;

-- For a given user, return all the show's that this user has assigned
-- to them.
CREATE OR REPLACE FUNCTION get_shows_for_user(uid INTEGER)
RETURNS TABLE (
    showid   INTEGER,
    showname TEXT
)
AS $$
BEGIN
   RETURN QUERY SELECT show.id, show.name
       FROM show
       INNER JOIN user_show ON user_show.show_id = show.id
       WHERE user_show.user_id = uid;
END;
$$ LANGUAGE plpgsql;

-- For a give show, find the station's cartwall ids.
CREATE OR REPLACE FUNCTION get_station_cartwalls_for_show(showid INTEGER)
RETURNS TABLE (
    id INTEGER,
    name TEXT
)
AS $$
DECLARE
    stationid INTEGER;
BEGIN
    SELECT show.owner INTO stationid FROM show WHERE show.id = showid;

    RETURN QUERY SELECT cart_wall.id, cart_wall.name
         FROM cart_wall
         WHERE cart_wall.station_owner = stationid;
END;
$$ LANGUAGE plpgsql;

-- For a given show, return all the cartwall ids.
CREATE OR REPLACE FUNCTION get_cartwalls_for_show(showid INTEGER)
RETURNS TABLE (
    id INTEGER,
    name TEXT
)
AS $$
BEGIN
    RETURN QUERY SELECT cart_wall.id, cart_wall.name
         FROM cart_wall
         WHERE cart_wall.show_owner = showid;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION get_carts_for_cartwall(cartwallid INTEGER)
RETURNS TABLE (
    title       text,
    page        integer,
    x           integer,
    y           integer,
    bg_colour   varchar,
    text_colour varchar
)
AS $$
BEGIN
    return QUERY SELECT cart.title,
                        cart.page,
                        cart.x,
                        cart.y,
                        bgcol.hex AS bg_colour,
                        textcol.hex AS text_colour
        FROM cart
        INNER JOIN cart_theme ON cart.theme = cart_theme.id
        INNER JOIN colour AS bgcol ON cart_theme.bg_colour = bgcol.id
        INNER JOIN colour AS textcol ON cart_theme.text_colour = textcol.id
        WHERE cart.wall = cartwallid;
END;
$$ LANGUAGE plpgsql;
