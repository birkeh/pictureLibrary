#ifndef CIMAGEVIEWER_H
#define CIMAGEVIEWER_H


#include "cimage.h"

#include <QDialog>


namespace Ui {
class cImageViewer;
}

class cImageViewer : public QDialog
{
	Q_OBJECT

public:
	explicit cImageViewer(QWidget *parent = nullptr);
	~cImageViewer();

	void					setImage(cImage* lpImage);
private:
	Ui::cImageViewer*		ui;
};

#endif // CIMAGEVIEWER_H
