/*!
 \file cexportdialog.cpp

*/

#include "cexportdialog.h"
#include "ui_cexportdialog.h"

#include <QSettings>
#include <QFileDialog>


cExportDialog::cExportDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cExportDialog)
{
	initUI();
	createActions();
}

cExportDialog::~cExportDialog()
{
	delete ui;
}

void cExportDialog::initUI()
{
	ui->setupUi(this);

	ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

	QSettings	settings;

	qint32		iX		= settings.value("export/x", QVariant::fromValue(-1)).toInt();
	qint32		iY		= settings.value("export/y", QVariant::fromValue(-1)).toInt();
	qint32		iWidth	= settings.value("export/width", QVariant::fromValue(-1)).toInt();
	qint32		iHeight	= settings.value("export/height", QVariant::fromValue(-1)).toInt();

	if(iWidth != -1 && iHeight != -1)
		resize(iWidth, iHeight);
	if(iX != -1 && iY != -1)
		move(iX, iY);

	ui->m_lpPath->setText(settings.value("export/path", QDir::homePath()).toString());

	QString		str		= settings.value("export/filter", "exportAll").toString();
	if(str == "exportAll")
	{
		ui->m_lpExportAll->setChecked(true);
		ui->m_lpExportSelection->setChecked(false);
		ui->m_lpExportFilter->setChecked(false);
	}
	else if(str == "exportSelection")
	{
		ui->m_lpExportAll->setChecked(false);
		ui->m_lpExportSelection->setChecked(true);
		ui->m_lpExportFilter->setChecked(false);
	}
	else
	{
		ui->m_lpExportAll->setChecked(false);
		ui->m_lpExportSelection->setChecked(false);
		ui->m_lpExportFilter->setChecked(true);
	}

	ui->m_lpKeepFilename->setChecked(settings.value("export/keepFile", true).toBool());
	ui->m_lpRenameFilename->setChecked(!settings.value("export/keepFile", true).toBool());
	ui->m_lpFilePattern->setText(settings.value("export/filePattern", "%o").toString());

	ui->m_lpKeepStructure->setChecked(settings.value("export/keepStructure", true).toBool());
	ui->m_lpRenameStructure->setChecked(!settings.value("export/keepStructure", true).toBool());
	ui->m_lpStructurePattern->setText(settings.value("export/structurePattern", "%o").toString());

	checkAccept();
}

void cExportDialog::createActions()
{
	connect(ui->m_lpPathSelect,			&QPushButton::clicked,		this,	&cExportDialog::onPathSelect);
	connect(ui->m_lpPath,				&QLineEdit::textChanged,	this,	&cExportDialog::onPathChanged);
	connect(ui->m_lpKeepFilename,		&QRadioButton::clicked,		this,	&cExportDialog::onFileOriginalClicked);
	connect(ui->m_lpRenameFilename,		&QRadioButton::clicked,		this,	&cExportDialog::onFilePatternClicked);
	connect(ui->m_lpFilePattern,		&QLineEdit::textChanged,	this,	&cExportDialog::onFilePatternChanged);
	connect(ui->m_lpKeepStructure,		&QRadioButton::clicked,		this,	&cExportDialog::onStructureOriginalClicked);
	connect(ui->m_lpRenameStructure,	&QRadioButton::clicked,		this,	&cExportDialog::onStructurePatternClicked);
	connect(ui->m_lpStructurePattern,	&QLineEdit::textChanged,	this,	&cExportDialog::onStructurePatternChanged);
}

void cExportDialog::onPathSelect()
{
	QSettings	settings;
	QString		szPath	= settings.value("export/path", QDir::homePath()).toString();
	szPath	= QFileDialog::getExistingDirectory(this, tr("Export Directory"), szPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if(szPath.isEmpty())
		return;

	ui->m_lpPath->setText(szPath);
	settings.setValue("export/path", szPath);
}

void cExportDialog::onPathChanged(const QString& /*text*/)
{
	checkAccept();
}

void cExportDialog::onFileOriginalClicked(bool /*selected*/)
{
	checkAccept();
}

void cExportDialog::onFilePatternClicked(bool /*selected*/)
{
	checkAccept();
}

void cExportDialog::onFilePatternChanged(const QString& /*text*/)
{
	checkAccept();
}

void cExportDialog::onStructureOriginalClicked(bool /*selected*/)
{
	checkAccept();
}

void cExportDialog::onStructurePatternClicked(bool /*selected*/)
{
	checkAccept();
}

void cExportDialog::onStructurePatternChanged(const QString& /*text*/)
{
	checkAccept();
}

void cExportDialog::accept()
{
	savePosition();
	QDialog::accept();
}

void cExportDialog::reject()
{
	savePosition();
	QDialog::reject();
}

void cExportDialog::savePosition()
{
	QSettings	settings;

	settings.setValue("export/width", QVariant::fromValue(size().width()));
	settings.setValue("export/height", QVariant::fromValue(size().height()));
	settings.setValue("export/x", QVariant::fromValue(x()));
	settings.setValue("export/y", QVariant::fromValue(y()));

	settings.setValue("export/path", ui->m_lpPath->text());

	if(ui->m_lpExportAll->isChecked())
		settings.setValue("export/filter", "exportAll");
	else if(ui->m_lpExportSelection->isChecked())
		settings.setValue("export/filter", "exportSelection");
	else
		settings.setValue("export/filter", "exportFilter");

	settings.setValue("export/keepFile", QVariant::fromValue(ui->m_lpKeepFilename->isChecked()));
	settings.setValue("export/filePattern", ui->m_lpFilePattern->text());

	settings.setValue("export/keepStructure", QVariant::fromValue(ui->m_lpKeepStructure->isChecked()));
	settings.setValue("export/structurePattern", ui->m_lpStructurePattern->text());
}

QString cExportDialog::path()
{
	return(ui->m_lpPath->text());
}

cExportDialog::EXPORT_TYPE cExportDialog::exportType()
{
	if(ui->m_lpExportAll->isChecked())
		return(EXPORT_TYPE_ALL);
	else if(ui->m_lpExportSelection->isChecked())
		return(EXPORT_TYPE_SELECTION);
	else
		return(EXPORT_TYPE_FILTER);
}

QString cExportDialog::filePattern()
{
	if(ui->m_lpKeepFilename->isChecked())
		return(":::KEEP:::");

	return(ui->m_lpFilePattern->text());
}

QString cExportDialog::structurePattern()
{
	if(ui->m_lpKeepStructure->isChecked())
		return(":::KEEP:::");

	return(ui->m_lpStructurePattern->text());
}

void cExportDialog::checkAccept()
{
	bool	accept	= true;

	if(ui->m_lpPath->text().isEmpty())
		accept	= false;

	if(ui->m_lpRenameFilename->isChecked() && ui->m_lpFilePattern->text().isEmpty())
		accept	= false;

	if(accept)
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
	else
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}
