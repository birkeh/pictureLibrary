#ifndef CPICTURELIBRARY_H
#define CPICTURELIBRARY_H


#include <QObject>

#include <QSqlDatabase>


/**
 * @brief
 *
 */
class cPictureLibrary : public QObject
{
	Q_OBJECT
public:
	/**
	 * @brief
	 *
	 * @param parent
	 */
	explicit cPictureLibrary(QObject *parent = nullptr);

	/*!
	 \brief

	 \fn openDatabase
	 \return bool
	*/
	bool						openDatabase();
	/*!
	 \brief

	 \fn rootPath
	 \return QString
	*/
	QString						rootPath();

	/*!
	 \brief

	 \fn isValie
	 \return bool
	*/
	bool						isValid();

	/*!
	 \brief

	 \fn database
	 \return QSqlDatabase
	*/
	QSqlDatabase				database();

signals:

public slots:

private:
	QSqlDatabase				m_db;						/*!< TODO: describe */
	QString						m_szRootPath;				/*!< TODO: describe */
	/*!
	 \brief

	 \fn createDatabase
	 \return bool
	*/
	bool						createDatabase();
	/*!
	 \brief

	 \fn updateDatabase
	 \param version
	 \return bool
	*/
	bool						updateDatabase(qint32 version);
	/*!
	 \brief

	 \fn updateDatabase2
	 \return bool
	*/
	bool						updateDatabase2(qint32 version);
	/*!
	 \brief

	 \fn updateDatabase3
	 \return bool
	*/
	bool						updateDatabase3(qint32 version);
	/*!
	 \brief

	 \fn updateDatabase4
	 \return bool
	*/
	bool						updateDatabase4(qint32 version);
	/*!
	 \brief

	 \fn createTable
	 \param szSQL
	 \return bool
	*/
	bool						createTable(const QString& szSQL);
};

#endif // CPICTURELIBRARY_H
