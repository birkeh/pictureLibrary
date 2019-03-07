/*!
 \file cpicture.cpp

*/

#include "common.h"

#include "cexif.h"
#include "cpicture.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>

#include <QApplication>


cPicture::cPicture(qint32 iID, QObject *parent) :
	QObject(parent),
	m_iID(iID),
	m_szFileName(""),
	m_szFilePath(""),
	m_iFileSize(0),
	m_szTitle(""),
	m_mimeType(""),
	m_imageWidth(0),
	m_imageHeight(0),
	m_cameraMake(""),
	m_cameraModel(""),
	m_fNumber(""),
	m_iso(0),
	m_flash(""),
	m_flashID(0),
	m_focalLength(0.0),
	m_lensMake(""),
	m_lensModel(""),
	m_exposureTime(""),
	m_exposureBias(0),
	m_exifVersion(""),
	m_whiteBalance(0),
	m_focalLength35(0.0),
	m_gps(""),
	m_duration(0),
	m_hdr(false)
{
}

bool cPicture::fromFile(const QString& szFileName)
{
	cEXIF		exif;
	QFileInfo	fileInfo(szFileName);

	if(!exif.fromFile(szFileName))
		return(false);

	m_iID					= -1;

	m_szFileName			= fileInfo.fileName();
	m_szFilePath			= fileInfo.absolutePath();
	m_iFileSize				= fileInfo.size();
	m_thumbnail				= exif.thumbnail();
	m_mimeType				= exif.mimeType();
	m_imageWidth			= exif.imageWidth();
	m_imageHeight			= exif.imageHeight();
	m_imageOrientation		= exif.imageOrientation();
	m_cameraMake			= exif.cameraMake().simplified();
	m_cameraModel			= exif.cameraModel().simplified();
	m_dateTime				= exif.dateTime();
	m_fNumber				= exif.fNumber();
	m_iso					= exif.iso();
	m_flash					= exif.flash().simplified();
	m_flashID				= exif.flashID();
	m_focalLength			= exif.focalLength();
	m_lensMake				= exif.lensMake().simplified();
	m_lensModel				= exif.lensModel().simplified();
	m_exposureTime			= exif.exposureTime();
	m_exposureBias			= exif.exposureBias();
	m_exifVersion			= exif.exifVersion();
	m_dateTimeOriginal		= exif.dateTimeOriginal();
	m_dateTimeDigitized		= exif.dateTimeDigitized();
	m_whiteBalance			= exif.whiteBalance();
	m_focalLength35			= exif.focalLength35();
	m_gps					= exif.gps();
	m_duration				= exif.duration().toLongLong();

	return(true);
}

