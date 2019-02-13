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
		ui->m_lpDate->setText("---");
		ui->m_lpSize->setText("---");
		ui->m_lpCamera->setText("---");
		return;
	}

	ui->m_lpFileName->setText(lpPicture->fileName());
	ui->m_lpDate->setText(lpPicture->dateTime().toString());
	ui->m_lpSize->setText(QString("%1x%2").arg(lpPicture->imageWidth()).arg(lpPicture->imageHeight()));
//	ui->m_lpCamera->setText(QString("%1 %2").arg(lpPicture->cameraMake()).arg(lpPicture->cameraModel()));
	ui->m_lpCamera->setText(QString("%1").arg(lpPicture->imageOrientation()));
}
