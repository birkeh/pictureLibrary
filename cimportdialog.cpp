#include "cimportdialog.h"
#include "ui_cimportdialog.h"

#include "common.h"

#include "cpicture.h"

#include "cdatetimepicker.h"

#include <QSettings>
#include <QDir>
#include <QFileInfoList>
#include <QFileDialog>

#include <QPainter>

#include <QMimeDatabase>
#include <QMimeType>

#include <QDateTime>

#include <QMessageBox>
#include <QDebug>


cImportDialog::cImportDialog(const QString& szRootPath, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cImportDialog),
	m_szRootPath(szRootPath),
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
	ui->m_lpImport->setEnabled(false);

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

	ui->m_lpRecursive->setChecked(settings.value("import/recursive", QVariant::fromValue(true)).toBool());
	if(settings.value("import/copy", QVariant::fromValue(true)).toBool())
		ui->m_lpCopy->setChecked(true);
	else
		ui->m_lpMove->setChecked(true);
	ui->m_lpDetectHDR->setChecked(settings.value("import/detectHDR", QVariant::fromValue(true)).toBool());
	ui->m_lpDetectJPG_RAW->setChecked(settings.value("import/detectJPG_RAW", QVariant::fromValue(true)).toBool());
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
	qint32			iCount			= ui->m_lpImportList->selectionModel()->selectedRows().count();
	ui->m_lpCount->setText(QString("count: %1, selected: %2").arg(m_lpImportListModel->rowCount()).arg(iCount));

	if(iCount)
		ui->m_lpImport->setEnabled(true);
	else
		ui->m_lpImport->setEnabled(false);

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

	settings.setValue("import/recursive", QVariant::fromValue(ui->m_lpRecursive->isChecked()));
	settings.setValue("import/copy", QVariant::fromValue(ui->m_lpCopy->isChecked()));
	settings.setValue("import/detectHDR", QVariant::fromValue(ui->m_lpDetectHDR->isChecked()));
	settings.setValue("import/detectJPG_RAW", QVariant::fromValue(ui->m_lpDetectJPG_RAW->isChecked()));
}

void cImportDialog::onRead()
{
	if(ui->m_lpPath->text().isEmpty())
	{
		QMessageBox::critical(this, tr("Error"), tr("no path given!"));
		return;
	}

	m_lpImportListModel->clear();
	ui->m_lpImport->setEnabled(false);

	readDirectory(ui->m_lpPath->text(), ui->m_lpRecursive->isChecked());
}

void cImportDialog::onImport()
{
	QModelIndexList	selected	= ui->m_lpImportList->selectionModel()->selectedRows();
	QDir			dir;
	QFile			file;

	ui->m_lpProgress->setVisible(true);
	ui->m_lpProgress->setRange(0, selected.count());

	for(int x = 0;x < selected.count();x++)
	{
		QStandardItem*	lpItem	= m_lpImportListModel->itemFromIndex(selected[x]);

		if(lpItem)
		{
			cPicture*	lpPicture	= lpItem->data().value<cPicture*>();

			if(lpPicture)
			{
				ui->m_lpStatusText->setText(QString("importing %1 ...").arg(lpPicture->fileName()));
				qApp->processEvents();

				QString	szSource	= lpPicture->filePath() + QDir::separator() + lpPicture->fileName();
				QString	szDest		= m_szRootPath + QDir::separator();
				QString	szDestPath	= "";

				if(lpPicture->dateTime().isValid())
					szDestPath.append(QString::number(lpPicture->dateTime().date().year()) + QDir::separator() + lpPicture->dateTime().date().toString("yyyy-MM-dd") + QDir::separator());

				if(!lpPicture->cameraModel().isEmpty())
					szDestPath.append(lpPicture->cameraModel() + QDir::separator());

				szDest.append(szDestPath);

				if(dir.mkpath(szDest))
				{
					szDest.append(lpPicture->fileName());

					if(file.exists(szDest))
						file.remove(szDest);

					file.copy(szSource, szDest);

					ui->m_lpProgress->setValue(x);
					qApp->processEvents();

					lpPicture->setFilePath(szDestPath);
					lpPicture->toDB();

					if(ui->m_lpMove->isChecked())
					{
//						file.remove(szSource);
					}
				}
			}
		}
	}
	ui->m_lpStatusText->setText("");
	ui->m_lpProgress->setVisible(false);

	m_bHasImported	= true;
}

void cImportDialog::readDirectory(const QString& szPath, bool bRecursive)
{
	QMimeDatabase	mimeDB;
	QDir			dir(szPath);
	QStringList		szDirs	= dir.entryList(QDir::Dirs);
	QFileInfoList	szFiles	= dir.entryInfoList(QDir::Files);
	QDateTime		oldDateTime;

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
				if(!lpPicture->dateTime().isValid())
				{
					cDateTimePicker	dateTimePicker;
					dateTimePicker.setWindowTitle("Warning");
					dateTimePicker.setText(QString(tr("\"%1\" has no date.\nTo import, please set a date.").arg(fileInfo.filePath())));
					dateTimePicker.setImage(lpPicture->thumbnail());

					if(!oldDateTime.isValid())
						oldDateTime	= fileInfo.birthTime();

					dateTimePicker.setDateTime(oldDateTime);
					if(dateTimePicker.exec() == QDialog::Rejected)
						continue;

					oldDateTime	= dateTimePicker.dateTime();
					lpPicture->setDateTime(oldDateTime);
				}

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
