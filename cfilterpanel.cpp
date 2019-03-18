#include "cfilterpanel.h"
#include "ui_cfilterpanel.h"

cFilterPanel::cFilterPanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cFilterPanel)
{
	ui->setupUi(this);
}

cFilterPanel::~cFilterPanel()
{
	delete ui;
}
