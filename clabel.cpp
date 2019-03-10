#include "clabel.h"

#include <QResizeEvent>


cLabel::cLabel(QWidget *parent, Qt::WindowFlags f) :
	QLabel(parent, f)
{
}

cLabel::cLabel(const QString &text, QWidget *parent, Qt::WindowFlags f) :
	QLabel(text, parent, f)
{
}

void cLabel::setImage(cImage* lpImage)
{
	m_lpImage	= lpImage;
}

void cLabel::resizeEvent(QResizeEvent* e)
{
	QLabel::resizeEvent(e);
	setPixmap(QPixmap::fromImage(m_lpImage->scaled(width(), height(), Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation)));
}
