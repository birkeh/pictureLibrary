#include "ctoolboxtag.h"
#include "ui_ctoolboxtag.h"

cToolBoxTag::cToolBoxTag(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cToolBoxTag)
{
	ui->setupUi(this);
}

cToolBoxTag::~cToolBoxTag()
{
	delete ui;
}
