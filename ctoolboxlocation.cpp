#include "ctoolboxlocation.h"
#include "ui_ctoolboxlocation.h"

cToolBoxLocation::cToolBoxLocation(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cToolBoxLocation)
{
	ui->setupUi(this);
}

cToolBoxLocation::~cToolBoxLocation()
{
	delete ui;
}
