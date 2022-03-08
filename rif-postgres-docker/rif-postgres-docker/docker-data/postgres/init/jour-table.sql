CREATE SEQUENCE IF NOT EXISTS public.jour_id_seq
    INCREMENT 1
    START 1
    MINVALUE 1
    MAXVALUE 9223372036854775807
    CACHE 1;

CREATE TABLE IF NOT EXISTS public.jour
(
    id integer NOT NULL DEFAULT nextval('jour_id_seq'::regclass),
    cdate timestamp without time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
    mdate timestamp without time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
    objectid integer,
    object character varying(128) COLLATE pg_catalog."default",
    comment character varying(256) COLLATE pg_catalog."default" NOT NULL,
    reason character varying(256) COLLATE pg_catalog."default",
    measures character varying(256) COLLATE pg_catalog."default",
    operator character varying(256) COLLATE pg_catalog."default",
    operatorid character varying(256) COLLATE pg_catalog."default",
    status character varying(32) COLLATE pg_catalog."default",
    direction character varying(32) COLLATE pg_catalog."default",
    type bigint,
    flag bigint,
    d1 bigint,
    d2 bigint,
    d3 bigint,
    d4 bigint,
    objecttype bigint,
    params json
);