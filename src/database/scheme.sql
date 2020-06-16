-- SEQUENCE: public.jour_id_seq

-- DROP SEQUENCE public.jour_id_seq;

CREATE SEQUENCE public.jour_id_seq
    INCREMENT 1
    START 1
    MINVALUE 1
    MAXVALUE 9223372036854775807
    CACHE 1;

ALTER SEQUENCE public.jour_id_seq
    OWNER TO root;
--
--
-- SEQUENCE: public.message_id_seq

-- DROP SEQUENCE public.message_id_seq;

CREATE SEQUENCE public.message_id_seq
    INCREMENT 1
    START 1
    MINVALUE 1
    MAXVALUE 9223372036854775807
    CACHE 1;

ALTER SEQUENCE public.message_id_seq
    OWNER TO root;
--
--
-- Table: public.jour

-- DROP TABLE public.jour;

CREATE TABLE public.jour
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
    direction character varying(1) COLLATE pg_catalog."default",
    CONSTRAINT jour_pkey PRIMARY KEY (id)
)

TABLESPACE pg_default;

ALTER TABLE public.jour
    OWNER to root;
--
--
-- Table: public.message

-- DROP TABLE public.message;

CREATE TABLE public.message
(
    id integer NOT NULL DEFAULT nextval('message_id_seq'::regclass),
    cdate timestamp without time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
    mdate timestamp without time zone NOT NULL DEFAULT CURRENT_TIMESTAMP,
    object character varying(128) COLLATE pg_catalog."default",
    operatorid character varying(256) COLLATE pg_catalog."default",
    direction character varying(1) COLLATE pg_catalog."default",
    bytearraydata bytea,
    CONSTRAINT message_pkey PRIMARY KEY (id)
)

TABLESPACE pg_default;

ALTER TABLE public.message
    OWNER to root;
--
--