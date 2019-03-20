/*!
 \file cperson.h

*/

#ifndef CPERSON_H
#define CPERSON_H


#include "csplashscreen.h"

#include <QObject>
#include <QList>

#include <QProgressBar>

#include <QMetaType>


/*!
 \brief

 \class cPerson cperson.h "cperson.h"
*/
class cPerson : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cPerson
	 \param parent
	*/
	explicit cPerson(qint32 iID = -1, QObject *parent = nullptr);

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
	bool					operator==(const cPerson& other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cPerson*& other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cPerson* other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(cPerson* other);

signals:

public slots:

private:
	qint32					m_iID;					/*!< TODO: describe */
	QString					m_szName;				/*!< TODO: describe */
};

Q_DECLARE_METATYPE(cPerson*)

/*!
 \brief

 \class cPersonList cperson.h "cperson.h"
*/
class cPersonList : public QObject, public QList<cPerson*>
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cPersonList
	 \param parent
	*/
	explicit				cPersonList(QObject *parent = nullptr);

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
	 \return cPerson
	*/
	cPerson*				add(qint32 iID = -1, bool bNoCheck = false);
	/*!
	 \brief

	 \fn add
	 \param cPerson
	 \param bNoCheck
	 \return bool
	*/
	bool					add(cPerson* lpPerson, bool bNoCheck = false);

	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cPerson
	*/
	cPerson*				find(qint32 iID);
	/*!
	 \brief

	 \fn find
	 \param lpPerson
	 \return cPerson
	*/
	cPerson*				find(cPerson* lpPerson);
	/*!
	 \brief

	 \fn find
	 \param szName
	 \return cPerson
	*/
	cPerson*				find(const QString& szName);
	/*!
	 \brief

	 \fn remove
	 \param lpPerson
	 \return bool
	*/
	bool					remove(cPerson* lpPerson);

	/*!
	 \brief

	 \fn PersonList
	 \return QStringList
	*/
	QStringList				personList();
signals:

public slots:
};

#endif // CPERSON_H
