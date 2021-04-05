#ifndef DBFORM_H
#define DBFORM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMap>

namespace Ui {
class DBform;
}

class DBform : public QDialog
{
    Q_OBJECT

public:
    explicit DBform(QWidget *parent = nullptr,QString system_type="РИФ+");
    ~DBform();

    //при открытии формы нужно найти в QSqlDatabase db
    // и отобразить в таблице все бд с названием rif_bd0 (1,2,3)
    void find_rif_db(QSqlDatabase db);

    QList<QString> databases;

private slots:


    void on_add_DB_pushButton_clicked();

    void on_drop_BD_pushButton_clicked();

    void on_use_DB_pushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::DBform *ui;

    QMap <int,QString> m_db_rif{
        {0,"rif_db0"},
        {1,"rif_db1"},
        {2,"rif_db2"},
        {3,"rif_db3"},

    };

    QMap <int,QString> m_db_ssoi{

        {0,"ssoi_db0"},
        {1,"ssoi_db1"},
        {2,"ssoi_db2"},
        {3,"ssoi_db3"},
    };

    QString sys_type;

signals:
    void create_db(QString db_name);
    void drop_db(QString db_name);
    void use_db(QString db_name);
};

#endif // DBFORM_H

/*
-- Database: rif_db0

-- DROP DATABASE rif_db0;

CREATE DATABASE rif_db0
  WITH OWNER = postgres
       ENCODING = 'UTF8'
       TABLESPACE = pg_default
       LC_COLLATE = 'ru_RU.UTF-8'
       LC_CTYPE = 'ru_RU.UTF-8'
       CONNECTION LIMIT = -1;



 */

/*
-- Sequence: public.jour_id_seq

-- DROP SEQUENCE public.jour_id_seq;

CREATE SEQUENCE public.jour_id_seq
  INCREMENT 1
  MINVALUE 1
  MAXVALUE 9223372036854775807
  START 124646
  CACHE 1;
ALTER TABLE public.jour_id_seq
  OWNER TO root;

 */

/*
-- Table: public.jour

-- DROP TABLE public.jour;

CREATE TABLE public.jour
(
  id integer NOT NULL DEFAULT nextval('jour_id_seq'::regclass),
  cdate timestamp without time zone NOT NULL DEFAULT now(),
  mdate timestamp without time zone NOT NULL DEFAULT now(),
  objectid integer,
  object character varying(128),
  comment character varying(256) NOT NULL,
  reason character varying(256),
  measures character varying(256),
  operator character varying(256),
  operatorid character varying(256),
  status character varying(32),
  direction character varying(32),
  type bigint,
  flag bigint,
  d1 bigint,
  d2 bigint,
  d3 bigint,
  d4 bigint,
  objecttype bigint
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.jour
  OWNER TO root;

 */
