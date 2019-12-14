FROM postgres:alpine

COPY schema.sql /docker-entrypoint-initdb.d/01-schema.sql
COPY functions.sql /docker-entrypoint-initdb.d/02-functions.sql
COPY fixtures.sql /docker-entrypoint-initdb.d/03-fixtures.sql
