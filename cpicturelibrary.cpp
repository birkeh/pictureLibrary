#include "cpicturelibrary.h"
#include "common.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QSettings>


cPictureLibrary::cPictureLibrary(QObject *parent) : QObject(parent)
{
	if(!openDatabase())
		return;
}

bool cPictureLibrary::openDatabase()
{
	QSettings	settings;
	QString		szDB	= settings.value("database/path").toString();

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

		query.next();
		if(query.value("version").toInt() < 4)
			updateDatabase(query.value("version").toInt());
		query.finish();
	}

	if(!query.exec("SELECT rootPath FROM config;"))
	{
		myDebug << query.lastError().text();
		return(false);
	}

	if(!query.next())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	m_szRootPath	= query.value("rootPath").toString();

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
					"    version                  INTEGER, "
					"    rootPath                 TEXT"
					"); "))
		return(false);

	if(!createTable("CREATE TABLE picture ( "
					"    id                       INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
					"    fileName                 TEXT, "
					"    filePath                 TEXT, "
					"    imageWidth               INTEGER, "
					"    imageHeight              INTEGER, "
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
					"    thumbnail                BLOB"
					"); "))
		return(false);

	query.prepare("INSERT INTO config (version) VALUES (:version);");
	query.bindValue(":version", 4);
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	return(true);
}

bool cPictureLibrary::updateDatabase(qint32 version)
{
	if(version < 4)
		updateDatabase4(version);

	return(true);
}

bool cPictureLibrary::updateDatabase2(qint32 /*version*/)
{
	QSqlQuery	query;

	if(!query.exec("ALTER TABLE config ADD rootPath TEXT;"))
	{
		myDebug << query.lastError().text();
		return(false);
	}

	if(!query.exec("UPDATE config SET version=2;"))
	{
		myDebug << query.lastError().text();
		return(false);
	}

	return(true);
}

bool cPictureLibrary::updateDatabase3(qint32 version)
{
	if(version < 2)
		updateDatabase2(version);

	QSqlQuery	query;

	if(!createTable("CREATE TABLE picture ( "
					"    id                       INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
					"    fileName                 TEXT, "
					"    imageWidth               INTEGER, "
					"    imageHeight              INTEGER, "
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
					"    thumbnail                BLOB"
					"); "))
		return(false);

	if(!query.exec("UPDATE config SET version=3;"))
	{
		myDebug << query.lastError().text();
		return(false);
	}

	return(true);
}

bool cPictureLibrary::updateDatabase4(qint32 version)
{
	if(version < 3)
		updateDatabase3(version);

	QSqlQuery	query;

	QString	rootPath;

	if(!query.exec("SELECT rootPath FROM config;"))
	{
		myDebug << query.lastError().text();
		return(false);
	}
	if(!query.next())
	{
		myDebug << query.lastError().text();
		return(false);
	}
	rootPath	= query.value("rootPath").toString();

	if(!query.exec("ALTER TABLE picture ADD filePath TEXT;"))
	{
		myDebug << query.lastError().text();
		return(false);
	}

	query.prepare(" UPDATE    picture"
				  " SET       fileName = REPLACE(fileName, RTRIM(fileName, REPLACE(fileName, '\', '')), ''),"
				  "			  filePath = SUBSTR(SUBSTR(fileName, LENGTH(:rootPath1)+2, LENGTH(SUBSTR(fileName, LENGTH(:rootPath2)+2))-LENGTH(REPLACE(fileName, RTRIM(fileName, REPLACE(fileName, '\', '')), ''))), 1, LENGTH(SUBSTR(fileName, LENGTH(:rootPath3)+2, LENGTH(SUBSTR(fileName, LENGTH(:rootPath4)+2))-LENGTH(REPLACE(fileName, RTRIM(fileName, REPLACE(fileName, '\', '')), ''))))-1);");
	query.bindValue(":rootPath1", rootPath);
	query.bindValue(":rootPath2", rootPath);
	query.bindValue(":rootPath3", rootPath);
	query.bindValue(":rootPath4", rootPath);
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	if(!query.exec("UPDATE config SET version=4;"))
	{
		myDebug << query.lastError().text();
		return(false);
	}

	return(true);
}
