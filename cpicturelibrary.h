#ifndef CPICTURELIBRARY_H
#define CPICTURELIBRARY_H


#include <QObject>

#include <QSqlDatabase>


class cPictureLibrary : public QObject
{
	Q_OBJECT
public:
	explicit cPictureLibrary(QObject *parent = nullptr);

	/*!
	 \brief

	 \fn openDatabase
	 \return bool
	*/
	bool						openDatabase();

signals:

public slots:

private:
	QSqlDatabase				m_db;						/*!< TODO: describe */

	/*!
	 \brief

	 \fn createDatabase
	 \return bool
	*/
	bool			createDatabase();
	/*!
	 \brief

	 \fn updateDatabase
	 \param version
	 \return bool
	*/
	bool			updateDatabase(qint32 version);
	/*!
	 \brief

	 \fn updateDatabase1
	 \return bool
	*/
	bool			updateDatabase2(qint32 version);
	/*!
	 \brief

	 \fn createTable
	 \param szSQL
	 \return bool
	*/
	bool			createTable(const QString& szSQL);
};

#endif // CPICTURELIBRARY_H
