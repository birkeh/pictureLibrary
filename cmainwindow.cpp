#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QTextStream>


cMainWindow::cMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow)
{
	ui->setupUi(this);

	cEXIF	exif(&m_exifTagList);

	exif.fromFile("C:\\Users\\VET0572\\Pictures\\IMG_1371.CR2");
	qDebug() << "===========================================================================";
	qDebug() << exif.fileName();
	qDebug() << "---------------------------------------------------------------------------";
	qDebug() << "ImageWidth: " << exif.imageWidth();
	qDebug() << "ImageHeight: " << exif.imageHeight();
	qDebug() << "Make: " << exif.cameraMake();
	qDebug() << "Model: " << exif.cameraModel();
	qDebug() << "DateTime: " << exif.dateTime();
	qDebug() << "FNumber: " << exif.fNumber();
	qDebug() << "ISOSpeedRatings: " << exif.iso();
	qDebug() << "Flash: " << exif.flash();
	qDebug() << "FocalLength: " << exif.focalLength();
	qDebug() << "LensMake: " << exif.lensMake();
	qDebug() << "LensModel: " << exif.lensModel();
	qDebug() << "ExposureTime: " << exif.exposureTime();
	qDebug() << "ExposureBias: " << exif.exposureBias();
	qDebug() << "ExifVersion: " << exif.exifVersion();
	qDebug() << "DateTimeOriginal: " << exif.dateTimeOriginal();
	qDebug() << "DateTimeDigitized: " << exif.dateTimeDigitized();
	qDebug() << "WhiteBalance: " << exif.whiteBalance();
	qDebug() << "FocalLengthIn35mmFilm: " << exif.focalLength35();
	qDebug() << "GPS: " << exif.gps();

	exif.fromFile("C:\\Users\\VET0572\\Pictures\\IMG_1372.CR2");
	qDebug() << "===========================================================================";
	qDebug() << exif.fileName();
	qDebug() << "---------------------------------------------------------------------------";
	qDebug() << "ImageWidth: " << exif.imageWidth();
	qDebug() << "ImageHeight: " << exif.imageHeight();
	qDebug() << "Make: " << exif.cameraMake();
	qDebug() << "Model: " << exif.cameraModel();
	qDebug() << "DateTime: " << exif.dateTime();
	qDebug() << "FNumber: " << exif.fNumber();
	qDebug() << "ISOSpeedRatings: " << exif.iso();
	qDebug() << "Flash: " << exif.flash();
	qDebug() << "FocalLength: " << exif.focalLength();
	qDebug() << "LensMake: " << exif.lensMake();
	qDebug() << "LensModel: " << exif.lensModel();
	qDebug() << "ExposureTime: " << exif.exposureTime();
	qDebug() << "ExposureBias: " << exif.exposureBias();
	qDebug() << "ExifVersion: " << exif.exifVersion();
	qDebug() << "DateTimeOriginal: " << exif.dateTimeOriginal();
	qDebug() << "DateTimeDigitized: " << exif.dateTimeDigitized();
	qDebug() << "WhiteBalance: " << exif.whiteBalance();
	qDebug() << "FocalLengthIn35mmFilm: " << exif.focalLength35();
	qDebug() << "GPS: " << exif.gps();

	exif.fromFile("C:\\Users\\VET0572\\Pictures\\IMG_1373.CR2");
	qDebug() << "===========================================================================";
	qDebug() << exif.fileName();
	qDebug() << "---------------------------------------------------------------------------";
	qDebug() << "ImageWidth: " << exif.imageWidth();
	qDebug() << "ImageHeight: " << exif.imageHeight();
	qDebug() << "Make: " << exif.cameraMake();
	qDebug() << "Model: " << exif.cameraModel();
	qDebug() << "DateTime: " << exif.dateTime();
	qDebug() << "FNumber: " << exif.fNumber();
	qDebug() << "ISOSpeedRatings: " << exif.iso();
	qDebug() << "Flash: " << exif.flash();
	qDebug() << "FocalLength: " << exif.focalLength();
	qDebug() << "LensMake: " << exif.lensMake();
	qDebug() << "LensModel: " << exif.lensModel();
	qDebug() << "ExposureTime: " << exif.exposureTime();
	qDebug() << "ExposureBias: " << exif.exposureBias();
	qDebug() << "ExifVersion: " << exif.exifVersion();
	qDebug() << "DateTimeOriginal: " << exif.dateTimeOriginal();
	qDebug() << "DateTimeDigitized: " << exif.dateTimeDigitized();
	qDebug() << "WhiteBalance: " << exif.whiteBalance();
	qDebug() << "FocalLengthIn35mmFilm: " << exif.focalLength35();
	qDebug() << "GPS: " << exif.gps();

	exif.fromFile("C:\\Users\\VET0572\\Pictures\\IMG_3444.CR2");
	qDebug() << "===========================================================================";
	qDebug() << exif.fileName();
	qDebug() << "---------------------------------------------------------------------------";
	qDebug() << "ImageWidth: " << exif.imageWidth();
	qDebug() << "ImageHeight: " << exif.imageHeight();
	qDebug() << "Make: " << exif.cameraMake();
	qDebug() << "Model: " << exif.cameraModel();
	qDebug() << "DateTime: " << exif.dateTime();
	qDebug() << "FNumber: " << exif.fNumber();
	qDebug() << "ISOSpeedRatings: " << exif.iso();
	qDebug() << "Flash: " << exif.flash();
	qDebug() << "FocalLength: " << exif.focalLength();
	qDebug() << "LensMake: " << exif.lensMake();
	qDebug() << "LensModel: " << exif.lensModel();
	qDebug() << "ExposureTime: " << exif.exposureTime();
	qDebug() << "ExposureBias: " << exif.exposureBias();
	qDebug() << "ExifVersion: " << exif.exifVersion();
	qDebug() << "DateTimeOriginal: " << exif.dateTimeOriginal();
	qDebug() << "DateTimeDigitized: " << exif.dateTimeDigitized();
	qDebug() << "WhiteBalance: " << exif.whiteBalance();
	qDebug() << "FocalLengthIn35mmFilm: " << exif.focalLength35();
	qDebug() << "GPS: " << exif.gps();

	exif.fromFile("C:\\Users\\VET0572\\OneDrive - WINDESIGN\\exif-samples-master\\jpg\\Fujifilm_FinePix6900ZOOM.jpg");
	qDebug() << "===========================================================================";
	qDebug() << exif.fileName();
	qDebug() << "---------------------------------------------------------------------------";
	qDebug() << "ImageWidth: " << exif.imageWidth();
	qDebug() << "ImageHeight: " << exif.imageHeight();
	qDebug() << "Make: " << exif.cameraMake();
	qDebug() << "Model: " << exif.cameraModel();
	qDebug() << "DateTime: " << exif.dateTime();
	qDebug() << "FNumber: " << exif.fNumber();
	qDebug() << "ISOSpeedRatings: " << exif.iso();
	qDebug() << "Flash: " << exif.flash();
	qDebug() << "FocalLength: " << exif.focalLength();
	qDebug() << "LensMake: " << exif.lensMake();
	qDebug() << "LensModel: " << exif.lensModel();
	qDebug() << "ExposureTime: " << exif.exposureTime();
	qDebug() << "ExposureBias: " << exif.exposureBias();
	qDebug() << "ExifVersion: " << exif.exifVersion();
	qDebug() << "DateTimeOriginal: " << exif.dateTimeOriginal();
	qDebug() << "DateTimeDigitized: " << exif.dateTimeDigitized();
	qDebug() << "WhiteBalance: " << exif.whiteBalance();
	qDebug() << "FocalLengthIn35mmFilm: " << exif.focalLength35();
	qDebug() << "GPS: " << exif.gps();

	exif.fromFile("C:\\Users\\VET0572\\OneDrive - WINDESIGN\\20181123_125857.jpg");
	qDebug() << "===========================================================================";
	qDebug() << exif.fileName();
	qDebug() << "---------------------------------------------------------------------------";
	qDebug() << "ImageWidth: " << exif.imageWidth();
	qDebug() << "ImageHeight: " << exif.imageHeight();
	qDebug() << "Make: " << exif.cameraMake();
	qDebug() << "Model: " << exif.cameraModel();
	qDebug() << "DateTime: " << exif.dateTime();
	qDebug() << "FNumber: " << exif.fNumber();
	qDebug() << "ISOSpeedRatings: " << exif.iso();
	qDebug() << "Flash: " << exif.flash();
	qDebug() << "FocalLength: " << exif.focalLength();
	qDebug() << "LensMake: " << exif.lensMake();
	qDebug() << "LensModel: " << exif.lensModel();
	qDebug() << "ExposureTime: " << exif.exposureTime();
	qDebug() << "ExposureBias: " << exif.exposureBias();
	qDebug() << "ExifVersion: " << exif.exifVersion();
	qDebug() << "DateTimeOriginal: " << exif.dateTimeOriginal();
	qDebug() << "DateTimeDigitized: " << exif.dateTimeDigitized();
	qDebug() << "WhiteBalance: " << exif.whiteBalance();
	qDebug() << "FocalLengthIn35mmFilm: " << exif.focalLength35();
	qDebug() << "GPS: " << exif.gps();

	qDebug() << "done";
}

cMainWindow::~cMainWindow()
{
	delete ui;
}
