/*!
 \file cdatetimepicker.cpp

*/

#include "cdatetimepicker.h"
#include "ui_cdatetimepicker.h"


cDateTimePicker::cDateTimePicker(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cDateTimePicker)
{
	ui->setupUi(this);
	ui->m_lpText->setVisible(false);
	ui->m_lpPicture->setVisible(false);
}

cDateTimePicker::~cDateTimePicker()
{
	delete ui;
}

void cDateTimePicker::setText(const QString& szText)
{
	if(szText.isEmpty())
		ui->m_lpText->setVisible(false);
	else
	{
		ui->m_lpText->setVisible(true);
		ui->m_lpText->setText(szText);
	}
}

void cDateTimePicker::setImage(const QImage& image)
{
	if(image.isNull())
		ui->m_lpPicture->setVisible(false);
	else
	{
		ui->m_lpPicture->setVisible(true);
		ui->m_lpPicture->setPixmap(QPixmap::fromImage(image));
	}
}

void cDateTimePicker::setDateTime(const QDateTime dateTime)
{
	ui->m_lpDateTime->setDateTime(dateTime);
}

QDateTime cDateTimePicker::dateTime()
{
	return(ui->m_lpDateTime->dateTime());
}
