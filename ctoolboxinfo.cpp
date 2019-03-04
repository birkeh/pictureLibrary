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

	if(lpPicture->mimeType().startsWith("image"))
	{
		ui->m_lpCategory->setCurrentIndex(0);
		if(!lpPicture)
		{
			ui->m_lpFileNamePicture->setText("---");
			ui->m_lpPathPicture->setText("---");
			ui->m_lpDatePicture->setText("---");
			ui->m_lpSizePicture->setText("---");
			ui->m_lpCameraPicture->setText("---");
			ui->m_lpLensModelPicture->setText("---");
			ui->m_lpFNumberPicture->setText("---");
			ui->m_lpExposureTimePicture->setText("---");
			ui->m_lpExposureBiasPicture->setText("---");
			ui->m_lpISOPicture->setText("---");
			ui->m_lpFocalLengthPicture->setText("---");
			ui->m_lpFlashPicture->setText("---");
			ui->m_lpGPSPicture->setText("---");
			return;
		}

		ui->m_lpFileNamePicture->setText(lpPicture->fileName());
		ui->m_lpPathPicture->setText(lpPicture->filePath());
		ui->m_lpDatePicture->setText(lpPicture->dateTime().toString());
		ui->m_lpSizePicture->setText(QString("%1x%2").arg(lpPicture->imageWidth()).arg(lpPicture->imageHeight()));
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
		if(!lpPicture)
		{
			ui->m_lpFileNameVideo->setText("---");
			ui->m_lpPathVideo->setText("---");
			ui->m_lpDateVideo->setText("---");
			ui->m_lpSizeVideo->setText("---");
			ui->m_lpCameraVideo->setText("---");
			ui->m_lpDurationVideo->setText("---");
			return;
		}

		ui->m_lpFileNameVideo->setText(lpPicture->fileName());
		ui->m_lpPathVideo->setText(lpPicture->filePath());
		ui->m_lpDateVideo->setText(lpPicture->dateTime().toString());
		ui->m_lpSizeVideo->setText(QString("%1x%2").arg(lpPicture->imageWidth()).arg(lpPicture->imageHeight()));
		ui->m_lpCameraVideo->setText(QString("%1 %2").arg(lpPicture->cameraMake()).arg(lpPicture->cameraModel()));
		ui->m_lpDurationVideo->setText(ms2String(lpPicture->duration()));
	}
}
