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
	qint32					id();

	void					setImageWidth(const qint32& imageWidth);
	qint32					imageWidth();

	void					setImageHeight(const qint32& imageHeight);
	qint32					imageHeight();

	void					setCameraMake(const QString& cameraMake);
	QString					cameraMake();

	void					setCameraModel(const QString& cameraModel);
	QString					cameraModel();

	void					setDateTime(const QDateTime& dateTime);
	QDateTime				dateTime();

	void					setFNumber(const QString& fNumber);
	QString					fNumber();

	void					setISO(const qint32& iso);
	qint32					iso();

	void					setFlash(const QString& flash);
	QString					flash();

	void					setFlashID(const qint32& flashID);
	qint32					flashID();

	void					setFocalLength(const qreal& focalLength);
	qreal					focalLength();

	void					setLensMake(const QString& lensMake);
	QString					lensMake();

	void					setLensModel(const QString& lensModel);
	QString					lensModel();

	void					setExposureTime(const QString& exposureTime);
	QString					exposureTime();

	void					setExposureBias(const qint32& exposureBias);
	qint32					exposureBias();

	void					setExifVersion(const QString& exifVersion);
	QString					exifVersion();

	void					setDateTimeOriginal(const QDateTime& dateTimeOriginal);
	QDateTime				dateTimeOriginal();

	void					setDateTimeDigitized(const QDateTime& dateTimeDigitized);
	QDateTime				dateTimeDigitized();

	void					setWhiteBalance(const qint32& whiteBalance);
	qint32					whiteBalance();

	void					setFocalLength35(const qreal& focalLength35);
	qreal					focalLength35();

	void					setGPS(const QString& gps);
	QString					gps();

	void					setFileName(const QString& fileName);
	QString					fileName();

	void					setFilePath(const QString& filePath);
	QString					filePath();

	void					setThumbnail(const QImage& thumbnail);
	QImage					thumbnail();

signals:

public slots:

private:
	qint32					m_iID;					/**< TODO: describe */
	QString					m_szFileName;			/**< TODO: describe */
	QString					m_szFilePath;			/**< TODO: describe */
	QImage					m_thumbnail;			/**< TODO: describe */
	qint32					m_imageWidth;			/**< TODO: describe */
	qint32					m_imageHeight;			/**< TODO: describe */
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

	cPicture*				add(qint32 iID = -1);
	cPicture*				find(qint32 iID);

signals:

public slots:
};

#endif // CPICTURE_H