bool cPicture::toDB()
{
	QSqlQuery	query;

	if(m_iID != -1)
	{
		query.prepare("SELECT id FROM picture WHERE id=:id;");
		query.bindValue(":id", m_iID);
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			return(false);
		}

		if(!query.next())
			query.prepare("INSERT INTO picture (fileName, fileSize, title, mimeType, imageWidth, imageHeight, imageOrientation, cameraMake, cameraModel, dateTime, fNumber, iso, flashID, focalLength, lensMake, lensModel, exposureTime, exposureBias, exifVersion, dateTimeOriginal, dateTimeDigitized, whiteBalance, focalLength35, gps, duration, hdr, thumbnail) VALUES (:fileName, :fileSize, :title, :mimeType, :imageWidth, :imageHeight, :imageOrientation, :cameraMake, :cameraModel, :dateTime, :fNumber, :iso, :flashID, :focalLength, :lensMake, :lensModel, :exposureTime, :exposureBias, :exifVersion, :dateTimeOriginal, :dateTimeDigitized, :whiteBalance, :focalLength35, :gps, :duration, :hdr, :thumbnail);");
		else
			query.prepare("UPDATE picture SET fileName=:fileName, fileSize=:fileSize, title=:title, mimeType=:mimeType, imageWidth=:imageWidth, imageHeight=:imageHeight, imageOrientation=:imageOrientation, cameraMake=:cameraMake, cameraModel=:cameraModel, dateTime=:dateTime, fNumber=:fNumber, iso=:iso, flashID=:flashID, focalLength=:focalLength, lensMake=:lensMake, lensModel=:lensModel, exposureTime=:exposureTime, exposureBias=:exposureBias, exifVersion=:exifVersion, dateTimeOriginal=:dateTimeOriginal, dateTimeDigitized=:dateTimeDigitized, whiteBalance=:whiteBalance, focalLength35=:focalLength35, gps=:gps, duration=:duration, hdr=:hdr, thumbnail=:thumbnail WHERE id=:id;");
	}
	else
		query.prepare("INSERT INTO picture (fileName, fileSize, title, mimeType, imageWidth, imageHeight, imageOrientation, cameraMake, cameraModel, dateTime, fNumber, iso, flashID, focalLength, lensMake, lensModel, exposureTime, exposureBias, exifVersion, dateTimeOriginal, dateTimeDigitized, whiteBalance, focalLength35, gps, duration, hdr, thumbnail) VALUES (:fileName, :fileSize, :title, :mimeType, :imageWidth, :imageHeight, :imageOrientation, :cameraMake, :cameraModel, :dateTime, :fNumber, :iso, :flashID, :focalLength, :lensMake, :lensModel, :exposureTime, :exposureBias, :exifVersion, :dateTimeOriginal, :dateTimeDigitized, :whiteBalance, :focalLength35, :gps, :duration, :hdr, :thumbnail);");


	query.bindValue(":id",					m_iID);
	query.bindValue(":fileName",			m_szFileName);
	query.bindValue(":fileSize",			m_iFileSize);
	query.bindValue(":title",				m_szTitle);
	query.bindValue(":mimeType",			m_mimeType);
	query.bindValue(":imageWidth",			m_imageWidth);
	query.bindValue(":imageHeight",			m_imageHeight);
	query.bindValue(":imageOrientation",	m_imageOrientation);
	query.bindValue(":cameraMake",			m_cameraMake);
	query.bindValue(":cameraModel",			m_cameraModel);
	query.bindValue(":dateTime",			m_dateTime);
	query.bindValue(":fNumber",				m_fNumber);
	query.bindValue(":iso",					m_iso);
	query.bindValue(":flashID",				m_flashID);
	query.bindValue(":focalLength",			m_focalLength);
	query.bindValue(":lensMake",			m_lensMake);
	query.bindValue(":lensModel",			m_lensModel);
	query.bindValue(":exposureTime",		m_exposureTime);
	query.bindValue(":exposureBias",		m_exposureBias);
	query.bindValue(":exifVersion",			m_exifVersion);
	query.bindValue(":dateTimeOriginal",	m_dateTimeOriginal);
	query.bindValue(":dateTimeDigitized",	m_dateTimeDigitized);
	query.bindValue(":whiteBalance",		m_whiteBalance);
	query.bindValue(":focalLength35",		m_focalLength35);
	query.bindValue(":gps",					m_gps);
	query.bindValue(":duration",			m_duration);
	query.bindValue(":hdr",					m_hdr);
	if(!m_thumbnail.isNull())
		query.bindValue(":thumbnail", image2Blob(m_thumbnail));
	else
		query.bindValue(":thumbnail", QVariant(QVariant::ByteArray));

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	if(m_iID == -1)
	{
		query.prepare("SELECT id FROM picture WHERE _rowid_=(SELECT MAX(_rowid_) FROM picture);");
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			return(false);
		}

		query.next();
		m_iID	= query.value("id").toInt();
	}

	return(true);
}

void cPicture::setID(const qint32& id)
{
	m_iID	= id;
}

qint32 cPicture::id()
{
	return(m_iID);
}

void cPicture::setTitle(const QString &title)
{
	m_szTitle	= title;
}

QString cPicture::title()
{
	return(m_szTitle);
}

void cPicture::setMimeType(const QString &mimeType)
{
	m_mimeType	= mimeType;
}

QString cPicture::mimeType()
{
	return(m_mimeType);
}

void cPicture::setImageWidth(const qint32& imageWidth)
{
	m_imageWidth	= imageWidth;
}

qint32 cPicture::imageWidth()
{
	return(m_imageWidth);
}

void cPicture::setImageHeight(const qint32& imageHeight)
{
	m_imageHeight	= imageHeight;
}

qint32 cPicture::imageHeight()
{
	return(m_imageHeight);
}

void cPicture::setImageOrientation(const qint16& imageOrientation)
{
	m_imageOrientation	= imageOrientation;
}

qint16 cPicture::imageOrientation()
{
	return(m_imageOrientation);
}

void cPicture::setCameraMake(const QString& cameraMake)
{
	m_cameraMake	= cameraMake;
}

