#include "clabel.h"

#include <QResizeEvent>
#include <QKeyEvent>


cLabel::cLabel(QWidget *parent, Qt::WindowFlags f) :
	QLabel(parent, f)
{
	installEventFilter(this);
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

void cLabel::keyPressEvent(QKeyEvent* e)
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

	QLabel::keyPressEvent(e);
}
