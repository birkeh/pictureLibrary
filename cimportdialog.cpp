/*!
 \file cimportdialog.cpp

*/

#include "cimportdialog.h"
#include "ui_cimportdialog.h"

#include "common.h"

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


cImportDialog::cImportDialog(const QString& szRootPath, cPictureList& pictureList, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cImportDialog),
	m_szRootPath(szRootPath),
	m_pictureList(pictureList),
	m_lpFolderViewModel(nullptr),
	m_lpThumbnailViewModel(nullptr),
	m_lpThumbnailSortFilterProxyModel(nullptr),
	m_bLoading(false),
	m_bHasImported(false),
	m_lpRootItem(nullptr)
{
	initUI();
	createActions();
}

cImportDialog::~cImportDialog()
{
	delete m_lpThumbnailViewModel;
	delete m_lpFolderViewModel;
	delete m_lpThumbnailSortFilterProxyModel;

	delete ui;
}

void cImportDialog::initUI()
{
	ui->setupUi(this);
	ui->m_lpProgress->setVisible(false);
	ui->m_lpTotalProgress->setVisible(false);
	ui->m_lpImport->setEnabled(false);

	m_lpFolderViewModel	= new QStandardItemModel;
	ui->m_lpFolderView->setModel(m_lpFolderViewModel);

	m_lpThumbnailViewModel	= new QStandardItemModel;
	m_lpThumbnailSortFilterProxyModel	= new cThumbnailSortFilterProxyModel(this);
	ui->m_lpThumbnailView->setModel(m_lpThumbnailSortFilterProxyModel);
	m_lpThumbnailSortFilterProxyModel->setSourceModel(m_lpThumbnailViewModel);

	QSettings	settings;

	qint32		iX		= settings.value("import/x", QVariant::fromValue(-1)).toInt();
	qint32		iY		= settings.value("import/y", QVariant::fromValue(-1)).toInt();
	qint32		iWidth	= settings.value("import/width", QVariant::fromValue(-1)).toInt();
	qint32		iHeight	= settings.value("import/height", QVariant::fromValue(-1)).toInt();

	if(iWidth != -1 && iHeight != -1)
		resize(iWidth, iHeight);
	if(iX != -1 && iY != -1)
		move(iX, iY);

	qint32		iWidth1	= settings.value("main/splitter1", QVariant::fromValue(-1)).toInt();
	qint32		iWidth2	= settings.value("main/splitter2", QVariant::fromValue(-1)).toInt();
	qint32		iWidth3	= settings.value("main/splitter3", QVariant::fromValue(-1)).toInt();

	ui->m_lpSplitter->setSizes(QList<int>() << iWidth1 << iWidth2 << iWidth3);

	ui->m_lpPath->setText(settings.value("import/path", QDir::homePath()).toString());

	ui->m_lpRecursive->setChecked(settings.value("import/recursive", QVariant::fromValue(true)).toBool());
	if(settings.value("import/copy", QVariant::fromValue(true)).toBool())
		ui->m_lpCopy->setChecked(true);
	else
		ui->m_lpMove->setChecked(true);

	ui->m_lpPictures->setChecked(settings.value("import/pictures", QVariant::fromValue(true)).toBool());
	ui->m_lpVideos->setChecked(settings.value("import/videos", QVariant::fromValue(true)).toBool());
	ui->m_lpDetectHDR->setChecked(settings.value("import/detectHDR", QVariant::fromValue(true)).toBool());
	ui->m_lpDetectJPG_RAW->setChecked(settings.value("import/detectJPG_RAW", QVariant::fromValue(true)).toBool());
}

bool cImportDialog::hasImported()
{
	return(m_bHasImported);
}

void cImportDialog::createActions()
{
	connect(ui->m_lpPathSelect,							&QPushButton::clicked,					this,	&cImportDialog::onPathSelect);
	connect(ui->m_lpRead,								&QPushButton::clicked,					this,	&cImportDialog::onRead);
	connect(ui->m_lpImport,								&QPushButton::clicked,					this,	&cImportDialog::onImport);
	connect(ui->m_lpThumbnailView->selectionModel(),	&QItemSelectionModel::selectionChanged,	this,	&cImportDialog::onThumbnailSelected);
	connect(ui->m_lpFolderView->selectionModel(),		&QItemSelectionModel::selectionChanged,	this,	&cImportDialog::onFolderSelected);
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
	qint32			iCount			= ui->m_lpThumbnailView->selectionModel()->selectedRows().count();
	ui->m_lpCount->setText(QString("count: %1, selected: %2").arg(m_lpThumbnailViewModel->rowCount()).arg(iCount));

	if(iCount)
		ui->m_lpImport->setEnabled(true);
	else
		ui->m_lpImport->setEnabled(false);

	if(ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count() != 1)
	{
		lpToolBoxInfo->setPicture(nullptr);
		return;
	}

	for(int x = 0;x < ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count();x++)
	{
		QModelIndex		index	= ui->m_lpThumbnailView->selectionModel()->selectedIndexes()[x];
		if(!index.isValid())
			return;

		cPicture*		lpPicture	= m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>();
		lpToolBoxInfo->setPicture(lpPicture);
	}
}