QString cPicture::cameraMake()
{
	return(m_cameraMake);
}

void cPicture::setCameraModel(const QString& cameraModel)
{
	m_cameraModel	= cameraModel;
}

QString cPicture::cameraModel()
{
	return(m_cameraModel);
}

void cPicture::setDateTime(const QDateTime& dateTime)
{
	m_dateTime	 = dateTime;
}

QDateTime cPicture::dateTime()
{
	return(m_dateTime);
}

void cPicture::setFNumber(const QString& fNumber)
{
	m_fNumber	= fNumber;
}

QString cPicture::fNumber()
{
	return(m_fNumber);
}

void cPicture::setISO(const qint32& iso)
{
	m_iso	= iso;
}

qint32 cPicture::iso()
{
	return(m_iso);
}

void cPicture::setFlash(const QString& flash)
{
	m_flash	= flash;
}

QString cPicture::flash()
{
	return(m_flash);
}

void cPicture::setFlashID(const qint32& flashID)
{
	m_flashID	= flashID;
}

qint32 cPicture::flashID()
{
	return(m_flashID);
}

void cPicture::setFocalLength(const qreal& focalLength)
{
	m_focalLength	= focalLength;
}

qreal cPicture::focalLength()
{
	return(m_focalLength);
}

void cPicture::setLensMake(const QString& lensMake)
{
	m_lensMake	= lensMake;
}

QString cPicture::lensMake()
{
	return(m_lensMake);
}

void cPicture::setLensModel(const QString& lensModel)
{
	m_lensModel	= lensModel;
}

QString cPicture::lensModel()
{
	return(m_lensModel);
}

void cPicture::setExposureTime(const QString& exposureTime)
{
	m_exposureTime	= exposureTime;
}

QString cPicture::exposureTime()
{
	return(m_exposureTime);
}

void cPicture::setExposureBias(const qint32& exposureBias)
{
	m_exposureBias	= exposureBias;
}

qint32 cPicture::exposureBias()
{
	return(m_exposureBias);
}

void cPicture::setExifVersion(const QString& exifVersion)
{
	m_exifVersion	= exifVersion;
}

QString cPicture::exifVersion()
{
	return(m_exifVersion);
}

void cPicture::setDateTimeOriginal(const QDateTime& dateTimeOriginal)
{
	m_dateTimeOriginal	= dateTimeOriginal;
}

QDateTime cPicture::dateTimeOriginal()
{
	return(m_dateTimeOriginal);
}

void cPicture::setDateTimeDigitized(const QDateTime& dateTimeDigitized)
{
	m_dateTimeDigitized	= dateTimeDigitized;
}

QDateTime cPicture::dateTimeDigitized()
{
	return(m_dateTimeDigitized);
}

void cPicture::setWhiteBalance(const qint32& whiteBalance)
{
	m_whiteBalance	= whiteBalance;
}

qint32 cPicture::whiteBalance()
{
	return(m_whiteBalance);
}

void cPicture::setFocalLength35(const qreal& focalLength35)
{
	m_focalLength35	= focalLength35;
}

qreal cPicture::focalLength35()
{
	return(m_focalLength35);
}

void cPicture::setGPS(const QString& gps)
{
	m_gps	= gps;
}

QString cPicture::gps()
{
	return(m_gps);
}

void cPicture::setDuration(const qint64& duration)
{
	m_duration	= duration;
}

qint64 cPicture::duration()
{
	return(m_duration);
}

void cPicture::setHDR(const bool& hdr)
{
	m_hdr	= hdr;
}

bool cPicture::hdr()
{
	return(m_hdr);
}

void cPicture::setFileName(const QString& fileName)
{
	m_szFileName	= fileName;
}

QString cPicture::fileName()
{
	return(m_szFileName);
}

void cPicture::setFilePath(const QString& filePath)
{
	m_szFilePath	= filePath;
}

QString cPicture::filePath()
{
	return(m_szFilePath);
}

void cPicture::setFileSize(const qint64& fileSize)
{
	m_iFileSize	= fileSize;
}

qint64 cPicture::fileSize()
{
	return(m_iFileSize);
}

void cPicture::setThumbnail(const QImage& thumbnail)
{
	m_thumbnail	= thumbnail;
}

QImage cPicture::thumbnail()
{
	return(m_thumbnail);
}

