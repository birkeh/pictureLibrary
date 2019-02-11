#ifndef CTOOLBOXINFO_H
#define CTOOLBOXINFO_H


#include "cpicture.h"

#include <QWidget>


namespace Ui {
class cToolBoxInfo;
}

class cToolBoxInfo : public QWidget
{
	Q_OBJECT

public:
	explicit cToolBoxInfo(QWidget *parent = nullptr);
	~cToolBoxInfo();

	void				setPicture(cPicture* lpPicture);
private:
	Ui::cToolBoxInfo*	ui;
};

#endif // CTOOLBOXINFO_H
