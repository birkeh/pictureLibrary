/*!
 \file cTag.cpp

*/


#include "common.h"

#include "ctag.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QApplication>


cTag::cTag(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szName("")
{
}

bool cTag::toDB()
{
	QSqlQuery	query;

	if(m_iID != -1)
	{
		query.prepare("SELECT id FROM tag WHERE id=:id;");
		query.bindValue(":id", m_iID);
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			return(false);
		}

		if(!query.next())
			query.prepare("INSERT INTO tag (name) VALUES (:name);");
		else
			query.prepare("UPDATE tag SET name=:name WHERE id=:id;");
	}
	else
		query.prepare("INSERT INTO tag (name) VALUES (:name);");


	query.bindValue(":id",					m_iID);
	query.bindValue(":name",				m_szName);

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	if(m_iID == -1)
	{
		query.prepare("SELECT id FROM tag WHERE _rowid_=(SELECT MAX(_rowid_) FROM tag);");
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

void cTag::setID(const qint32& id)
{
	m_iID	= id;
}

qint32 cTag::id()
{
	return(m_iID);
}

void cTag::setName(const QString &name)
{
	m_szName	= name;
}

QString cTag::name()
{
	return(m_szName);
}

bool cTag::operator==(const cTag& other) const
{
	if(this->m_szName != other.m_szName)
		return(false);

	return(true);
}

bool cTag::operator==(const cTag*& other) const
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

bool cTag::operator==(const cTag* other) const
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

bool cTag::operator==(cTag* other)
{
	if(this->m_szName != other->m_szName)
		return(false);

	return(true);
}

cTagList::cTagList(QObject *parent) :
	QObject(parent)
{
}

bool cTagList::load(cSplashScreen *lpSplashScreen, QProgressBar *lpProgressBar)
{
	QSqlQuery		query;

	query.prepare("SELECT	COUNT(1) cnt FROM tag;");

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
				  "FROM     tag "
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
		cTag*	lpTag	= add(query.value("id").toInt(), true);
		lpTag->setName(query.value("name").toString());

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

cTag* cTagList::add(qint32 iID, bool bNoCheck)
{
	if(iID != -1 && !bNoCheck)
	{
		if(find(iID))
			return(nullptr);
	}

	cTag*	lpNew	= new cTag(iID);
	append(lpNew);
	return(lpNew);
}

bool cTagList::add(cTag* lpTag, bool bNoCheck)
{
	if(bNoCheck)
	{
		append(lpTag);
		return(true);
	}

	if(contains(lpTag))
		return(false);

	append(lpTag);
	return(true);
}

cTag* cTagList::find(qint32 iID)
{
	for(cTagList::iterator i = begin(); i != end(); i++)
	{
		if((*i)->id() == iID)
			return(*i);
	}
	return(nullptr);
}

cTag* cTagList::find(cTag* lpTag)
{
	for(cTagList::iterator i = begin(); i != end(); i++)
	{
		if(*lpTag == (**i))
			return(*i);
	}
	return(nullptr);
}

cTag* cTagList::find(const QString& szName)
{
	for(cTagList::iterator i = begin(); i != end(); i++)
	{
		if(szName == (*i)->name())
			return(*i);
	}
	return(nullptr);
}

bool cTagList::remove(cTag* lpTag)
{
	if(!find(lpTag))
		return(true);

	QSqlQuery	query;

	query.prepare("SELECT COUNT(1) cnt FROM picture_tag WHERE tagID=:id;");
	query.bindValue(":id", lpTag->id());

	if(!query.exec())
		return(false);

	if(!query.next())
		return(false);

	if(query.value("cnt").toInt() != 0)
		return(false);

	query.prepare("DELETE FROM tag WHERE id=:id;");
	query.bindValue(":id", lpTag->id());

	if(!query.exec())
		return(false);

	this->removeOne(lpTag);
	delete lpTag;

	return(true);
}

QStringList cTagList::tagList()
{
	QStringList	szTagList;

	for(cTagList::iterator i = begin(); i != end();i++)
		szTagList.append((*i)->name());

	szTagList.removeDuplicates();
	szTagList.sort(Qt::CaseInsensitive);
	return(szTagList);
}

bool cTagList::contains(cTag* const& lpTag)
{
	return(QList::contains(lpTag));
}

bool cTagList::contains(QList<qint32> idList, bool bAnd)
{
	if(bAnd)
	{
		int	found	= 0;

		for(QList<qint32>::iterator z = idList.begin();z != idList.end();z++)
		{
			for(cTagList::iterator i = begin();i != end();i++)
			{
				if((*i)->id() == (*z))
				{
					found++;
					break;
				}
			}
		}
		if(found == idList.count())
			return(true);
		return(false);
	}
	else
	{
		for(cTagList::iterator i = begin();i != end();i++)
		{
			if(idList.contains((*i)->id()))
				return(true);
		}
		return(false);
	}
}