bool cPicture::operator==(const cPicture& other) const
{
	if(this->m_szFileName != other.m_szFileName)
		return(false);
	if(this->m_iFileSize != other.m_iFileSize)
		return(false);
	if(this->m_szTitle != other.m_szTitle)
		return(false);
	if(this->m_mimeType != other.m_mimeType)
		return(false);
	if(this->m_imageWidth != other.m_imageWidth)
		return(false);
	if(this->m_imageHeight != other.m_imageHeight)
		return(false);
	if(this->m_imageOrientation != other.m_imageOrientation)
		return(false);
	if(this->m_cameraMake != other.m_cameraMake)
			return(false);
	if(this->m_cameraModel != other.m_cameraModel)
	   return(false);
	if(this->m_dateTime != other.m_dateTime)
	   return(false);
	if(this->m_fNumber != other.m_fNumber)
	   return(false);
	if(this->m_iso != other.m_iso)
	   return(false);
	if(this->m_flashID != other.m_flashID)
	   return(false);
	if(this->m_focalLength != other.m_focalLength)
	   return(false);
	if(this->m_lensMake != other.m_lensMake)
	   return(false);
	if(this->m_lensModel != other.m_lensModel)
	   return(false);
	if(this->m_exposureTime != other.m_exposureTime)
	   return(false);
	if(this->m_exposureBias != other.m_exposureBias)
	   return(false);
	if(this->m_exifVersion != other.m_exifVersion)
	   return(false);
	if(this->m_dateTimeOriginal != other.m_dateTimeOriginal)
	   return(false);
	if(this->m_dateTimeDigitized != other.m_dateTimeDigitized)
	   return(false);
	if(this->m_whiteBalance != other.m_whiteBalance)
	   return(false);
	if(this->m_focalLength35 != other.m_focalLength35)
	   return(false);
	if(this->m_gps != other.m_gps)
	   return(false);
	if(this->m_duration != other.m_duration)
		return(false);

	return(true);
}

bool cPicture::operator==(const cPicture*& other) const
{
	if(this->m_szFileName != other->m_szFileName)
		return(false);
	if(this->m_iFileSize != other->m_iFileSize)
		return(false);
	if(this->m_szTitle != other->m_szTitle)
		return(false);
	if(this->m_mimeType != other->m_mimeType)
		return(false);
	if(this->m_imageWidth != other->m_imageWidth)
		return(false);
	if(this->m_imageHeight != other->m_imageHeight)
		return(false);
	if(this->m_imageOrientation != other->m_imageOrientation)
		return(false);
	if(this->m_cameraMake != other->m_cameraMake)
			return(false);
	if(this->m_cameraModel != other->m_cameraModel)
	   return(false);
	if(this->m_dateTime != other->m_dateTime)
	   return(false);
	if(this->m_fNumber != other->m_fNumber)
	   return(false);
	if(this->m_iso != other->m_iso)
	   return(false);
	if(this->m_flashID != other->m_flashID)
	   return(false);
	if(this->m_focalLength != other->m_focalLength)
	   return(false);
	if(this->m_lensMake != other->m_lensMake)
	   return(false);
	if(this->m_lensModel != other->m_lensModel)
	   return(false);
	if(this->m_exposureTime != other->m_exposureTime)
	   return(false);
	if(this->m_exposureBias != other->m_exposureBias)
	   return(false);
	if(this->m_exifVersion != other->m_exifVersion)
	   return(false);
	if(this->m_dateTimeOriginal != other->m_dateTimeOriginal)
	   return(false);
	if(this->m_dateTimeDigitized != other->m_dateTimeDigitized)
	   return(false);
	if(this->m_whiteBalance != other->m_whiteBalance)
	   return(false);
	if(this->m_focalLength35 != other->m_focalLength35)
	   return(false);
	if(this->m_gps != other->m_gps)
	   return(false);
	if(this->m_duration != other->m_duration)
		return(false);

	return(true);
}

