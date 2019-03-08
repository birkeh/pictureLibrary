/*!
 \file cFlag.h

*/

#ifndef cFlag_H
#define cFlag_H


#include "csplashscreen.h"

#include <QObject>
#include <QList>

#include <QProgressBar>

#include <QMetaType>


/*!
 \brief

 \class cFlag cflag.h "cflag.h"
*/
class cFlag : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cFlag
	 \param parent
	*/
	explicit cFlag(qint32 iID = -1, QObject *parent = nullptr);

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
	bool					operator==(const cFlag& other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cFlag*& other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cFlag* other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(cFlag* other);

signals:

public slots:

private:
	qint32					m_iID;					/*!< TODO: describe */
	QString					m_szName;				/*!< TODO: describe */
};

Q_DECLARE_METATYPE(cFlag*)

/*!
 \brief

 \class cFlagList cflag.h "cflag.h"
*/
class cFlagList : public QObject, public QList<cFlag*>
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cFlagList
	 \param parent
	*/
	explicit				cFlagList(QObject *parent = nullptr);

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
	 \return cFlag
	*/
	cFlag*					add(qint32 iID = -1, bool bNoCheck = false);
	/*!
	 \brief

	 \fn add
	 \param cFlag
	 \param bNoCheck
	 \return bool
	*/
	bool					add(cFlag* lpFlags, bool bNoCheck = false);

	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cFlag
	*/
	cFlag*					find(qint32 iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cFlag
	*/
	cFlag*					find(cFlag* lpFlags);

	/*!
	 \brief

	 \fn flagList
	 \return QStringList
	*/
	QStringList				flagList();
signals:

public slots:
};

#endif // cFlag_H
