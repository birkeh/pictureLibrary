/*!
 \file cpicture.h

*/

#ifndef CPICTURE_H
#define CPICTURE_H


#include "csplashscreen.h"

#include <QObject>
#include <QList>
#include <QImage>
#include <QDateTime>

#include <QProgressBar>

#include <QMetaType>


/*!
 \brief

 \class cPicture cpicture.h "cpicture.h"
*/
class cPicture : public QObject
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cPicture
	 \param iID
	 \param parent
	*/
	explicit cPicture(qint32 iID = -1, QObject *parent = nullptr);

	/*!
	 \brief

	 \fn fromFile
	 \param szFileName
	 \return bool
	*/
	bool					fromFile(const QString& szFileName);
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

	 \fn setMimeType
	 \param mimeType
	*/
	void					setMimeType(const QString& mimeType);
	/*!
	 \brief

	 \fn mimeType
	 \return QString
	*/
	QString					mimeType();

	/*!
	 \brief

	 \fn setImageWidth
	 \param imageWidth
	*/
	void					setImageWidth(const qint32& imageWidth);
	/*!
	 \brief

	 \fn imageWidth
	 \return qint32
	*/
	qint32					imageWidth();

	/*!
	 \brief

	 \fn setImageHeight
	 \param imageHeight
	*/
	void					setImageHeight(const qint32& imageHeight);
	/*!
	 \brief

	 \fn imageHeight
	 \return qint32
	*/
	qint32					imageHeight();

	/*!
	 \brief

	 \fn setImageOrientation
	 \param imageOrientation
	*/
	void					setImageOrientation(const qint16& imageOrientation);
	/*!
	 \brief

	 \fn imageOrientation
	 \return qint16
	*/
	qint16					imageOrientation();

	/*!
	 \brief

	 \fn setCameraMake
	 \param cameraMake
	*/
	void					setCameraMake(const QString& cameraMake);
	/*!
	 \brief

	 \fn cameraMake
	 \return QString
	*/
	QString					cameraMake();

	/*!
	 \brief

	 \fn setCameraModel
	 \param cameraModel
	*/
	void					setCameraModel(const QString& cameraModel);
	/*!
	 \brief

	 \fn cameraModel
	 \return QString
	*/
	QString					cameraModel();

	/*!
	 \brief

	 \fn setDateTime
	 \param dateTime
	*/
	void					setDateTime(const QDateTime& dateTime);
	/*!
	 \brief

	 \fn dateTime
	 \return QDateTime
	*/
	QDateTime				dateTime();

	/*!
	 \brief

	 \fn setFNumber
	 \param fNumber
	*/
	void					setFNumber(const QString& fNumber);
	/*!
	 \brief

	 \fn fNumber
	 \return QString
	*/
	QString					fNumber();

	/*!
	 \brief

	 \fn setISO
	 \param iso
	*/
	void					setISO(const qint32& iso);
	/*!
	 \brief

	 \fn iso
	 \return qint32
	*/
	qint32					iso();

	/*!
	 \brief

	 \fn setFlash
	 \param flash
	*/
	void					setFlash(const QString& flash);
	/*!
	 \brief

	 \fn flash
	 \return QString
	*/
	QString					flash();

	/*!
	 \brief

	 \fn setFlashID
	 \param flashID
	*/
	void					setFlashID(const qint32& flashID);
	/*!
	 \brief

	 \fn flashID
	 \return qint32
	*/
	qint32					flashID();

	/*!
	 \brief

	 \fn setFocalLength
	 \param focalLength
	*/
	void					setFocalLength(const qreal& focalLength);
	/*!
	 \brief

	 \fn focalLength
	 \return qreal
	*/
	qreal					focalLength();

	/*!
	 \brief

	 \fn setLensMake
	 \param lensMake
	*/
	void					setLensMake(const QString& lensMake);
	/*!
	 \brief

	 \fn lensMake
	 \return QString
	*/
	QString					lensMake();

	/*!
	 \brief

	 \fn setLensModel
	 \param lensModel
	*/
	void					setLensModel(const QString& lensModel);
	/*!
	 \brief

	 \fn lensModel
	 \return QString
	*/
	QString					lensModel();

	/*!
	 \brief

	 \fn setExposureTime
	 \param exposureTime
	*/
	void					setExposureTime(const QString& exposureTime);
	/*!
	 \brief

	 \fn exposureTime
	 \return QString
	*/
	QString					exposureTime();

	/*!
	 \brief

	 \fn setExposureBias
	 \param exposureBias
	*/
	void					setExposureBias(const qint32& exposureBias);
	/*!
	 \brief

	 \fn exposureBias
	 \return qint32
	*/
	qint32					exposureBias();

	/*!
	 \brief

	 \fn setExifVersion
	 \param exifVersion
	*/
	void					setExifVersion(const QString& exifVersion);
	/*!
	 \brief

	 \fn exifVersion
	 \return QString
	*/
	QString					exifVersion();

	/*!
	 \brief

	 \fn setDateTimeOriginal
	 \param dateTimeOriginal
	*/
	void					setDateTimeOriginal(const QDateTime& dateTimeOriginal);
	/*!
	 \brief

	 \fn dateTimeOriginal
	 \return QDateTime
	*/
	QDateTime				dateTimeOriginal();

	/*!
	 \brief

	 \fn setDateTimeDigitized
	 \param dateTimeDigitized
	*/
	void					setDateTimeDigitized(const QDateTime& dateTimeDigitized);
	/*!
	 \brief

	 \fn dateTimeDigitized
	 \return QDateTime
	*/
	QDateTime				dateTimeDigitized();

	/*!
	 \brief

	 \fn setWhiteBalance
	 \param whiteBalance
	*/
	void					setWhiteBalance(const qint32& whiteBalance);
	/*!
	 \brief

	 \fn whiteBalance
	 \return qint32
	*/
	qint32					whiteBalance();

	/*!
	 \brief

	 \fn setFocalLength35
	 \param focalLength35
	*/
	void					setFocalLength35(const qreal& focalLength35);
	/*!
	 \brief

	 \fn focalLength35
	 \return qreal
	*/
	qreal					focalLength35();

	/*!
	 \brief

	 \fn setGPS
	 \param gps
	*/
	void					setGPS(const QString& gps);
	/*!
	 \brief

	 \fn gps
	 \return QString
	*/
	QString					gps();

	/*!
	 \brief

	 \fn setDuration
	 \param duration
	*/
	void					setDuration(const qint64& duration);
	/*!
	 \brief

	 \fn gps
	 \return qint64
	*/
	qint64					duration();

	/*!
	 \brief

	 \fn setFileName
	 \param fileName
	*/
	void					setFileName(const QString& fileName);
	/*!
	 \brief

	 \fn fileName
	 \return QString
	*/
	QString					fileName();

	/*!
	 \brief

	 \fn setFilePath
	 \param filePath
	*/
	void					setFilePath(const QString& filePath);
	/*!
	 \brief

	 \fn filePath
	 \return QString
	*/
	QString					filePath();

	/*!
	 \brief

	 \fn setFileSize
	 \param fileSize
	*/
	void					setFileSize(const qint64& fileSize);
	/*!
	 \brief

	 \fn fileSize
	 \return qint64
	*/
	qint64					fileSize();

	/*!
	 \brief

	 \fn setThumbnail
	 \param thumbnail
	*/
	void					setThumbnail(const QImage& thumbnail);
	/*!
	 \brief

	 \fn thumbnail
	 \return QImage
	*/
	QImage					thumbnail();

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cPicture& other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cPicture*& other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(const cPicture* other) const;

	/*!
	 \brief

	 \fn operator==
	 \param other
	 \return bool
	*/
	bool					operator==(cPicture* other);

