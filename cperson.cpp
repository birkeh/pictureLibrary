/*!
 \file cPerson.cpp

*/

#include "common.h"

#include "cperson.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QApplication>


cPerson::cPerson(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName("")
{
}

bool cPerson::toDB()
{
	QSqlQuery	query;

	query.prepare("SELECT id FROM person WHERE UPPER(name)=UPPER(:name);");
	query.bindValue(":name", m_szName);
	if(query.exec())
	{
		if(query.next())
			return(false);
	}

	if(m_iID != -1)
	{
		query.prepare("SELECT id FROM person WHERE id=:id;");
		query.bindValue(":id", m_iID);
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			return(false);
		}

		if(!query.next())
			query.prepare("INSERT INTO person (name) VALUES (:name);");
		else
			query.prepare("UPDATE person SET name=:name WHERE id=:id;");
	}
	else
		query.prepare("INSERT INTO person (name) VALUES (:name);");


	query.bindValue(":id",					m_iID);
	query.bindValue(":name",				m_szName);

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	if(m_iID == -1)
	{
		query.prepare("SELECT id FROM person WHERE _rowid_=(SELECT MAX(_rowid_) FROM person);");
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

void cPerson::setID(const qint32& id)
{
	m_iID	= id;
}

qint32 cPerson::id()
{
	return(m_iID);
}

void cPerson::setName(const QString &name)
{
	m_szName	= name;
}

QString cPerson::name()
{
	return(m_szName);
}

bool cPerson::operator==(const cPerson& other) const
{
	if(this->m_szName != other.m_szName)
		return(false);

	return(true);
}

bool cPerson::operator==(const cPerson*& other) const
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

bool cPerson::operator==(const cPerson* other) const
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

bool cPerson::operator==(cPerson* other)
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

cPersonList::cPersonList(QObject *parent) :
	QObject(parent)
{
}

bool cPersonList::load(cSplashScreen *lpSplashScreen, QProgressBar *lpProgressBar)
{
	QSqlQuery		query;

	query.prepare("SELECT	COUNT(1) cnt FROM person;");

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
				  "FROM     person "
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
		cPerson*	lpFlags	= add(query.value("id").toInt(), true);
		lpFlags->setName(query.value("name").toString());

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

cPerson* cPersonList::add(qint32 iID, bool bNoCheck)
{
	if(iID != -1 && !bNoCheck)
	{
		if(find(iID))
			return(nullptr);
	}

	cPerson*	lpNew	= new cPerson(iID);
	append(lpNew);
	return(lpNew);
}

bool cPersonList::add(cPerson* lpFlags, bool bNoCheck)
{
	if(bNoCheck)
	{
		append(lpFlags);
		return(true);
	}

	if(contains(lpFlags))
		return(false);

	append(lpFlags);
	return(true);
}

cPerson* cPersonList::find(qint32 iID)
{
	for(cPersonList::iterator i = begin(); i != end(); i++)
	{
		if((*i)->id() == iID)
			return(*i);
	}
	return(nullptr);
}

cPerson* cPersonList::find(cPerson* lpPerson)
{
	for(cPersonList::iterator i = begin(); i != end(); i++)
	{
		if(*lpPerson == (**i))
			return(*i);
	}
	return(nullptr);
}

bool cPersonList::remove(cPerson* lpPerson)
{
	if(!find(lpPerson))
		return(true);

	QSqlQuery	query;

	query.prepare("SELECT COUNT(1) cnt FROM picture_person WHERE personID=:id;");
	query.bindValue(":id", lpPerson->id());

	if(!query.exec())
		return(false);

	if(!query.next())
		return(false);

	if(query.value("cnt").toInt() != 0)
		return(false);

	query.prepare("DELETE FROM person WHERE id=:id;");
	query.bindValue(":id", lpPerson->id());

	if(!query.exec())
		return(false);

	this->removeOne(lpPerson);
	delete lpPerson;

	return(true);
}

QStringList cPersonList::personList()
{
	QStringList	szPersonList;

	for(cPersonList::iterator i = begin(); i != end();i++)
		szPersonList.append((*i)->name());

	szPersonList.removeDuplicates();
	szPersonList.sort(Qt::CaseInsensitive);
	return(szPersonList);
}
