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
	m_gps("")
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
	m_imageWidth			= exif.imageWidth();
	m_imageHeight			= exif.imageHeight();
	m_imageOrientation		= exif.imageOrientation();
	m_cameraMake			= exif.cameraMake();
	m_cameraModel			= exif.cameraModel();
	m_dateTime				= exif.dateTime();
	m_fNumber				= exif.fNumber();
	m_iso					= exif.iso();
	m_flash					= exif.flash();
	m_flashID				= exif.flashID();
	m_focalLength			= exif.focalLength();
	m_lensMake				= exif.lensMake();
	m_lensModel				= exif.lensModel();
	m_exposureTime			= exif.exposureTime();
	m_exposureBias			= exif.exposureBias();
	m_exifVersion			= exif.exifVersion();
	m_dateTimeOriginal		= exif.dateTimeOriginal();
	m_dateTimeDigitized		= exif.dateTimeDigitized();
	m_whiteBalance			= exif.whiteBalance();
	m_focalLength35			= exif.focalLength35();
	m_gps					= exif.gps();

	return(true);
}

bool cPicture::toDB()
{
	QSqlQuery	query;

	if(m_iID != -1)
	{
		query.prepare("SELECT id FROM file WHERE id=:id;");
		query.bindValue(":id", m_iID);
		if(!query.exec())
		{
			myDebug << query.lastError().text();
			return(false);
		}

		if(!query.next())
			query.prepare("INSERT INTO picture (fileName, filePath, fileSize, imageWidth, imageHeight, imageOrientation, cameraMake, cameraModel, dateTime, fNumber, iso, flashID, focalLength, lensMake, lensModel, exposureTime, exposureBias, exifVersion, dateTimeOriginal, dateTimeDigitized, whiteBalance, focalLength35, gps, thumbnail) VALUES (:fileName, :filePath, :fileSize, :imageWidth, :imageHeight, :imageOrientation, :cameraMake, :cameraModel, :dateTime, :fNumber, :iso, :flashID, :focalLength, :lensMake, :lensModel, :exposureTime, :exposureBias, :exifVersion, :dateTimeOriginal, :dateTimeDigitized, :whiteBalance, :focalLength35, :gps, :thumbnail);");
		else
			query.prepare("UPDATE picture SET fileName=:fileName, filePath=:filePath, fileSize=:fileSize, imageWidth=:imageWidth, imageHeight=:imageHeight, imageOrientation=:imageOrientation, cameraMake=:cameraMake, cameraModel=:cameraModel, dateTime=:dateTime, fNumber=:fNumber, iso=:iso, flashID=:flashID, focalLength=:focalLength, lensMake=:lensMake, lensModel=:lensModel, exposureTime=:exposureTime, exposureBias=:exposureBias, exifVersion=:exifVersion, dateTimeOriginal=:dateTimeOriginal, dateTimeDigitized=:dateTimeDigitized, whiteBalance=:whiteBalance, focalLength35=:focalLength35, gps=:gps, thumbnail=:thumbnail WHERE id=:id;");
	}
	else
		query.prepare("INSERT INTO picture (fileName, filePath, fileSize, imageWidth, imageHeight, imageOrientation, cameraMake, cameraModel, dateTime, fNumber, iso, flashID, focalLength, lensMake, lensModel, exposureTime, exposureBias, exifVersion, dateTimeOriginal, dateTimeDigitized, whiteBalance, focalLength35, gps, thumbnail) VALUES (:fileName, :filePath, :fileSize, :imageWidth, :imageHeight, :imageOrientation, :cameraMake, :cameraModel, :dateTime, :fNumber, :iso, :flashID, :focalLength, :lensMake, :lensModel, :exposureTime, :exposureBias, :exifVersion, :dateTimeOriginal, :dateTimeDigitized, :whiteBalance, :focalLength35, :gps, :thumbnail);");


	query.bindValue(":id",					m_iID);
	query.bindValue(":fileName",			m_szFileName);
	query.bindValue(":filePath",			m_szFilePath);
	query.bindValue(":fileSize",			m_iFileSize);
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
				  "         filePath, "
				  "         fileSize, "
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
				  "         thumbnail "
				  "FROM     picture "
				  "ORDER BY filePath, "
				  "         UPPER(fileName);");

	if(!query.exec())
	{
		myDebug << query.lastError().text();
		return(false);
	}

	qint32	count	= 0;
	qint32	step	= max/200;

	while(query.next())
	{
		cPicture*	lpPicture	= add(query.value("id").toInt(), true);
		lpPicture->setFileName(query.value("fileName").toString());
		lpPicture->setFilePath(query.value("filePath").toString());
		lpPicture->setFileSize(query.value("fileSize").toLongLong());
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
		lpPicture->setThumbnail(blob2Image(query.value("thumbnail").toByteArray()));

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

cPicture* cPictureList::find(qint32 iID)
{
	for(int i = 0;i < count();i++)
	{
		if(at(i)->id() == iID)
			return(at(i));
	}
	return(nullptr);
}
