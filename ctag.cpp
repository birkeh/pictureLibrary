/*!
 \file cFlag.cpp

*/

#include "common.h"

#include "cflag.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QApplication>


cFlag::cFlag(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName("")
{
}

bool cFlag::toDB()
{
	QSqlQuery	query;

	if(m_iID != -1)
	{
		query.prepare("SELECT id FROM flag WHERE id=:id;");
		query.bindValue(":id", m_iID);
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			return(false);
		}

		if(!query.next())
			query.prepare("INSERT INTO flag (name) VALUES (:name);");
		else
			query.prepare("UPDATE flag SET name=:name WHERE id=:id;");
	}
	else
		query.prepare("INSERT INTO flag (name) VALUES (:name);");


	query.bindValue(":id",					m_iID);
	query.bindValue(":name",				m_szName);

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	if(m_iID == -1)
	{
		query.prepare("SELECT id FROM flag WHERE _rowid_=(SELECT MAX(_rowid_) FROM flag);");
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

void cFlag::setID(const qint32& id)
{
	m_iID	= id;
}

qint32 cFlag::id()
{
	return(m_iID);
}

void cFlag::setName(const QString &name)
{
	m_szName	= name;
}

QString cFlag::name()
{
	return(m_szName);
}

bool cFlag::operator==(const cFlag& other) const
{
	if(this->m_szName != other.m_szName)
		return(false);

	return(true);
}

bool cFlag::operator==(const cFlag*& other) const
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

bool cFlag::operator==(const cFlag* other) const
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

bool cFlag::operator==(cFlag* other)
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

cFlagList::cFlagList(QObject *parent) :
	QObject(parent)
{
}

bool cFlagList::load(cSplashScreen *lpSplashScreen, QProgressBar *lpProgressBar)
{
	QSqlQuery		query;

	query.prepare("SELECT	COUNT(1) cnt FROM flag;");

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
				  "FROM     flag "
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
		cFlag*	lpFlag	= add(query.value("id").toInt(), true);
		lpFlag->setName(query.value("name").toString());

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

cFlag* cFlagList::add(qint32 iID, bool bNoCheck)
{
	if(iID != -1 && !bNoCheck)
	{
		if(find(iID))
			return(nullptr);
	}

	cFlag*	lpNew	= new cFlag(iID);
	append(lpNew);
	return(lpNew);
}

bool cFlagList::add(cFlag* lpFlag, bool bNoCheck)
{
	if(bNoCheck)
	{
		append(lpFlag);
		return(true);
	}

	if(contains(lpFlag))
		return(false);

	append(lpFlag);
	return(true);
}

cFlag* cFlagList::find(qint32 iID)
{
	for(cFlagList::iterator i = begin(); i != end(); i++)
	{
		if((*i)->id() == iID)
			return(*i);
	}
	return(nullptr);
}

cFlag* cFlagList::find(cFlag* lpFlag)
{
	for(cFlagList::iterator i = begin(); i != end(); i++)
	{
		if(*lpFlag == (**i))
			return(*i);
	}
	return(nullptr);
}

QStringList cFlagList::flagList()
{
	QStringList	szFlagList;

	for(cFlagList::iterator i = begin(); i != end();i++)
		szFlagList.append((*i)->name());

	szFlagList.removeDuplicates();
	szFlagList.sort(Qt::CaseInsensitive);
	return(szFlagList);
}
