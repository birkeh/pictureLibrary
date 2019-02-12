#include "cimportdialog.h"
#include "ui_cimportdialog.h"

#include <QSettings>
#include <QDir>
#include <QFileDialog>


cImportDialog::cImportDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cImportDialog)
{
	ui->setupUi(this);

	QSettings	settings;

	if(settings.value("main/maximized").toBool())
	{
		qint32		iX		= settings.value("import/x", QVariant::fromValue(-1)).toInt();
		qint32		iY		= settings.value("import/y", QVariant::fromValue(-1)).toInt();
		qint32		iWidth	= settings.value("import/width", QVariant::fromValue(-1)).toInt();
		qint32		iHeight	= settings.value("import/height", QVariant::fromValue(-1)).toInt();

		if(iWidth != -1 && iHeight != -1)
			resize(iWidth, iHeight);
		if(iX != -1 && iY != -1)
			move(iX, iY);
	}
}

cImportDialog::~cImportDialog()
{
	delete ui;
}

void cImportDialog::on_m_lpPathSelect_clicked()
{
	QSettings	settings;
	QString		szPath	= settings.value("import/path", QDir::homePath()).toString();
	szPath	= QFileDialog::getExistingDirectory(this, tr("Import Directory"), szPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if(szPath.isEmpty())
		return;

	ui->m_lpPath->setText(szPath);
	settings.setValue("import/path", szPath);
}

void cImportDialog::closeEvent(QCloseEvent *event)
{
	QSettings	settings;
	settings.setValue("import/width", QVariant::fromValue(size().width()));
	settings.setValue("import/height", QVariant::fromValue(size().height()));
	settings.setValue("import/x", QVariant::fromValue(x()));
	settings.setValue("import/y", QVariant::fromValue(y()));
	if(this->isMaximized())
		settings.setValue("import/maximized", QVariant::fromValue(true));
	else
		settings.setValue("import/maximized", QVariant::fromValue(false));

	event->accept();
}
