#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "cexif.h"


cMainWindow::cMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow)
{
	ui->setupUi(this);

	cEXIF	exif;

	exif.fromFile("C:/Users/VET0572/Pictures/IMG_1372.CR2");
}

cMainWindow::~cMainWindow()
{
	delete ui;
}
