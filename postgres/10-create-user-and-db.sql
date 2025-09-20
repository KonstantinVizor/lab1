-- file: 10-create-user-and-db.sql
CREATE DATABASE persons;
CREATE ROLE program WITH PASSWORD 'test';
GRANT ALL PRIVILEGES ON DATABASE persons TO program;
ALTER ROLE program WITH LOGIN;

\connect persons;
create table persons (
        id serial primary key not null,
        name varchar not null,
        age int not null,
        address varchar not null,
        work varchar not null
);
GRANT ALL PRIVILEGES ON TABLE persons TO program;
GRANT ALL PRIVILEGES ON SEQUENCE persons_id_seq TO program;
