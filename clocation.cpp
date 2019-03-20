/*!
 \file clocation.cpp

*/


#include "common.h"

#include "clocation.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QApplication>


cLocation::cLocation(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName("")
{
}

bool cLocation::toDB()
{
	QSqlQuery	query;

	if(m_iID != -1)
	{
		query.prepare("SELECT id FROM location WHERE id=:id;");
		query.bindValue(":id", m_iID);
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			return(false);
		}

		if(!query.next())
			query.prepare("INSERT INTO location (name) VALUES (:name);");
		else
			query.prepare("UPDATE location SET name=:name WHERE id=:id;");
	}
	else
		query.prepare("INSERT INTO location (name) VALUES (:name);");


	query.bindValue(":id",					m_iID);
	query.bindValue(":name",				m_szName);

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	if(m_iID == -1)
	{
		query.prepare("SELECT id FROM location WHERE _rowid_=(SELECT MAX(_rowid_) FROM location);");
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			return(false);
		}

		query.next();
		m_iID	= query.value("id").toInt();
	}

	return(true);
}

void cLocation::setID(const qint32& id)
{
	m_iID	= id;
}

qint32 cLocation::id()
{
	return(m_iID);
}

void cLocation::setName(const QString &name)
{
	m_szName	= name;
}

QString cLocation::name()
{
	return(m_szName);
}

bool cLocation::operator==(const cLocation& other) const
{
	if(this->m_szName != other.m_szName)
		return(false);

	return(true);
}

bool cLocation::operator==(const cLocation*& other) const
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

bool cLocation::operator==(const cLocation* other) const
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

bool cLocation::operator==(cLocation* other)
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

cLocationList::cLocationList(QObject *parent) :
	QObject(parent)
{
}

bool cLocationList::load(cSplashScreen *lpSplashScreen, QProgressBar *lpProgressBar)
{
	QSqlQuery		query;

	query.prepare("SELECT	COUNT(1) cnt FROM location;");

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}
	query.next();

	qint32	max		= static_cast<qint32>(query.value("cnt").toLongLong());

	if(lpProgressBar)
		lpProgressBar->setMaximum(max);
	else if(lpSplashScreen)
		lpSplashScreen->setMax(max);

	query.prepare("SELECT   id, "
				  "         name "
				  "FROM     location "
				  "ORDER BY UPPER(name);");

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	qint32	count	= 0;
	qint32	step	= max/200;

	if(!step)
		step = 1;

	while(query.next())
	{
		cLocation*	lpLocation	= add(query.value("id").toInt(), true);
		lpLocation->setName(query.value("name").toString());

		count++;
		if(!(count % step))
		{
			if(lpProgressBar)
				lpProgressBar->setValue(count);
			else if(lpSplashScreen)
				lpSplashScreen->setProgress(count);
			qApp->processEvents();
		}
	}

	return(true);
}

cLocation* cLocationList::add(qint32 iID, bool bNoCheck)
{
	if(iID != -1 && !bNoCheck)
	{
		if(find(iID))
			return(nullptr);
	}

	cLocation*	lpNew	= new cLocation(iID);
	append(lpNew);
	return(lpNew);
}

bool cLocationList::add(cLocation* lpLocation, bool bNoCheck)
{
	if(bNoCheck)
	{
		append(lpLocation);
		return(true);
	}

	if(contains(lpLocation))
		return(false);

	append(lpLocation);
	return(true);
}

cLocation* cLocationList::find(qint32 iID)
{
	for(cLocationList::iterator i = begin(); i != end(); i++)
	{
		if((*i)->id() == iID)
			return(*i);
	}
	return(nullptr);
}

cLocation* cLocationList::find(cLocation* lpLocation)
{
	for(cLocationList::iterator i = begin(); i != end(); i++)
	{
		if(*lpLocation == (**i))
			return(*i);
	}
	return(nullptr);
}

cLocation* cLocationList::find(const QString& szName)
{
	for(cLocationList::iterator i = begin(); i != end(); i++)
	{
		if(szName == (*i)->name())
			return(*i);
	}
	return(nullptr);
}

bool cLocationList::remove(cLocation* lpLocation)
{
	if(!find(lpLocation))
		return(true);

	QSqlQuery	query;

	query.prepare("SELECT COUNT(1) cnt FROM picture_location WHERE locationID=:id;");
	query.bindValue(":id", lpLocation->id());

	if(!query.exec())
		return(false);

	if(!query.next())
		return(false);

	if(query.value("cnt").toInt() != 0)
		return(false);

	query.prepare("DELETE FROM location WHERE id=:id;");
	query.bindValue(":id", lpLocation->id());

	if(!query.exec())
		return(false);

	this->removeOne(lpLocation);
	delete lpLocation;

	return(true);
}

QStringList cLocationList::locationList()
{
	QStringList	szLocationList;

	for(cLocationList::iterator i = begin(); i != end();i++)
		szLocationList.append((*i)->name());

	szLocationList.removeDuplicates();
	szLocationList.sort(Qt::CaseInsensitive);
	return(szLocationList);
}