signals:

public slots:

private:
	qint32					m_iID;					/*!< TODO: describe */
	QString					m_szFileName;			/*!< TODO: describe */
	QString					m_szFilePath;			/*!< TODO: describe */
	qint64					m_iFileSize;			/*!< TODO: describe */
	QImage					m_thumbnail;			/*!< TODO: describe */
	QString					m_mimeType;				/*!< TODO: describe */
	qint32					m_imageWidth;			/*!< TODO: describe */
	qint32					m_imageHeight;			/*!< TODO: describe */
	qint16					m_imageOrientation;		/*!< TODO: describe */
	QString					m_cameraMake;			/*!< TODO: describe */
	QString					m_cameraModel;			/*!< TODO: describe */
	QDateTime				m_dateTime;				/*!< TODO: describe */
	QString					m_fNumber;				/*!< TODO: describe */
	qint32					m_iso;					/*!< TODO: describe */
	QString					m_flash;				/*!< TODO: describe */
	qint32					m_flashID;				/*!< TODO: describe */
	qreal					m_focalLength;			/*!< TODO: describe */
	QString					m_lensMake;				/*!< TODO: describe */
	QString					m_lensModel;			/*!< TODO: describe */
	QString					m_exposureTime;			/*!< TODO: describe */
	qint32					m_exposureBias;			/*!< TODO: describe */
	QString					m_exifVersion;			/*!< TODO: describe */
	QDateTime				m_dateTimeOriginal;		/*!< TODO: describe */
	QDateTime				m_dateTimeDigitized;	/*!< TODO: describe */
	qint32					m_whiteBalance;			/*!< TODO: describe */
	qreal					m_focalLength35;		/*!< TODO: describe */
	QString					m_gps;					/*!< TODO: describe */
	qint64					m_duration;				/*!< TODO: describe */
};

Q_DECLARE_METATYPE(cPicture*)

/*!
 \brief

 \class cPictureList cpicture.h "cpicture.h"
*/
class cPictureList : public QObject, public QList<cPicture*>
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cPictureList
	 \param parent
	*/
	explicit				cPictureList(QObject *parent = nullptr);

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
	 \return cPicture
	*/
	cPicture*				add(qint32 iID = -1, bool bNoCheck = false);
	/*!
	 \brief

	 \fn add
	 \param cPicture
	 \param bNoCheck
	 \return bool
	*/
	bool					add(cPicture* lpPicture, bool bNoCheck = false);

	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cPicture
	*/
	cPicture*				find(qint32 iID);
	/*!
	 \brief

	 \fn find
	 \param iID
	 \return cPicture
	*/
	cPicture*				find(cPicture* lpPicture);

signals:

public slots:
};

#endif // CPICTURE_H
