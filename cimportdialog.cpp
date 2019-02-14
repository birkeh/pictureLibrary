#include "cimportdialog.h"
#include "ui_cimportdialog.h"

#include "common.h"

#include "cpicture.h"

#include <QSettings>
#include <QDir>
#include <QFileInfoList>
#include <QFileDialog>

#include <QPainter>

#include <QMimeDatabase>
#include <QMimeType>

#include <QMessageBox>
#include <QDebug>


cImportDialog::cImportDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cImportDialog),
	m_bHasImported(false)
{
	initUI();
	createActions();
}

cImportDialog::~cImportDialog()
{
	delete ui;
}

void cImportDialog::initUI()
{
	ui->setupUi(this);
	ui->m_lpProgress->setVisible(false);

	m_lpImportListModel	= new QStandardItemModel;
	ui->m_lpImportList->setModel(m_lpImportListModel);

	QSettings	settings;

	qint32		iX		= settings.value("import/x", QVariant::fromValue(-1)).toInt();
	qint32		iY		= settings.value("import/y", QVariant::fromValue(-1)).toInt();
	qint32		iWidth	= settings.value("import/width", QVariant::fromValue(-1)).toInt();
	qint32		iHeight	= settings.value("import/height", QVariant::fromValue(-1)).toInt();

	if(iWidth != -1 && iHeight != -1)
		resize(iWidth, iHeight);
	if(iX != -1 && iY != -1)
		move(iX, iY);

	qint32		iWidth1	= settings.value("import/splitter1", QVariant::fromValue(-1)).toInt();
	qint32		iWidth2	= settings.value("import/splitter2", QVariant::fromValue(-1)).toInt();

	ui->m_lpSplitter->setSizes(QList<int>() << iWidth1 << iWidth2);

	ui->m_lpPath->setText(settings.value("import/path", QDir::homePath()).toString());
}

bool cImportDialog::hasImported()
{
	return(m_bHasImported);
}

void cImportDialog::createActions()
{
	connect(ui->m_lpPathSelect,						&QPushButton::clicked,					this,	&cImportDialog::onPathSelect);
	connect(ui->m_lpRead,							&QPushButton::clicked,					this,	&cImportDialog::onRead);
	connect(ui->m_lpImport,							&QPushButton::clicked,					this,	&cImportDialog::onImport);
	connect(ui->m_lpImportList->selectionModel(),	&QItemSelectionModel::selectionChanged,	this,	&cImportDialog::onThumbnailSelected);
}

void cImportDialog::onPathSelect()
{
	QSettings	settings;
	QString		szPath	= settings.value("import/path", QDir::homePath()).toString();
	szPath	= QFileDialog::getExistingDirectory(this, tr("Import Directory"), szPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if(szPath.isEmpty())
		return;

	ui->m_lpPath->setText(szPath);
	settings.setValue("import/path", szPath);
}

void cImportDialog::onThumbnailSelected(const QItemSelection& /*selection*/, const QItemSelection& /*previous*/)
{
	cToolBoxInfo*	lpToolBoxInfo	= ui->m_lpInfo;

	ui->m_lpCount->setText(QString("count: %1, selected: %2").arg(m_lpImportListModel->rowCount()).arg(ui->m_lpImportList->selectionModel()->selectedRows().count()));

	if(ui->m_lpImportList->selectionModel()->selectedIndexes().count() != 1)
	{
		lpToolBoxInfo->setPicture(nullptr);
		return;
	}

	QStandardItem*	lpItem			= m_lpImportListModel->itemFromIndex(ui->m_lpImportList->currentIndex());
	cPicture*		lpPicture		= lpItem->data().value<cPicture*>();
	lpToolBoxInfo->setPicture(lpPicture);
}

void cImportDialog::accept()
{
	savePosition();
	QDialog::accept();
}

void cImportDialog::reject()
{
	savePosition();
	QDialog::reject();
}

void cImportDialog::savePosition()
{
	QSettings	settings;

	settings.setValue("import/width", QVariant::fromValue(size().width()));
	settings.setValue("import/height", QVariant::fromValue(size().height()));
	settings.setValue("import/x", QVariant::fromValue(x()));
	settings.setValue("import/y", QVariant::fromValue(y()));

	QList<qint32>	sizes	= ui->m_lpSplitter->sizes();

	for(int x = 0;x < sizes.count();x++)
		settings.setValue(QString("import/splitter%1").arg(x+1), QVariant::fromValue(sizes[x]));
}

void cImportDialog::onRead()
{
	if(ui->m_lpPath->text().isEmpty())
	{
		QMessageBox::critical(this, tr("Error"), tr("no path given!"));
		return;
	}

	m_lpImportListModel->clear();

	readDirectory(ui->m_lpPath->text(), ui->m_lpRecursive->isChecked());
}

void cImportDialog::onImport()
{
	m_bHasImported	= true;
}

void cImportDialog::readDirectory(const QString& szPath, bool bRecursive)
{
	QMimeDatabase	mimeDB;
	QDir			dir(szPath);
	QStringList		szDirs	= dir.entryList(QDir::Dirs);
	QFileInfoList	szFiles	= dir.entryInfoList(QDir::Files);

	if(bRecursive)
	{
		szDirs.removeAll(".");
		szDirs.removeAll("..");

		for(int x = 0;x < szDirs.count();x++)
			readDirectory(szPath + QDir::separator() + szDirs[x], bRecursive);
	}

	for(int x = 0;x < szFiles.count();x++)
	{
		QFileInfo	fileInfo	= szFiles[x];
		QMimeType	mimeType	= mimeDB.mimeTypeForFile(szFiles[x]);

		if(mimeType.name().startsWith("image"))
		{
			ui->m_lpStatusText->setText(QString(tr("found %1")).arg(fileInfo.fileName()));
			qApp->processEvents();

			cPicture*		lpPicture	= new cPicture;
			QIcon			icon;

			if(lpPicture->fromFile(fileInfo.filePath()))
			{
				if(lpPicture->thumbnail().width() != THUMBNAIL_WIDTH || lpPicture->thumbnail().height() != THUMBNAIL_HEIGHT)
				{
					QImage			thumbnail(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, lpPicture->thumbnail().format());
					thumbnail.fill(Qt::black);

					QPainter		painter(&thumbnail);
					painter.drawImage((THUMBNAIL_WIDTH-lpPicture->thumbnail().width())/2, (THUMBNAIL_HEIGHT-lpPicture->thumbnail().height())/2, lpPicture->thumbnail());
					painter.end();
					icon	= QIcon(QPixmap::fromImage(thumbnail));
				}
				else
					icon	= QIcon(QPixmap::fromImage(lpPicture->thumbnail()));

				QStandardItem*	lpItem		= new QStandardItem(icon, lpPicture->fileName());
				lpItem->setTextAlignment(Qt::AlignCenter);
				lpItem->setData(QVariant::fromValue(lpPicture));
				m_lpImportListModel->appendRow(lpItem);
				qApp->processEvents();

				ui->m_lpCount->setText(QString("count: %1, selected: %2").arg(m_lpImportListModel->rowCount()).arg(ui->m_lpImportList->selectionModel()->selectedRows().count()));
			}
		}
	}

	ui->m_lpStatusText->setText("");
}
