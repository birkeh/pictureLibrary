#include "cimageviewer.h"
#include "ui_cimageviewer.h"

#include <QKeyEvent>

#include <QDebug>


cImageViewer::cImageViewer(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cImageViewer)
{
	ui->setupUi(this);
	ui->m_lpImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

//	connect(ui->m_lpImage,	&cLabel::imageNext,		this,	&cImageViewer::onImageNext);
//	connect(ui->m_lpImage,	&cLabel::imagePrev,		this,	&cImageViewer::onImagePrev);
//	connect(ui->m_lpImage,	&cLabel::imageFirst,	this,	&cImageViewer::onImageFirst);
//	connect(ui->m_lpImage,	&cLabel::imageLast,		this,	&cImageViewer::onImageLast);
}

cImageViewer::~cImageViewer()
{
	delete ui;
}

void cImageViewer::setImage(cImage* lpImage)
{
	ui->m_lpImage->setImage(lpImage);

	setWindowFlag(Qt::Window);
	showFullScreen();

	ui->m_lpImage->setFocus();
}

void cImageViewer::keyPressEvent(QKeyEvent* e)
{
	switch(e->key())
	{
	case Qt::Key_Left:
		emit imagePrev();
		break;
	case Qt::Key_Right:
		emit imageNext();
		break;
	case Qt::Key_Home:
		emit imageFirst();
		break;
	case Qt::Key_End:
		emit imageLast();
		break;
	default:
		break;
	}

	QDialog::keyPressEvent(e);
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
