/*!
 \file cpicturelibrary.cpp

*/

#include "cpicturelibrary.h"
#include "common.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QSqlRecord>

#include <QDir>

#include <QSettings>


cPictureLibrary::cPictureLibrary(QObject *parent) : QObject(parent)
{
}

bool cPictureLibrary::openDatabase(const QString& szPath)
{
	if(m_db.isOpen())
		m_db.close();

	m_szRootPath		= "";
	QString		szDB	= szPath + "/" + "pictureLibrary.db";

	m_db	= QSqlDatabase::addDatabase("QSQLITE");
	m_db.setHostName("localhost");
	m_db.setDatabaseName(szDB);

	if(!m_db.open())
	{
		myDebug << m_db.lastError().text();
		return(false);
	}

	QSqlQuery	query;
	if(!m_db.tables().contains("config"))
		createDatabase();
	else
	{
		query.prepare("SELECT version FROM config;");
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			m_db.close();
			return(false);
		}

		if(!query.first())
			myDebug << query.lastError().text();

		qint32	version	= query.value("version").toInt();
		if(version < 4)
			updateDatabase(version);
		query.finish();
	}

	m_szRootPath	= szPath;

	return(true);
}

QString cPictureLibrary::rootPath()
{
	return(m_szRootPath);
}

bool cPictureLibrary::isValid()
{
	if(m_db.isOpen() && m_db.isValid())
		return(true);
	return(false);
}

QSqlDatabase cPictureLibrary::database()
{
	return(m_db);
}

bool cPictureLibrary::createTable(const QString& szSQL)
{
	QSqlQuery	query;

	query.prepare(szSQL);

	if(!query.exec())
	{
		myDebug << szSQL << "\n" << query.lastError().text();
		return(false);
	}

	return(true);
}

bool cPictureLibrary::createDatabase()
{
	QSqlQuery	query;

	if(!createTable("CREATE TABLE config ( "
					"    version                  INTEGER"
					"); "))
		return(false);

	if(!createTable("CREATE TABLE picture ( "
					"    id                       INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
					"    fileName                 TEXT, "
					"    fileSize                 BIGINT, "
					"    mimeType                 TEXT, "
					"    title                    TEXT, "
					"    imageWidth               INTEGER, "
					"    imageHeight              INTEGER, "
					"    imageOrientation         INTEGER, "
					"    cameraMake               TEXT, "
					"    cameraModel              TEXT, "
					"    dateTime                 DATETIME, "
					"    fNumber                  TEXT, "
					"    iso                      INTEGER, "
					"    flashID                  INTEGER, "
					"    focalLength              DOUBLE, "
					"    lensMake                 TEXT, "
					"    lensModel                TEXT, "
					"    exposureTime             TEXT, "
					"    exposureBias             INTEGER, "
					"    exifVersion              TEXT, "
					"    dateTimeOriginal         DATETIME, "
					"    dateTimeDigitized        DATETIME, "
					"    whiteBalance             INTEGER, "
					"    focalLength35            DOUBLE, "
					"    gps                      TEXT, "
					"    duration                 BIGINT, "
					"    hdr                      BOOLEAN, "
					"    thumbnail                BLOB"
					"); "))
		return(false);

	if(!createTable("CREATE TABLE person ( "
					"    id                       INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
					"    name                     TEXT "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE location ( "
					"    id                       INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
					"    name                     TEXT "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE tag ( "
					"    id                       INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
					"    name                     TEXT "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE picture_tag ( "
					"    pictureID INTEGER REFERENCES picture (id), "
					"    tagID   INTEGER REFERENCES tag (id) "
					"); "))
		return(false);

	if(!createTable("CREATE UNIQUE INDEX picture_tag_idx ON picture_tag ( "
					"    pictureID, "
					"    tagID "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE picture_person ( "
					"    pictureID INTEGER REFERENCES picture (id), "
					"    personID   INTEGER REFERENCES people (id)  "
					"); "))
		return(false);

	if(!createTable("CREATE UNIQUE INDEX picture_person_idx ON picture_person ( "
					"    pictureID, "
					"    personID "
					"); "))
		return(false);

	if(!createTable("CREATE TABLE picture_location ( "
					"    pictureID INTEGER REFERENCES picture (id), "
					"    locationID   INTEGER REFERENCES location (id)  "
					"); "))
		return(false);

	if(!createTable("CREATE UNIQUE INDEX picture_location_idx ON picture_location ( "
					"    pictureID, "
					"    personID "
					"); "))
		return(false);

	query.prepare("INSERT INTO config (version) VALUES (:version);");
	query.bindValue(":version", 1);
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	return(true);
}

bool cPictureLibrary::updateDatabase(qint32 /*version*/)
{
//	if(version < 4)
//		updateDatabase4(version);

	return(true);
}

