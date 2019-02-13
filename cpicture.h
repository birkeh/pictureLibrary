#ifndef CPICTURE_H
#define CPICTURE_H


#include <QObject>
#include <QList>
#include <QImage>
#include <QDateTime>

#include <QMetaType>


/**
 * @brief
 *
 */
class cPicture : public QObject
{
	Q_OBJECT
public:
	/**
	 * @brief
	 *
	 * @param parent
	 */
	explicit cPicture(qint32 iID = -1, QObject *parent = nullptr);

	/**
	 * @brief
	 *
	 * @param szFileName
	 * @return bool
	 */
	bool					fromFile(const QString& szFileName);
	/**
	 * @brief
	 *
	 * @param db
	 * @param iID
	 * @return bool
	 */
	bool					toDB();

	void					setID(const qint32& id);
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32					id();

	/**
	 * @brief
	 *
	 * @param imageWidth
	 */
	void					setImageWidth(const qint32& imageWidth);
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32					imageWidth();

	/**
	 * @brief
	 *
	 * @param imageHeight
	 */
	void					setImageHeight(const qint32& imageHeight);
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32					imageHeight();

	/**
	 * @brief
	 *
	 * @param imageOrientation
	 */
	void					setImageOrientation(const qint16& imageOrientation);
	/**
	 * @brief
	 *
	 * @return qint16
	 */
	qint16					imageOrientation();

	/**
	 * @brief
	 *
	 * @param cameraMake
	 */
	void					setCameraMake(const QString& cameraMake);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					cameraMake();

	/**
	 * @brief
	 *
	 * @param cameraModel
	 */
	void					setCameraModel(const QString& cameraModel);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					cameraModel();

	/**
	 * @brief
	 *
	 * @param dateTime
	 */
	void					setDateTime(const QDateTime& dateTime);
	/**
	 * @brief
	 *
	 * @return QDateTime
	 */
	QDateTime				dateTime();

	/**
	 * @brief
	 *
	 * @param fNumber
	 */
	void					setFNumber(const QString& fNumber);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					fNumber();

	/**
	 * @brief
	 *
	 * @param iso
	 */
	void					setISO(const qint32& iso);
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32					iso();

	/**
	 * @brief
	 *
	 * @param flash
	 */
	void					setFlash(const QString& flash);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					flash();

	/**
	 * @brief
	 *
	 * @param flashID
	 */
	void					setFlashID(const qint32& flashID);
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32					flashID();

	/**
	 * @brief
	 *
	 * @param focalLength
	 */
	void					setFocalLength(const qreal& focalLength);
	/**
	 * @brief
	 *
	 * @return qreal
	 */
	qreal					focalLength();

	/**
	 * @brief
	 *
	 * @param lensMake
	 */
	void					setLensMake(const QString& lensMake);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					lensMake();

	/**
	 * @brief
	 *
	 * @param lensModel
	 */
	void					setLensModel(const QString& lensModel);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					lensModel();

	/**
	 * @brief
	 *
	 * @param exposureTime
	 */
	void					setExposureTime(const QString& exposureTime);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					exposureTime();

	/**
	 * @brief
	 *
	 * @param exposureBias
	 */
	void					setExposureBias(const qint32& exposureBias);
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32					exposureBias();

	/**
	 * @brief
	 *
	 * @param exifVersion
	 */
	void					setExifVersion(const QString& exifVersion);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					exifVersion();

	/**
	 * @brief
	 *
	 * @param dateTimeOriginal
	 */
	void					setDateTimeOriginal(const QDateTime& dateTimeOriginal);
	/**
	 * @brief
	 *
	 * @return QDateTime
	 */
	QDateTime				dateTimeOriginal();

	/**
	 * @brief
	 *
	 * @param dateTimeDigitized
	 */
	void					setDateTimeDigitized(const QDateTime& dateTimeDigitized);
	/**
	 * @brief
	 *
	 * @return QDateTime
	 */
	QDateTime				dateTimeDigitized();

	/**
	 * @brief
	 *
	 * @param whiteBalance
	 */
	void					setWhiteBalance(const qint32& whiteBalance);
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32					whiteBalance();

	/**
	 * @brief
	 *
	 * @param focalLength35
	 */
	void					setFocalLength35(const qreal& focalLength35);
	/**
	 * @brief
	 *
	 * @return qreal
	 */
	qreal					focalLength35();

	/**
	 * @brief
	 *
	 * @param gps
	 */
	void					setGPS(const QString& gps);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					gps();

	/**
	 * @brief
	 *
	 * @param fileName
	 */
	void					setFileName(const QString& fileName);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					fileName();

	/**
	 * @brief
	 *
	 * @param filePath
	 */
	void					setFilePath(const QString& filePath);
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					filePath();

	/**
	 * @brief
	 *
	 * @param fileSize
	 */
	void					setFileSize(const qint64& fileSize);
	/**
	 * @brief
	 *
	 * @return qint64
	 */
	qint64					fileSize();

	/**
	 * @brief
	 *
	 * @param thumbnail
	 */
	void					setThumbnail(const QImage& thumbnail);
	/**
	 * @brief
	 *
	 * @return QImage
	 */
	QImage					thumbnail();

signals:

public slots:

private:
	qint32					m_iID;					/**< TODO: describe */
	QString					m_szFileName;			/**< TODO: describe */
	QString					m_szFilePath;			/**< TODO: describe */
	qint64					m_iFileSize;			/**< TODO: describe */
	QImage					m_thumbnail;			/**< TODO: describe */
	qint32					m_imageWidth;			/**< TODO: describe */
	qint32					m_imageHeight;			/**< TODO: describe */
	qint16					m_imageOrientation;		/**< TODO: describe */
	QString					m_cameraMake;			/**< TODO: describe */
	QString					m_cameraModel;			/**< TODO: describe */
	QDateTime				m_dateTime;				/**< TODO: describe */
	QString					m_fNumber;				/**< TODO: describe */
	qint32					m_iso;					/**< TODO: describe */
	QString					m_flash;				/**< TODO: describe */
	qint32					m_flashID;				/**< TODO: describe */
	qreal					m_focalLength;			/**< TODO: describe */
	QString					m_lensMake;				/**< TODO: describe */
	QString					m_lensModel;			/**< TODO: describe */
	QString					m_exposureTime;			/**< TODO: describe */
	qint32					m_exposureBias;			/**< TODO: describe */
	QString					m_exifVersion;			/**< TODO: describe */
	QDateTime				m_dateTimeOriginal;		/**< TODO: describe */
	QDateTime				m_dateTimeDigitized;	/**< TODO: describe */
	qint32					m_whiteBalance;			/**< TODO: describe */
	qreal					m_focalLength35;		/**< TODO: describe */
	QString					m_gps;					/**< TODO: describe */
};

Q_DECLARE_METATYPE(cPicture*)

/**
 * @brief
 *
 */
class cPictureList : public QObject, public QList<cPicture*>
{
	Q_OBJECT
public:
	/**
	 * @brief
	 *
	 * @param parent
	 */
	explicit				cPictureList(QObject *parent = nullptr);

	bool					load();

	/**
	 * @brief
	 *
	 * @param iID
	 * @return cPicture
	 */
	cPicture*				add(qint32 iID = -1);
	/**
	 * @brief
	 *
	 * @param iID
	 * @return cPicture
	 */
	cPicture*				find(qint32 iID);

signals:

public slots:
};

#endif // CPICTURE_H
