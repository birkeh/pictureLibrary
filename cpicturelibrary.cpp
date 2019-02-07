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

	if(!m_db.tables().contains("config"))
		createDatabase();
	else
	{
		QSqlQuery	query;

		query.prepare("SELECT version FROM config;");
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			m_db.close();
			return(false);
		}

		query.next();
		if(query.value("version").toInt() < 2)
			updateDatabase(query.value("version").toInt());
		query.finish();
	}

	return(true);
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

	query.prepare("INSERT INTO config (version) VALUES (:version);");
	query.bindValue(":version", 1);
	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	return(true);
}

bool cPictureLibrary::updateDatabase(qint32 version)
{
	if(version < 2)
		updateDatabase2(version);

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
