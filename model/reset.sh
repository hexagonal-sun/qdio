#!/bin/bash
set -e

dropdb qdio;
createdb qdio;
psql -d qdio -f model.sql
psql -d qdio -f functions.sql
psql -d qdio -f fixtures.sql
