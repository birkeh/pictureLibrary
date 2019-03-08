#include "ccombopicker.h"
#include "ui_ccombopicker.h"


cComboPicker::cComboPicker(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cComboPicker)
{
	ui->setupUi(this);
	ui->m_lpText->setVisible(false);
	ui->m_lpPicture->setVisible(false);
}

cComboPicker::~cComboPicker()
{
	delete ui;
}

void cComboPicker::setText(const QString& szText)
{
	if(szText.isEmpty())
		ui->m_lpText->setVisible(false);
	else
	{
		ui->m_lpText->setVisible(true);
		ui->m_lpText->setText(szText);
	}
}

void cComboPicker::setImage(const QImage& image)
{
	if(image.isNull())
		ui->m_lpPicture->setVisible(false);
	else
	{
		ui->m_lpPicture->setVisible(true);
		ui->m_lpPicture->setPixmap(QPixmap::fromImage(image));
	}
}

void cComboPicker::setList(const QStringList& list)
{
	ui->m_lpComboBox->addItems(list);
}

void cComboPicker::setEditable(bool editable)
{
	ui->m_lpComboBox->setEditable(editable);
}

void cComboPicker::setSelection(const QString& selection)
{
	ui->m_lpComboBox->setCurrentText(selection);
}

QString cComboPicker::selection()
{
	return(ui->m_lpComboBox->currentText());
}