bool cPicture::operator==(const cPicture* other) const
{
	if(this->m_szFileName != other->m_szFileName)
		return(false);
	if(this->m_iFileSize != other->m_iFileSize)
		return(false);
	if(this->m_szTitle != other->m_szTitle)
		return(false);
	if(this->m_mimeType != other->m_mimeType)
		return(false);
	if(this->m_imageWidth != other->m_imageWidth)
		return(false);
	if(this->m_imageHeight != other->m_imageHeight)
		return(false);
	if(this->m_imageOrientation != other->m_imageOrientation)
		return(false);
	if(this->m_cameraMake != other->m_cameraMake)
			return(false);
	if(this->m_cameraModel != other->m_cameraModel)
	   return(false);
	if(this->m_dateTime != other->m_dateTime)
	   return(false);
	if(this->m_fNumber != other->m_fNumber)
	   return(false);
	if(this->m_iso != other->m_iso)
	   return(false);
	if(this->m_flashID != other->m_flashID)
	   return(false);
	if(this->m_focalLength != other->m_focalLength)
	   return(false);
	if(this->m_lensMake != other->m_lensMake)
	   return(false);
	if(this->m_lensModel != other->m_lensModel)
	   return(false);
	if(this->m_exposureTime != other->m_exposureTime)
	   return(false);
	if(this->m_exposureBias != other->m_exposureBias)
	   return(false);
	if(this->m_exifVersion != other->m_exifVersion)
	   return(false);
	if(this->m_dateTimeOriginal != other->m_dateTimeOriginal)
	   return(false);
	if(this->m_dateTimeDigitized != other->m_dateTimeDigitized)
	   return(false);
	if(this->m_whiteBalance != other->m_whiteBalance)
	   return(false);
	if(this->m_focalLength35 != other->m_focalLength35)
	   return(false);
	if(this->m_gps != other->m_gps)
	   return(false);
	if(this->m_duration != other->m_duration)
		return(false);

	return(true);
}

bool cPicture::operator==(cPicture* other)
{
	if(this->m_szFileName != other->m_szFileName)
		return(false);
	if(this->m_iFileSize != other->m_iFileSize)
		return(false);
	if(this->m_szTitle != other->m_szTitle)
		return(false);
	if(this->m_mimeType != other->m_mimeType)
		return(false);
	if(this->m_imageWidth != other->m_imageWidth)
		return(false);
	if(this->m_imageHeight != other->m_imageHeight)
		return(false);
	if(this->m_imageOrientation != other->m_imageOrientation)
		return(false);
	if(this->m_cameraMake != other->m_cameraMake)
			return(false);
	if(this->m_cameraModel != other->m_cameraModel)
	   return(false);
	if(this->m_dateTime != other->m_dateTime)
	   return(false);
	if(this->m_fNumber != other->m_fNumber)
	   return(false);
	if(this->m_iso != other->m_iso)
	   return(false);
	if(this->m_flashID != other->m_flashID)
	   return(false);
	if(this->m_focalLength != other->m_focalLength)
	   return(false);
	if(this->m_lensMake != other->m_lensMake)
	   return(false);
	if(this->m_lensModel != other->m_lensModel)
	   return(false);
	if(this->m_exposureTime != other->m_exposureTime)
	   return(false);
	if(this->m_exposureBias != other->m_exposureBias)
	   return(false);
	if(this->m_exifVersion != other->m_exifVersion)
	   return(false);
	if(this->m_dateTimeOriginal != other->m_dateTimeOriginal)
	   return(false);
	if(this->m_dateTimeDigitized != other->m_dateTimeDigitized)
	   return(false);
	if(this->m_whiteBalance != other->m_whiteBalance)
	   return(false);
	if(this->m_focalLength35 != other->m_focalLength35)
	   return(false);
	if(this->m_gps != other->m_gps)
	   return(false);
	if(this->m_duration != other->m_duration)
		return(false);

	return(true);
}

cPictureList::cPictureList(QObject *parent) :
	QObject(parent)
{
}

