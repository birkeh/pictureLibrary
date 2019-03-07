/*!
 \file ctoolboxinfo.cpp

*/

#include "ctoolboxinfo.h"
#include "ui_ctoolboxinfo.h"

#include "common.h"


cToolBoxInfo::cToolBoxInfo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cToolBoxInfo)
{
	ui->setupUi(this);
}

cToolBoxInfo::~cToolBoxInfo()
{
	delete ui;
}

void cToolBoxInfo::setPicture(cPicture* lpPicture)
{
	if(!lpPicture)
	{
		ui->m_lpTitlePicture->setText("---");
		ui->m_lpFileNamePicture->setText("---");
		ui->m_lpPathPicture->setText("---");
		ui->m_lpDatePicture->setText("---");
		ui->m_lpSizePicture->setText("---");
		ui->m_lpHDRPicture->setText("---");
		ui->m_lpCameraPicture->setText("---");
		ui->m_lpLensModelPicture->setText("---");
		ui->m_lpFNumberPicture->setText("---");
		ui->m_lpExposureTimePicture->setText("---");
		ui->m_lpExposureBiasPicture->setText("---");
		ui->m_lpISOPicture->setText("---");
		ui->m_lpFocalLengthPicture->setText("---");
		ui->m_lpFlashPicture->setText("---");
		ui->m_lpGPSPicture->setText("---");

		ui->m_lpTitleVideo->setText("---");
		ui->m_lpFileNameVideo->setText("---");
		ui->m_lpPathVideo->setText("---");
		ui->m_lpDateVideo->setText("---");
		ui->m_lpSizeVideo->setText("---");
		ui->m_lpHDRVideo->setText("---");
		ui->m_lpCameraVideo->setText("---");
		ui->m_lpDurationVideo->setText("---");

		return;
	}

	if(lpPicture->mimeType().startsWith("image"))
	{
		ui->m_lpCategory->setCurrentIndex(0);

		ui->m_lpTitlePicture->setText(lpPicture->title());
		ui->m_lpFileNamePicture->setText(lpPicture->fileName());
		ui->m_lpPathPicture->setText(lpPicture->filePath());
		ui->m_lpDatePicture->setText(lpPicture->dateTime().toString());
		ui->m_lpSizePicture->setText(QString("%1x%2").arg(lpPicture->imageWidth()).arg(lpPicture->imageHeight()));
		ui->m_lpHDRPicture->setText(lpPicture->hdr() ? tr("yes") : tr("no"));
		ui->m_lpCameraPicture->setText(QString("%1 %2").arg(lpPicture->cameraMake()).arg(lpPicture->cameraModel()));
		ui->m_lpLensModelPicture->setText(lpPicture->lensModel());
		ui->m_lpFNumberPicture->setText("f 1:" + lpPicture->fNumber());
		ui->m_lpExposureTimePicture->setText(lpPicture->exposureTime());
		ui->m_lpExposureBiasPicture->setText(QString::number(lpPicture->exposureBias()));
		ui->m_lpISOPicture->setText(QString::number(lpPicture->iso()));
		ui->m_lpFocalLengthPicture->setText(QString("%1 mm").arg(lpPicture->focalLength()));
		ui->m_lpFlashPicture->setText(lpPicture->flash());
		ui->m_lpGPSPicture->setText(lpPicture->gps());
	}
	else
	{
		ui->m_lpCategory->setCurrentIndex(1);

		ui->m_lpTitleVideo->setText(lpPicture->title());
		ui->m_lpFileNameVideo->setText(lpPicture->fileName());
		ui->m_lpPathVideo->setText(lpPicture->filePath());
		ui->m_lpDateVideo->setText(lpPicture->dateTime().toString());
		ui->m_lpSizeVideo->setText(QString("%1x%2").arg(lpPicture->imageWidth()).arg(lpPicture->imageHeight()));
		ui->m_lpHDRVideo->setText(lpPicture->hdr() ? tr("yes") : tr("no"));
		ui->m_lpCameraVideo->setText(QString("%1 %2").arg(lpPicture->cameraMake()).arg(lpPicture->cameraModel()));
		ui->m_lpDurationVideo->setText(ms2String(lpPicture->duration()));
	}
}

