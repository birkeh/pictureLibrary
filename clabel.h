#ifndef CLABEL_H
#define CLABEL_H


#include <QLabel>

#include "cimage.h"


class cLabel : public QLabel
{
	Q_OBJECT

public:
	cLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	cLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

	void				setImage(cImage* lpImage);
private:
	cImage*				m_lpImage;

protected:
	void				resizeEvent(QResizeEvent* e);
	void				keyPressEvent(QKeyEvent* e);

signals:
	/*!
	 \brief

	 \fn imageNext
	*/
	void					imageNext();
	/*!
	 \brief

	 \fn imagePrev
	*/
	void					imagePrev();
	/*!
	 \brief

	 \fn imageLast
	*/
	void					imageLast();
	/*!
	 \brief

	 \fn imageFirst
	*/
	void					imageFirst();
};

#endif // CLABEL_H
