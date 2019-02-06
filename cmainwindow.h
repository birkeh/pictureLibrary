#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cexif.h"

#include <QMainWindow>


namespace Ui {
class cMainWindow;
}

class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit cMainWindow(QWidget *parent = nullptr);
	~cMainWindow();

private:
	Ui::cMainWindow*	ui;
	cEXIFTagList		m_exifTagList;
};

#endif // CMAINWINDOW_H
