/*!
 \file cdatepicker.cpp

*/

#include "cdatepicker.h"
#include "ui_cdatepicker.h"


cDatePicker::cDatePicker(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cDatePicker)
{
	ui->setupUi(this);
	ui->m_lpText->setVisible(false);
	ui->m_lpPicture->setVisible(false);
}

cDatePicker::~cDatePicker()
{
	delete ui;
}

void cDatePicker::setText(const QString& szText)
{
	if(szText.isEmpty())
		ui->m_lpText->setVisible(false);
	else
	{
		ui->m_lpText->setVisible(true);
		ui->m_lpText->setText(szText);
	}
}

void cDatePicker::setImage(const QImage& image)
{
	if(image.isNull())
		ui->m_lpPicture->setVisible(false);
	else
	{
		ui->m_lpPicture->setVisible(true);
		ui->m_lpPicture->setPixmap(QPixmap::fromImage(image));
	}
}

void cDatePicker::setDate(const QDate date)
{
	ui->m_lpDate->setDate(date);
}

QDate cDatePicker::date()
{
	return(ui->m_lpDate->date());
}