bool cPictureList::load(cSplashScreen *lpSplashScreen, QProgressBar *lpProgressBar)
{
	cEXIFFlashList	flashList;
	QSqlQuery		query;

	query.prepare("SELECT	COUNT(1) cnt FROM picture;");

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}
	query.next();

	qint32	max		= static_cast<qint32>(query.value("cnt").toLongLong());

	if(lpProgressBar)
		lpProgressBar->setMaximum(max);
	else if(lpSplashScreen)
		lpSplashScreen->setMax(max);

	query.prepare("SELECT   id, "
				  "         fileName, "
				  "         fileSize, "
				  "         title, "
				  "         mimeType, "
				  "         imageWidth, "
				  "         imageHeight, "
				  "         imageOrientation, "
				  "         cameraMake, "
				  "         cameraModel, "
				  "         dateTime, "
				  "         fNumber, "
				  "         iso, "
				  "         flashID, "
				  "         focalLength, "
				  "         lensMake, "
				  "         lensModel, "
				  "         exposureTime, "
				  "         exposureBias, "
				  "         exifVersion, "
				  "         dateTimeOriginal, "
				  "         dateTimeDigitized, "
				  "         whiteBalance, "
				  "         focalLength35, "
				  "         gps, "
				  "         duration, "
				  "         hdr, "
				  "         thumbnail "
				  "FROM     picture "
				  "ORDER BY dateTime, "
				  "         UPPER(fileName);");

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	qint32	count	= 0;
	qint32	step	= max/200;

	if(!step)
		step = 1;

	while(query.next())
	{
		cPicture*	lpPicture	= add(query.value("id").toInt(), true);
		lpPicture->setFileName(query.value("fileName").toString());
		lpPicture->setFileSize(query.value("fileSize").toLongLong());
		lpPicture->setTitle(query.value("title").toString());
		lpPicture->setMimeType(query.value("mimeType").toString());
		lpPicture->setImageWidth(query.value("imageWidth").toInt());
		lpPicture->setImageHeight(query.value("imageHeight").toInt());
		lpPicture->setImageOrientation(static_cast<qint16>(query.value("imageOrientation").toInt()));
		lpPicture->setCameraMake(query.value("cameraMake").toString());
		lpPicture->setCameraModel(query.value("cameraModel").toString());
		lpPicture->setDateTime(query.value("dateTime").toDateTime());
		lpPicture->setFNumber(query.value("fNumber").toString());
		lpPicture->setISO(query.value("iso").toInt());
		lpPicture->setFlashID(query.value("flashID").toInt());
		lpPicture->setFlash(flashList.flash(query.value("flashID").toInt()));
		lpPicture->setFocalLength(query.value("focalLength").toDouble());
		lpPicture->setLensMake(query.value("lensMake").toString());
		lpPicture->setLensModel(query.value("lensModel").toString());
		lpPicture->setExposureTime(query.value("exposureTime").toString());
		lpPicture->setExposureBias(query.value("exposureBias").toInt());
		lpPicture->setExifVersion(query.value("exifVersion").toString());
		lpPicture->setDateTimeOriginal(query.value("dateTimeOriginal").toDateTime());
		lpPicture->setDateTimeDigitized(query.value("dateTimeDigitized").toDateTime());
		lpPicture->setWhiteBalance(query.value("whiteBalance").toInt());
		lpPicture->setFocalLength35(query.value("focalLength35").toDouble());
		lpPicture->setGPS(query.value("gps").toString());
		lpPicture->setDuration(query.value("duration").toLongLong());
		lpPicture->setHDR(query.value("hdr").toBool());
		lpPicture->setThumbnail(blob2Image(query.value("thumbnail").toByteArray()));
		lpPicture->setFilePath(picture2Path(lpPicture));

		count++;
		if(!(count % step))
		{
			if(lpProgressBar)
				lpProgressBar->setValue(count);
			else if(lpSplashScreen)
				lpSplashScreen->setProgress(count);
			qApp->processEvents();
		}
	}

	return(true);
}

cPicture* cPictureList::add(qint32 iID, bool bNoCheck)
{
	if(iID != -1 && !bNoCheck)
	{
		if(find(iID))
			return(nullptr);
	}

	cPicture*	lpNew	= new cPicture(iID);
	append(lpNew);
	return(lpNew);
}

bool cPictureList::add(cPicture* lpPicture, bool bNoCheck)
{
	if(bNoCheck)
	{
		append(lpPicture);
		return(true);
	}

	if(contains(lpPicture))
		return(false);

	append(lpPicture);
	return(true);
}

cPicture* cPictureList::find(qint32 iID)
{
	for(int i = 0;i < count();i++)
	{
		if(at(i)->id() == iID)
			return(at(i));
	}
	return(nullptr);
}

cPicture* cPictureList::find(cPicture* lpPicture)
{
	for(int i = 0;i < count();i++)
	{
		if(*lpPicture == *at(i))
			return(at(i));
	}
	return(nullptr);
}

bool cPictureList::hasPath(const QString& szPath)
{
	for(int i = 0;i < count();i++)
	{
		if(at(i)->filePath() == szPath)
			return(true);
	}
	return(false);
}
