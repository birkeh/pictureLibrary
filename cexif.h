#ifndef CEXIF_H
#define CEXIF_H

#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QImage>

#include <QMetaType>
#include <QList>


/**
 * @brief
 *
 */
class cEXIFCompression
{
public:
	cEXIFCompression(const qint32& iID, const QString& szCompression);

	qint32		m_iID; /**< TODO: describe */
	QString		m_szCompression; /**< TODO: describe */
};

Q_DECLARE_METATYPE(cEXIFCompression*)

/**
 * @brief
 *
 */
class cEXIFCompressionList : public QList<cEXIFCompression*>
{
public:
	cEXIFCompressionList();

	/**
	 * @brief
	 *
	 * @param iID
	 * @param szCompression
	 * @return cEXIFCompression
	 */
	cEXIFCompression*	add(const qint32& iID, const QString& szCompression);
	/**
	 * @brief
	 *
	 * @param iID
	 * @return cEXIFCompression
	 */
	cEXIFCompression*	find(const qint32& iID);

	/**
	 * @brief
	 *
	 * @param iID
	 * @return QString
	 */
	QString				compression(const qint32& iID);
};

Q_DECLARE_METATYPE(cEXIFCompressionList)

/**
 * @brief
 *
 */
class cEXIFLightSource
{
public:
	cEXIFLightSource(const qint32& iID, const QString& szLightSource);

	qint32		m_iID; /**< TODO: describe */
	QString		m_szLightSource; /**< TODO: describe */
};

Q_DECLARE_METATYPE(cEXIFLightSource*)

/**
 * @brief
 *
 */
class cEXIFLightSourceList : public QList<cEXIFLightSource*>
{
public:
	cEXIFLightSourceList();

	/**
	 * @brief
	 *
	 * @param iID
	 * @param szLightSource
	 * @return cEXIFLightSource
	 */
	cEXIFLightSource*	add(const qint32& iID, const QString& szLightSource);
	/**
	 * @brief
	 *
	 * @param iID
	 * @return cEXIFLightSource
	 */
	cEXIFLightSource*	find(const qint32& iID);

	/**
	 * @brief
	 *
	 * @param iID
	 * @return QString
	 */
	QString			lightSource(const qint32& iID);
};

/**
 * @brief
 *
 */
class cEXIFFlash
{
public:
	cEXIFFlash(const qint32& iID, const QString& szFlash);

	qint32		m_iID; /**< TODO: describe */
	QString		m_szFlash; /**< TODO: describe */
};

Q_DECLARE_METATYPE(cEXIFFlash*)

/**
 * @brief
 *
 */
class cEXIFFlashList : public QList<cEXIFFlash*>
{
public:
	cEXIFFlashList();

	/**
	 * @brief
	 *
	 * @param iID
	 * @param szFlash
	 * @return cEXIFFlash
	 */
	cEXIFFlash*		add(const qint32& iID, const QString& szFlash);
	/**
	 * @brief
	 *
	 * @param iID
	 * @return cEXIFFlash
	 */
	cEXIFFlash*		find(const qint32& iID);

	/**
	 * @brief
	 *
	 * @param iID
	 * @return QString
	 */
	QString			flash(const qint32& iID);
};

/**
 * @brief
 *
 */
class cEXIFTag
{
public:
	cEXIFTag(const qint32& iTAGID, const QString& szTAGName, const qint32& iIFDID, const qint32& iTypeID, const QString& szDescription);

	qint32		m_iTAGID; /**< TODO: describe */
	QString		m_szTAGName; /**< TODO: describe */
	qint32		m_iIFDID; /**< TODO: describe */
	qint32		m_iTypeID; /**< TODO: describe */
	QString		m_szDescription; /**< TODO: describe */
};

Q_DECLARE_METATYPE(cEXIFTag*)

/**
 * @brief
 *
 */
class cEXIFTagList : public QList<cEXIFTag*>
{
public:
	cEXIFTagList();

