#include "cimageviewer.h"
#include "ui_cimageviewer.h"


cImageViewer::cImageViewer(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cImageViewer)
{
	ui->setupUi(this);
	ui->m_lpImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

cImageViewer::~cImageViewer()
{
	delete ui;
}

void cImageViewer::setImage(cImage* lpImage)
{
	ui->m_lpImage->setImage(lpImage);
}
