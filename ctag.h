/*!
 \file ctag.h

*/

#ifndef CTAG_H
#define CTAG_H


#include "csplashscreen.h"

#include <QObject>
#include <QList>

#include <QProgressBar>

#include <QMetaType>


/*!
 \brief

 \class cTag ctag.h "ctag.h"
*/
class cTag : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cTag
	 \param parent
	*/
	explicit cTag(qint32 iID = -1, QObject *parent = nullptr);

	/*!
	 \brief

	 \fn toDB
	 \return bool
	*/
	bool					toDB();

	/*!
	 \brief

	 \fn setID
	 \param id
	*/
	void					setID(const qint32& id);
	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32					id();

	/*!
	 \brief

	 \fn setName
	 \param name
	*/
	void					setName(const QString& name);
	/*!
	 \brief

	 \fn name
	 \return QString
	*/
	QString					name();

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cTag& other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cTag*& other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cTag* other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(cTag* other);

signals:

public slots:

private:
	qint32					m_iID;					/*!< TODO: describe */
	QString					m_szName;				/*!< TODO: describe */
};

Q_DECLARE_METATYPE(cTag*)

/*!
 \brief

 \class cTagList ctag.h "ctag.h"
*/
class cTagList : public QObject, public QList<cTag*>
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cTagList
	 \param parent
	*/
	explicit				cTagList(QObject *parent = nullptr);

	/*!
	 \brief

	 \fn load
	 \param lpSplashScreen
	 \param lpProgressBar
	 \return bool
	*/
	bool					load(cSplashScreen* lpSplashScreen, QProgressBar* lpProgressBar = nullptr);

	/*!
	 \brief

	 \fn add
	 \param iID
	 \param bNoCheck
	 \return cTag
	*/
	cTag*					add(qint32 iID = -1, bool bNoCheck = false);
	/*!
	 \brief

	 \fn add
	 \param cTag
	 \param bNoCheck
	 \return bool
	*/
	bool					add(cTag* lpTag, bool bNoCheck = false);

	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cTag
	*/
	cTag*					find(qint32 iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cTag
	*/
	cTag*					find(cTag* lpTag);

	/*!
	 \brief

	 \fn tagList
	 \return QStringList
	*/
	QStringList				tagList();
signals:

public slots:
};

#endif // CTAG_H