	/**
	 * @brief
	 *
	 * @param iTAGID
	 * @param szTAGName
	 * @param iIFDID
	 * @param iTypeID
	 * @param szDescription
	 * @return cEXIFTag
	 */
	cEXIFTag*		add(const qint32& iTAGID, const QString& szTAGName, const qint32& iIFDID, const qint32& iTypeID, const QString& szDescription);
	/**
	 * @brief
	 *
	 * @param iTAGID
	 * @param iIFDID
	 * @return cEXIFTag
	 */
	cEXIFTag*		find(const qint32& iTAGID, const qint32& iIFDID);
};

/**
 * @brief
 *
 */
class cEXIFValue
{
public:
	cEXIFValue(cEXIFTag* lpEXIFTag);

	/**
	 * @brief
	 *
	 * @return cEXIFTag
	 */
	cEXIFTag*		exifTag();
	/**
	 * @brief
	 *
	 * @param szValue
	 * @param iTypeId
	 * @param iCount
	 */
	void			setValue(const QString& szValue, qint32 iTypeId, qint32 iCount = 1);
	/**
	 * @brief
	 *
	 * @return QVariant
	 */
	QVariant		value();
	/**
	 * @brief
	 *
	 * @return QList<QVariant>
	 */
	QList<QVariant>	valueList();

private:
	cEXIFTag*		m_lpEXIFTag; /**< TODO: describe */
	QList<QVariant>	m_valueList; /**< TODO: describe */

	/**
	 * @brief
	 *
	 * @param szValue
	 * @param iTypeId
	 * @return QVariant
	 */
	QVariant		convertValue(const QString& szValue, qint32 iTypeId);
};

Q_DECLARE_METATYPE(cEXIFValue*)

/**
 * @brief
 *
 */
class cEXIFValueList : public QList<cEXIFValue*>
{
public:
	cEXIFValueList();

	/**
	 * @brief
	 *
	 * @param lpEXIFTag
	 * @return cEXIFValue
	 */
	cEXIFValue*		add(cEXIFTag* lpEXIFTag);
	/**
	 * @brief
	 *
	 * @param lpEXIFTag
	 * @return cEXIFValue
	 */
	cEXIFValue*		find(cEXIFTag* lpEXIFTag);
};

/**
 * @brief
 *
 */
class cEXIF
{
public:
	cEXIF(cEXIFTagList* lpEXIFTagList);

	/**
	 * @brief
	 *
	 * @param szFileName
	 * @return bool
	 */
	bool			fromFile(const QString& szFileName);

	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32			imageWidth();
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32			imageHeight();
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString			cameraMake();
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString			cameraModel();
	/**
	 * @brief
	 *
	 * @return QDateTime
	 */
	QDateTime		dateTime();
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString			fNumber();
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32			iso();
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString			flash();
	/**
	 * @brief
	 *
	 * @return qreal
	 */
	qreal			focalLength();
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString			lensMake();
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString			lensModel();
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString			exposureTime();
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32			exposureBias();
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString			exifVersion();
	/**
	 * @brief
	 *
	 * @return QDateTime
	 */
	QDateTime		dateTimeOriginal();
	/**
	 * @brief
	 *
	 * @return QDateTime
	 */
	QDateTime		dateTimeDigitized();
	/**
	 * @brief
	 *
	 * @return qint32
	 */
	qint32			whiteBalance();
	/**
	 * @brief
	 *
	 * @return qreal
	 */
	qreal			focalLength35();
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString			gps();
	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString			fileName();
	/**
	 * @brief
	 *
	 * @return QList<QImage>
	 */
	QList<QImage>	previewList();

private:
	cEXIFTagList*	m_lpEXIFTagList;	/**< TODO: describe */
	cEXIFValueList	m_exifValueList;	/**< TODO: describe */
	qint32			m_iWidth;			/**< TODO: describe */
	qint32			m_iHeight;			/**< TODO: describe */
	QString			m_szFileName;		/**< TODO: describe */
	QList<QImage>	m_previewList;		/**< TODO: describe */

	/**
	 * @brief
	 *
	 * @param iTAGID
	 * @param iIFDID
	 * @return QVariant
	 */
	QVariant		getTag(qint32 iTAGID, qint32 iIFDID);
	/**
	 * @brief
	 *
	 * @param iTAGID
	 * @param iIFDID
	 * @return QList<QVariant>
	 */
	QList<QVariant>	getTagList(qint32 iTAGID, qint32 iIFDID);
};

#endif // CEXIF_H
