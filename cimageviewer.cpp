#include "cimageviewer.h"
#include "ui_cimageviewer.h"

#include "cimage.h"

#include <QKeyEvent>
#include <QFile>

#include <QDebug>


cImageViewer::cImageViewer(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cImageViewer),
	m_lpImage(nullptr)
{
	ui->setupUi(this);
	ui->m_lpImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	connect(ui->m_lpImage,	&cLabel::imageNext,		this,	&cImageViewer::onImageNext);
	connect(ui->m_lpImage,	&cLabel::imagePrev,		this,	&cImageViewer::onImagePrev);
	connect(ui->m_lpImage,	&cLabel::imageFirst,	this,	&cImageViewer::onImageFirst);
	connect(ui->m_lpImage,	&cLabel::imageLast,		this,	&cImageViewer::onImageLast);
}

cImageViewer::~cImageViewer()
{
	if(m_lpImage)
		delete m_lpImage;

	delete ui;
}

void cImageViewer::setPicture(QString szNumber, QString szRootPath, cPicture* lpPicture)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);

	if(m_lpImage)
		delete m_lpImage;

	QFile			file(szRootPath + "/" + lpPicture->filePath() + "/" + lpPicture->fileName());

	if(!file.exists())
		return;

	m_lpImage	= new cImage(file.fileName());

	QApplication::restoreOverrideCursor();

	if(m_lpImage->isNull())
	{
		delete m_lpImage;
		m_lpImage	= nullptr;
		return;
	}

	ui->m_lpImage->setImage(m_lpImage);
	ui->m_lpFileName->setText(szNumber + " - " + lpPicture->filePath() + "/" + lpPicture->fileName());

	setWindowFlag(Qt::Window);
	showMaximized();

	ui->m_lpImage->setFocus();
}

void cImageViewer::onImageNext()
{
	emit imageNext();
}

void cImageViewer::onImagePrev()
{
	emit imagePrev();
}

void cImageViewer::onImageLast()
{
	emit imageLast();
}

void cImageViewer::onImageFirst()
{
	emit imageFirst();
}
