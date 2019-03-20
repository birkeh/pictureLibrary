/*!
 \file clocation.h

*/

#ifndef CLOCATION_H
#define CLOCATION_H


#include "csplashscreen.h"

#include <QObject>
#include <QList>

#include <QProgressBar>

#include <QMetaType>


/*!
 \brief

 \class cLocation clocation.h "clocation.h"
*/
class cLocation : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cLocation
	 \param parent
	*/
	explicit cLocation(qint32 iID = -1, QObject *parent = nullptr);

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
	bool					operator==(const cLocation& other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cLocation*& other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cLocation* other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(cLocation* other);

signals:

public slots:

private:
	qint32					m_iID;					/*!< TODO: describe */
	QString					m_szName;				/*!< TODO: describe */
};

Q_DECLARE_METATYPE(cLocation*)

/*!
 \brief

 \class ccLocation clocation.h "clocation.h"
*/
class cLocationList : public QObject, public QList<cLocation*>
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cLocationList
	 \param parent
	*/
	explicit				cLocationList(QObject *parent = nullptr);

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
	 \return cLocation
	*/
	cLocation*				add(qint32 iID = -1, bool bNoCheck = false);
	/*!
	 \brief

	 \fn add
	 \param cLocation
	 \param bNoCheck
	 \return bool
	*/
	bool					add(cLocation* lpLocation, bool bNoCheck = false);

	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cTag
	*/
	cLocation*				find(qint32 iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cTag
	*/
	cLocation*				find(cLocation* lpLocation);
	/*!
	 \brief

	 \fn find
	 \param szName
	 \return cLocation
	*/
	cLocation*				find(const QString& szLocation);
	/*!
	 \brief

	 \fn remove
	 \param lpLocation
	 \return bool
	*/
	bool					remove(cLocation* lpLocation);

	/*!
	 \brief

	 \fn locationList
	 \return QStringList
	*/
	QStringList				locationList();
signals:

public slots:
};

#endif // CLOCATION_H