void cImportDialog::onFolderSelected(const QItemSelection& /*selection*/, const QItemSelection& /*previous*/)
{
	if(m_bLoading)
		return;

	QStandardItem*			lpItem		= m_lpFolderViewModel->itemFromIndex(ui->m_lpFolderView->currentIndex());
	if(!lpItem)
		return;

	m_lpThumbnailSortFilterProxyModel->setFilterPath(lpItem->data(Qt::UserRole+2).toString());
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
		settings.setValue(QString("main/splitter%1").arg(x+1), QVariant::fromValue(sizes[x]));

	settings.setValue("import/recursive", QVariant::fromValue(ui->m_lpRecursive->isChecked()));
	settings.setValue("import/pictures", QVariant::fromValue(ui->m_lpRecursive->isChecked()));
	settings.setValue("import/videos", QVariant::fromValue(ui->m_lpRecursive->isChecked()));
	settings.setValue("import/copy", QVariant::fromValue(ui->m_lpCopy->isChecked()));
	settings.setValue("import/detectHDR", QVariant::fromValue(ui->m_lpDetectHDR->isChecked()));
	settings.setValue("import/detectJPG_RAW", QVariant::fromValue(ui->m_lpDetectJPG_RAW->isChecked()));
}

void cImportDialog::onRead()
{
	if(m_bLoading)
		return;

	if(ui->m_lpPath->text().isEmpty())
	{
		QMessageBox::critical(this, tr("Error"), tr("no path given!"));
		return;
	}

	m_bLoading	= true;

	m_lpFolderViewModel->clear();
	m_lpThumbnailViewModel->clear();
	ui->m_lpImport->setEnabled(false);

	m_lpRootItem	= new QStandardItem("library");
	m_lpFolderViewModel->appendRow(m_lpRootItem);

	readDirectory(ui->m_lpPath->text(), ui->m_lpRecursive->isChecked());

	ui->m_lpFolderView->expandAll();

	m_bLoading	= false;
}

void cImportDialog::onImport()
{
	QDir			dir;
	QFile			file;

	ui->m_lpProgress->setVisible(true);
	ui->m_lpProgress->setRange(0, 100);
	ui->m_lpTotalProgress->setVisible(true);
	ui->m_lpTotalProgress->setRange(0, ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count());

	for(int x = 0;x < ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count();x++)
	{
		QModelIndex		index	= ui->m_lpThumbnailView->selectionModel()->selectedIndexes()[x];
		if(index.isValid())
		{
			cPicture*		lpPicture	= m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>();

			if(lpPicture)
			{
				if(m_pictureList.find(lpPicture))
				{
					if(QMessageBox::question(this, tr("File Exists"), QString(tr("%1%2%3 already exists.\nDo you want to overwrite?").arg(lpPicture->filePath()).arg("/").arg(lpPicture->fileName()))) == QMessageBox::No)
						continue;
					continue;
				}
				ui->m_lpStatusText->setText(QString("importing %1 ...").arg(lpPicture->fileName()));
				qApp->processEvents();

				QString	szSource	= lpPicture->filePath() + "/" + lpPicture->fileName();
				QString	szDest		= m_szRootPath + "/";
				QString	szDestPath	= picture2Path(lpPicture);

				szDest.append(szDestPath + "/");
				szDest.append(lpPicture->fileName());
				szDest	= szDest.replace("\\", "/");

//				if(copyFile(ui->m_lpProgress, szSource, szDest, ui->m_lpMove->isChecked()))
				if(copyFile(ui->m_lpProgress, szSource, szDest, false))
				{
					ui->m_lpTotalProgress->setValue(x+1);
					qApp->processEvents();

					lpPicture->setFilePath(szDestPath);
					lpPicture->toDB();
					m_pictureList.add(lpPicture);
				}
			}
		}
	}
	ui->m_lpStatusText->setText("");
	ui->m_lpProgress->setVisible(false);
	ui->m_lpTotalProgress->setVisible(false);

	m_bHasImported	= true;
}

void cImportDialog::readDirectory(const QString& szPath, bool bRecursive)
{
	QMimeDatabase	mimeDB;
	QDir			dir(szPath);
	QStringList		szDirs		= dir.entryList(QDir::Dirs);
	QFileInfoList	szFiles		= dir.entryInfoList(QDir::Files);
	QDateTime		oldDateTime;
	bool			bPictures	= ui->m_lpPictures->isChecked();
	bool			bVideos		= ui->m_lpVideos->isChecked();

	if(bRecursive)
	{
		szDirs.removeAll(".");
		szDirs.removeAll("..");

		for(int x = 0;x < szDirs.count();x++)
			readDirectory(szPath + "/" + szDirs[x], bRecursive);
	}

	for(int x = 0;x < szFiles.count();x++)
	{
		QFileInfo	fileInfo	= szFiles[x];
		QMimeType	mimeType	= mimeDB.mimeTypeForFile(szFiles[x]);

		if((mimeType.name().startsWith("image") && bPictures) || (mimeType.name().startsWith("video") && bVideos))
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

				if(icon.isNull())
				{
					QPixmap		pixmap(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT);
					QPainter	painter(&pixmap);
					painter.setBrush(Qt::black);
					painter.drawRect(0, 0, THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT);
					painter.end();
					icon	= QIcon(pixmap);
				}

				QStandardItem*	lpItem		= new QStandardItem(icon, lpPicture->fileName());
				lpItem->setTextAlignment(Qt::AlignCenter);
				lpItem->setData(QVariant::fromValue(lpPicture));
				lpItem->setData(QVariant::fromValue(lpPicture->filePath()), Qt::UserRole+2);
				m_lpThumbnailViewModel->appendRow(lpItem);

				insertPath(lpPicture->filePath(), m_lpRootItem);

				qApp->processEvents();

				ui->m_lpCount->setText(QString("count: %1, selected: %2").arg(m_lpThumbnailViewModel->rowCount()).arg(ui->m_lpThumbnailView->selectionModel()->selectedRows().count()));
			}
		}
	}

	ui->m_lpStatusText->setText("");
}
