#ifndef CLABEL_H
#define CLABEL_H


#include <QLabel>

#include "cimage.h"


class cLabel : public QLabel
{
public:
	cLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	cLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

	void				setImage(cImage* lpImage);
private:
	cImage*				m_lpImage;

protected:
	void				resizeEvent(QResizeEvent* e);
};

#endif // CLABEL_H
