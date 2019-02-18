#include "ctoolboxinfo.h"
#include "ui_ctoolboxinfo.h"


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
		ui->m_lpFileName->setText("---");
		ui->m_lpPath->setText("---");
		ui->m_lpDate->setText("---");
		ui->m_lpSize->setText("---");
		ui->m_lpCamera->setText("---");
		ui->m_lpLensModel->setText("---");
		ui->m_lpFNumber->setText("---");
		ui->m_lpExposureTime->setText("---");
		ui->m_lpExposureBias->setText("---");
		ui->m_lpISO->setText("---");
		ui->m_lpFocalLength->setText("---");
		ui->m_lpFlash->setText("---");
		ui->m_lpGPS->setText("---");
		return;
	}

	ui->m_lpFileName->setText(lpPicture->fileName());
	ui->m_lpPath->setText(lpPicture->filePath());
	ui->m_lpDate->setText(lpPicture->dateTime().toString());
	ui->m_lpSize->setText(QString("%1x%2").arg(lpPicture->imageWidth()).arg(lpPicture->imageHeight()));
	ui->m_lpCamera->setText(QString("%1 %2").arg(lpPicture->cameraMake()).arg(lpPicture->cameraModel()));
	ui->m_lpLensModel->setText(lpPicture->lensModel());
	ui->m_lpFNumber->setText("f 1:" + lpPicture->fNumber());
	ui->m_lpExposureTime->setText(lpPicture->exposureTime());
	ui->m_lpExposureBias->setText(QString::number(lpPicture->exposureBias()));
	ui->m_lpISO->setText(QString::number(lpPicture->iso()));
	ui->m_lpFocalLength->setText(QString("%1 mm").arg(lpPicture->focalLength()));
	ui->m_lpFlash->setText(lpPicture->flash());
	ui->m_lpGPS->setText(lpPicture->gps());
}