void cToolBoxInfo::setPicture(QList<cPicture*> pictureList)
{
	cPicture*	lpPicture		= pictureList[0];
	QString		mimeType		= lpPicture->mimeType().left(lpPicture->mimeType().indexOf("/"));
	QString		title			= lpPicture->title();
	QString		fileName		= lpPicture->fileName();
	QString		filePath		= lpPicture->filePath();
	QDateTime	dateTime		= lpPicture->dateTime();
	qint32		imageWidth		= lpPicture->imageWidth();
	qint32		imageHeight		= lpPicture->imageHeight();
	int			hdr				= lpPicture->hdr() ? 1 : 0;
	QString		cameraMake		= lpPicture->cameraMake();
	QString		cameraModel		= lpPicture->cameraModel();
	QString		lensModel		= lpPicture->lensModel();
	QString		fNumber			= lpPicture->fNumber();
	QString		exposureTime	= lpPicture->exposureTime();
	qint32		exposureBias	= lpPicture->exposureBias();
	qint32		iso				= lpPicture->iso();
	qreal		focalLength		= lpPicture->focalLength();
	QString		flash			= lpPicture->flash();
	QString		gps				= lpPicture->gps();

	for(int x = 1;x < pictureList.count();x++)
	{
		lpPicture	= pictureList[x];

		if(mimeType != lpPicture->mimeType().left(lpPicture->mimeType().indexOf("/")))
		{
			mimeType = "---";
			break;
		}
		if(title != lpPicture->title())
			title = "---";
		if(fileName != lpPicture->fileName())
			fileName = "---";
		if(filePath != lpPicture->filePath())
			filePath = "---";
		if(dateTime != lpPicture->dateTime())
			dateTime = QDateTime();
		if(imageWidth != lpPicture->imageWidth())
			imageWidth = -1;
		if(imageHeight != lpPicture->imageHeight())
			imageHeight = -1;
		if(hdr != lpPicture->hdr())
			hdr = -1;
		if(cameraMake != lpPicture->cameraMake())
			cameraMake = "---";
		if(cameraModel != lpPicture->cameraModel())
			cameraModel = "---";
		if(lensModel != lpPicture->lensModel())
			lensModel = "---";
		if(fNumber != lpPicture->fNumber())
			fNumber = "---";
		if(exposureTime != lpPicture->exposureTime())
			exposureTime = "---";
		if(exposureBias != lpPicture->exposureBias())
			exposureBias = -1;
		if(iso != lpPicture->iso())
			iso = -1;
		if(focalLength != lpPicture->focalLength())
			focalLength = -1;
		if(flash != lpPicture->flash())
			flash = "---";
		if(gps != lpPicture->gps())
			gps = "---";
	}

	if(mimeType == "---")
	{
		ui->m_lpTitlePicture->setText("---");
		ui->m_lpFileNamePicture->setText("---");
		ui->m_lpPathPicture->setText("---");
		ui->m_lpDatePicture->setText("---");
		ui->m_lpSizePicture->setText("---");
		ui->m_lpHDRPicture->setText("---");
		ui->m_lpCameraPicture->setText("---");
		ui->m_lpLensModelPicture->setText("---");
		ui->m_lpFNumberPicture->setText("---");
		ui->m_lpExposureTimePicture->setText("---");
		ui->m_lpExposureBiasPicture->setText("---");
		ui->m_lpISOPicture->setText("---");
		ui->m_lpFocalLengthPicture->setText("---");
		ui->m_lpFlashPicture->setText("---");
		ui->m_lpGPSPicture->setText("---");

		ui->m_lpTitleVideo->setText("---");
		ui->m_lpFileNameVideo->setText("---");
		ui->m_lpPathVideo->setText("---");
		ui->m_lpDateVideo->setText("---");
		ui->m_lpSizeVideo->setText("---");
		ui->m_lpHDRVideo->setText("---");
		ui->m_lpCameraVideo->setText("---");
		ui->m_lpDurationVideo->setText("---");

		return;
	}

	if(mimeType.startsWith("image"))
	{
		ui->m_lpCategory->setCurrentIndex(0);

		ui->m_lpTitlePicture->setText(title);
		ui->m_lpFileNamePicture->setText(fileName);
		ui->m_lpPathPicture->setText(filePath);
		if(dateTime.isValid())
			ui->m_lpDatePicture->setText(dateTime.toString());
		else
			ui->m_lpDatePicture->setText("---");
		if(imageWidth == -1 || imageHeight == -1)
			ui->m_lpSizePicture->setText("---");
		else
			ui->m_lpSizePicture->setText(QString("%1x%2").arg(imageWidth).arg(imageHeight));
		if(hdr == -1)
			ui->m_lpHDRPicture->setText("---");
		else
			ui->m_lpHDRPicture->setText(hdr == 1 ? tr("yes") : tr("no"));
		if(cameraMake == "---" || cameraModel == "---")
			ui->m_lpCameraPicture->setText("---");
		else
			ui->m_lpCameraPicture->setText(QString("%1 %2").arg(cameraMake).arg(cameraModel));
		ui->m_lpLensModelPicture->setText(lensModel);
		if(fNumber == "---")
			ui->m_lpFNumberPicture->setText("---");
		else
			ui->m_lpFNumberPicture->setText("f 1:" + fNumber);
		ui->m_lpExposureTimePicture->setText(exposureTime);
		if(exposureBias == -1)
			ui->m_lpExposureBiasPicture->setText("---");
		else
			ui->m_lpExposureBiasPicture->setText(QString::number(exposureBias));
		if(iso == -1)
			ui->m_lpISOPicture->setText("---");
		else
			ui->m_lpISOPicture->setText(QString::number(iso));
		if(focalLength == -1)
			ui->m_lpFocalLengthPicture->setText("---");
		else
			ui->m_lpFocalLengthPicture->setText(QString("%1 mm").arg(focalLength));
		ui->m_lpFlashPicture->setText(flash);
		ui->m_lpGPSPicture->setText(gps);
	}
	else
	{
		ui->m_lpCategory->setCurrentIndex(1);

		ui->m_lpTitleVideo->setText(title);
		ui->m_lpFileNameVideo->setText(fileName);
		ui->m_lpPathVideo->setText(filePath);
		if(dateTime.isValid())
			ui->m_lpDateVideo->setText(dateTime.toString());
		else
			ui->m_lpDateVideo->setText("---");
		if(imageWidth == -1 || imageHeight == -1)
			ui->m_lpSizeVideo->setText("---");
		else
			ui->m_lpSizeVideo->setText(QString("%1x%2").arg(imageWidth).arg(imageHeight));
		if(hdr == -1)
			ui->m_lpHDRVideo->setText("---");
		else
			ui->m_lpHDRVideo->setText(hdr == 1 ? tr("yes") : tr("no"));
		if(cameraMake == "---" || cameraModel == "---")
			ui->m_lpCameraVideo->setText("---");
		else
			ui->m_lpCameraVideo->setText(QString("%1 %2").arg(cameraMake).arg(cameraModel));
	}
}
