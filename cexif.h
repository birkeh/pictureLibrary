#ifndef CEXIF_H
#define CEXIF_H

#include <QString>
#include <QVariant>
#include <QDateTime>

#include <QMetaType>
#include <QList>


class cEXIFCompression
{
public:
	cEXIFCompression(const qint32& iID, const QString& szCompression);

	qint32		m_iID;
	QString		m_szCompression;
};

Q_DECLARE_METATYPE(cEXIFCompression*)

class cEXIFCompressionList : public QList<cEXIFCompression*>
{
public:
	cEXIFCompressionList();

	cEXIFCompression*	add(const qint32& iID, const QString& szCompression);
	cEXIFCompression*	find(const qint32& iID);

	QString				compression(const qint32& iID);
};

Q_DECLARE_METATYPE(cEXIFCompressionList)

class cEXIFLightSource
{
public:
	cEXIFLightSource(const qint32& iID, const QString& szLightSource);

	qint32		m_iID;
	QString		m_szLightSource;
};

Q_DECLARE_METATYPE(cEXIFLightSource*)

class cEXIFLightSourceList : public QList<cEXIFLightSource*>
{
public:
	cEXIFLightSourceList();

	cEXIFLightSource*	add(const qint32& iID, const QString& szLightSource);
	cEXIFLightSource*	find(const qint32& iID);

	QString			lightSource(const qint32& iID);
};

class cEXIFFlash
{
public:
	cEXIFFlash(const qint32& iID, const QString& szFlash);

	qint32		m_iID;
	QString		m_szFlash;
};

Q_DECLARE_METATYPE(cEXIFFlash*)

class cEXIFFlashList : public QList<cEXIFFlash*>
{
public:
	cEXIFFlashList();

	cEXIFFlash*		add(const qint32& iID, const QString& szFlash);
	cEXIFFlash*		find(const qint32& iID);

	QString			flash(const qint32& iID);
};

class cEXIFTag
{
public:
	cEXIFTag(const qint32& iTAGID, const QString& szTAGName, const qint32& iIFDID, const qint32& iTypeID, const QString& szDescription);

	qint32		m_iTAGID;
	QString		m_szTAGName;
	qint32		m_iIFDID;
	qint32		m_iTypeID;
	QString		m_szDescription;
};

Q_DECLARE_METATYPE(cEXIFTag*)

class cEXIFTagList : public QList<cEXIFTag*>
{
public:
	cEXIFTagList();

	cEXIFTag*		add(const qint32& iTAGID, const QString& szTAGName, const qint32& iIFDID, const qint32& iTypeID, const QString& szDescription);
	cEXIFTag*		find(const qint32& iTAGID, const qint32& iIFDID);
};

class cEXIFValue
{
public:
	cEXIFValue(cEXIFTag* lpEXIFTag);

	cEXIFTag*		exifTag();
	void			setValue(const QString& szValue, qint32 iTypeId, qint32 iCount = 1);
	QVariant		value();
	QList<QVariant>	valueList();

private:
	cEXIFTag*		m_lpEXIFTag;
	QList<QVariant>	m_valueList;

	QVariant		convertValue(const QString& szValue, qint32 iTypeId);
};

Q_DECLARE_METATYPE(cEXIFValue*)

class cEXIFValueList : public QList<cEXIFValue*>
{
public:
	cEXIFValueList();

	cEXIFValue*		add(cEXIFTag* lpEXIFTag);
	cEXIFValue*		find(cEXIFTag* lpEXIFTag);
};

class cEXIF
{
public:
	cEXIF(cEXIFTagList* lpEXIFTagList);

	bool			fromFile(const QString& szFileName);

	qint32			imageWidth();
	qint32			imageHeight();
	QString			cameraMake();
	QString			cameraModel();
	QDateTime		dateTime();
	QString			fNumber();
	qint32			iso();
	QString			flash();
	qreal			focalLength();
	QString			lensMake();
	QString			lensModel();
	QString			exposureTime();
	qint32			exposureBias();
	QString			exifVersion();
	QDateTime		dateTimeOriginal();
	QDateTime		dateTimeDigitized();
	qint32			whiteBalance();
	qreal			focalLength35();
	QString			gps();
	QString			fileName();

private:
	cEXIFTagList*	m_lpEXIFTagList;
	cEXIFValueList	m_exifValueList;
	qint32			m_iWidth;
	qint32			m_iHeight;
	QString			m_szFileName;

	QVariant		getTag(qint32 iTAGID, qint32 iIFDID);
	QList<QVariant>	getTagList(qint32 iTAGID, qint32 iIFDID);
};

#endif // CEXIF_H
