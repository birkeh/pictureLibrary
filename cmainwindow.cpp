/*!
 \file cmainwindow.cpp

*/

#include "common.h"

#include "cmainwindow.h"
#include "cimportdialog.h"
#include "cexportdialog.h"

#include "cdatepicker.h"
#include "cdatetimepicker.h"
#include "ccombopicker.h"

#include "cimage.h"
#include "cimageviewer.h"

#include "ui_cmainwindow.h"

#include <QDebug>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QLabel>
#include <QStandardItem>
#include <QIcon>
#include <QPixmap>
#include <QInputDialog>
#include <QFileDialog>
#include <QPushButton>


cMainWindow::cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpFilterPanel(nullptr),
	m_lpProgressBar(nullptr),
	m_lpFolderViewModel(nullptr),
	m_lpFolderSortFilterProxyModel(nullptr),
	m_lpThumbnailViewModel(nullptr),
	m_lpThumbnailSortFilterProxyModel(nullptr),
	m_lpRootItem(nullptr),
	m_bLoading(false),
	m_lpSplashScreen(lpSplashScreen),
	m_lpFileMenu(nullptr),
	m_lpFileToolBar(nullptr)
{
	initUI();
	createActions();

	QSettings	settings;
	m_szOldPath	= settings.value("file/lastPath", QDir::homePath()).toString();
	m_pictureLibrary.openDatabase(m_szOldPath);
	loadData(false);

	updateRecentFileActions();
	showCount();
}

cMainWindow::~cMainWindow()
{
	if(m_lpFilterPanel)
		delete m_lpFilterPanel;

	delete m_lpThumbnailViewModel;
	delete m_lpFolderViewModel;
	delete m_lpThumbnailSortFilterProxyModel;
	delete m_lpFolderSortFilterProxyModel;

	delete ui;
}

void cMainWindow::closeEvent(QCloseEvent *event)
{
	QSettings	settings;
	settings.setValue("main/width", QVariant::fromValue(size().width()));
	settings.setValue("main/height", QVariant::fromValue(size().height()));
	settings.setValue("main/x", QVariant::fromValue(x()));
	settings.setValue("main/y", QVariant::fromValue(y()));
	if(this->isMaximized())
		settings.setValue("main/maximized", QVariant::fromValue(true));
	else
		settings.setValue("main/maximized", QVariant::fromValue(false));

	QList<qint32>	sizes	= ui->m_lpSplitter->sizes();

	for(int x = 0;x < sizes.count();x++)
		settings.setValue(QString("main/splitter%1").arg(x+1), QVariant::fromValue(sizes[x]));

	m_lpFilterPanel->saveSettings();

	event->accept();
}

void cMainWindow::initUI()
{
	ui->setupUi(this);

	QIcon::setThemeName("TangoMFK");

	ui->m_lpFilter->setTitle(tr("Filter"));
	m_lpFilterPanel	= new cFilterPanel(this);
	ui->m_lpFilter->setContentWidget(m_lpFilterPanel);

	m_lpFolderViewModel	= new QStandardItemModel;
	m_lpFolderSortFilterProxyModel	= new cFolderSortFilterProxyModel(this);
	ui->m_lpFolderView->setModel(m_lpFolderSortFilterProxyModel);
	m_lpFolderSortFilterProxyModel->setSourceModel(m_lpFolderViewModel);

	m_lpThumbnailViewModel	= new QStandardItemModel;
	m_lpThumbnailSortFilterProxyModel	= new cThumbnailSortFilterProxyModel(this);
	ui->m_lpThumbnailView->setModel(m_lpThumbnailSortFilterProxyModel);
	m_lpThumbnailSortFilterProxyModel->setSourceModel(m_lpThumbnailViewModel);

	m_lpProgressBar			= new QProgressBar(this);
	m_lpProgressBar->setVisible(false);
	ui->m_lpStatusBar->addPermanentWidget(m_lpProgressBar);

	QIcon::setThemeName("TangoMFK");

	QSettings	settings;

	if(!settings.value("main/maximized").toBool())
	{
		qint32		iX		= settings.value("main/x", QVariant::fromValue(-1)).toInt();
		qint32		iY		= settings.value("main/y", QVariant::fromValue(-1)).toInt();
		qint32		iWidth	= settings.value("main/width", QVariant::fromValue(-1)).toInt();
		qint32		iHeight	= settings.value("main/height", QVariant::fromValue(-1)).toInt();

		if(iWidth != -1 && iHeight != -1)
			resize(iWidth, iHeight);
		if(iX != -1 && iY != -1)
			move(iX, iY);
	}

	qint32		iWidth1	= settings.value("main/splitter1", QVariant::fromValue(-1)).toInt();
	qint32		iWidth2	= settings.value("main/splitter2", QVariant::fromValue(-1)).toInt();
	qint32		iWidth3	= settings.value("main/splitter3", QVariant::fromValue(-1)).toInt();

	ui->m_lpSplitter->setSizes(QList<int>() << iWidth1 << iWidth2 << iWidth3);

	ui->m_lpToolBox->setCurrentIndex(0);
}

void cMainWindow::createActions()
{
	setToolButtonStyle(Qt::ToolButtonFollowStyle);

	createFileActions();
	createContextActions();

	connect(ui->m_lpThumbnailView->selectionModel(),	&QItemSelectionModel::selectionChanged,	this,	&cMainWindow::onThumbnailSelected);
	connect(ui->m_lpFolderView->selectionModel(),		&QItemSelectionModel::selectionChanged,	this,	&cMainWindow::onFolderSelected);

	connect(ui->m_lpThumbnailView,						&QListView::customContextMenuRequested,	this,	&cMainWindow::onThumbnailViewContextMenu);

	connect(ui->m_lpThumbnailView,						&QListView::doubleClicked,				this,	&cMainWindow::onThumbnailDoubleClicked);

	connect(ui->m_lpToolBoxTags,						&cToolBoxTag::tagAdded,					this,	&cMainWindow::onTagAdded);
	connect(ui->m_lpToolBoxTags,						&cToolBoxTag::tagRemoved,				this,	&cMainWindow::onTagRemoved);
	connect(ui->m_lpToolBoxTags,						&cToolBoxTag::tagEdited,				this,	&cMainWindow::onTagEdited);
	connect(ui->m_lpToolBoxTags,						&cToolBoxTag::tagListChanged,			this,	&cMainWindow::onTagListChanged);

	connect(ui->m_lpToolBoxPerson,						&cToolBoxPerson::personAdded,			this,	&cMainWindow::onPersonAdded);
	connect(ui->m_lpToolBoxPerson,						&cToolBoxPerson::personRemoved,			this,	&cMainWindow::onPersonRemoved);
	connect(ui->m_lpToolBoxPerson,						&cToolBoxPerson::personEdited,			this,	&cMainWindow::onPersonEdited);
	connect(ui->m_lpToolBoxPerson,						&cToolBoxPerson::personListChanged,		this,	&cMainWindow::onPersonListChanged);

	connect(ui->m_lpToolBoxLocation,					&cToolBoxLocation::locationAdded,		this,	&cMainWindow::onLocationAdded);
	connect(ui->m_lpToolBoxLocation,					&cToolBoxLocation::locationRemoved,		this,	&cMainWindow::onLocationRemoved);
	connect(ui->m_lpToolBoxLocation,					&cToolBoxLocation::locationEdited,		this,	&cMainWindow::onLocationEdited);
	connect(ui->m_lpToolBoxLocation,					&cToolBoxLocation::locationListChanged,	this,	&cMainWindow::onLocationListChanged);

	connect(m_lpFilterPanel,							&cFilterPanel::titleChanged,			this,	&cMainWindow::onFilterTitleChanged);
	connect(m_lpFilterPanel,							&cFilterPanel::personChanged,			this,	&cMainWindow::onFilterPersonChanged);
	connect(m_lpFilterPanel,							&cFilterPanel::locationChanged,			this,	&cMainWindow::onFilterLocationChanged);
	connect(m_lpFilterPanel,							&cFilterPanel::tagChanged,				this,	&cMainWindow::onFilterTagChanged);
}

void cMainWindow::createContextActions()
{
	m_lpChangeTitleAction		= new QAction(tr("change title"), this);
	m_lpChangeTitleAction->setStatusTip(tr("change the title of this picture(s)"));
	connect(m_lpChangeTitleAction,		&QAction::triggered,	this,	&cMainWindow::onChangeTitle);

	m_lpChangeDateAction		= new QAction(tr("change date"), this);
	m_lpChangeDateAction->setStatusTip(tr("change the date of this pictures"));
	connect(m_lpChangeDateAction,		&QAction::triggered,	this,	&cMainWindow::onChangeDate);

	m_lpChangeDateTimeAction	= new QAction(tr("change date and time"), this);
	m_lpChangeDateTimeAction->setStatusTip(tr("change the date and time of this picture"));
	connect(m_lpChangeDateTimeAction,	&QAction::triggered,	this,	&cMainWindow::onChangeDateTime);

	m_lpSetHDRAction			= new QAction(tr("set HDR"), this);
	m_lpSetHDRAction->setStatusTip(tr("set this picture(s) to HDR"));
	connect(m_lpSetHDRAction,			&QAction::triggered,	this,	&cMainWindow::onSetHDR);

	m_lpUnsetHDRAction			= new QAction(tr("unset HDR"), this);
	m_lpUnsetHDRAction->setStatusTip(tr("unset this picture(s) from HDR"));
	connect(m_lpUnsetHDRAction,			&QAction::triggered,	this,	&cMainWindow::onUnsetHDR);
}

void cMainWindow::createFileActions()
{
	m_lpFileMenu				= menuBar()->addMenu(tr("&File"));
	m_lpFileToolBar				= addToolBar(tr("File Actions"));

	const QIcon	newIcon			= QIcon::fromTheme("document-new");
	m_lpFileNewAction			= m_lpFileMenu->addAction(newIcon, tr("&New"), this, &cMainWindow::onFileNew);
	m_lpFileToolBar->addAction(m_lpFileNewAction);
	m_lpFileNewAction->setPriority(QAction::LowPriority);
	m_lpFileNewAction->setShortcut(QKeySequence::New);

	const QIcon	openIcon		= QIcon::fromTheme("document-open");
	m_lpFileOpenAction			= m_lpFileMenu->addAction(openIcon, tr("&Open..."), this, &cMainWindow::onFileOpen);
	m_lpFileOpenAction->setShortcut(QKeySequence::Open);
	m_lpFileToolBar->addAction(m_lpFileOpenAction);

	m_lpFileSaveAsAction		= m_lpFileMenu->addAction(tr("Save &As..."), this, &cMainWindow::onFileSaveAs);
	m_lpFileSaveAsAction->setPriority(QAction::LowPriority);
	m_lpFileMenu->addSeparator();

	m_lpFileImportAction		= m_lpFileMenu->addAction(tr("&Import..."), this, &cMainWindow::onFileImport);
	m_lpFileToolBar->addAction(m_lpFileImportAction);

	m_lpFileExportAction		= m_lpFileMenu->addAction(tr("&Export..."), this, &cMainWindow::onFileExport);
	m_lpFileToolBar->addAction(m_lpFileExportAction);

	m_lpFileMenu->addSeparator();

	for(int i = 0; i < MaxRecentFiles;i++)
	{
		m_lpRecentFileAction[i]	= new QAction(this);
		m_lpRecentFileAction[i]->setVisible(false);
		m_lpFileMenu->addAction(m_lpRecentFileAction[i]);
		connect(m_lpRecentFileAction[i], &QAction::triggered, this, &cMainWindow::openRecentFile);
	}
	m_lpSeparatorRecent			= m_lpFileMenu->addSeparator();
	m_lpSeparatorRecent->setVisible(false);

	m_lpFileQuitAction			= m_lpFileMenu->addAction(tr("&Quit"), this, &QWidget::close);
	m_lpFileQuitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
}

void cMainWindow::loadData(bool bProgressBar)
{
	m_bLoading	= true;

	m_personList.clear();
	m_personList.load(m_lpSplashScreen, bProgressBar ? m_lpProgressBar : nullptr);

	m_locationList.clear();
	m_locationList.load(m_lpSplashScreen, bProgressBar ? m_lpProgressBar : nullptr);

	m_tagList.clear();
	m_tagList.load(m_lpSplashScreen, bProgressBar ? m_lpProgressBar : nullptr);

	m_pictureList.clear();
	if(bProgressBar)
		m_lpProgressBar->setVisible(true);
	m_pictureList.load(m_personList, m_locationList, m_tagList, m_lpSplashScreen, bProgressBar ? m_lpProgressBar : nullptr);
	if(bProgressBar)
		m_lpProgressBar->setVisible(false);

	displayData();

	m_bLoading	= false;
}

void cMainWindow::displayData()
{
	m_lpThumbnailViewModel->clear();
	m_lpFolderViewModel->clear();
	ui->m_lpToolBoxPerson->clearPersonList();
	ui->m_lpToolBoxLocation->clearLocationList();
	ui->m_lpToolBoxTags->clearTagList();

	ui->m_lpStatusBar->showMessage(tr("refreshing..."));
	qApp->processEvents();

	ui->m_lpToolBoxPerson->setPersonList(&m_personList);
	ui->m_lpToolBoxLocation->setLocationList(&m_locationList);
	ui->m_lpToolBoxTags->setTagList(&m_tagList);

	m_lpFilterPanel->setTitleList(m_pictureList.titleList());
	m_lpFilterPanel->setPersonList(&m_personList);
	m_lpFilterPanel->setLocationList(&m_locationList);
	m_lpFilterPanel->setTagList(&m_tagList);

	m_lpRootItem	= new QStandardItem("library");
	m_lpFolderViewModel->appendRow(m_lpRootItem);

	for(int x = 0;x < m_pictureList.count();x++)
	{
		QIcon			icon;

		if(m_pictureList[x]->thumbnail().width() != THUMBNAIL_WIDTH || m_pictureList[x]->thumbnail().height() != THUMBNAIL_HEIGHT)
		{
			QImage			thumbnail(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, m_pictureList[x]->thumbnail().format());
			thumbnail.fill(Qt::black);

			QPainter		painter(&thumbnail);
			painter.drawImage((THUMBNAIL_WIDTH-m_pictureList[x]->thumbnail().width())/2, (THUMBNAIL_HEIGHT-m_pictureList[x]->thumbnail().height())/2, m_pictureList[x]->thumbnail());
			painter.end();
			icon	= QIcon(QPixmap::fromImage(thumbnail));
		}
		else
			icon	= QIcon(QPixmap::fromImage(m_pictureList[x]->thumbnail()));

		if(icon.isNull())
		{
			QPixmap		pixmap(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT);
			QPainter	painter(&pixmap);
			painter.setBrush(Qt::black);
			painter.drawRect(0, 0, THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT);
			painter.end();
			icon	= QIcon(pixmap);
		}


		QStandardItem*	lpItem		= new QStandardItem(icon, m_pictureList[x]->fileName());
		lpItem->setTextAlignment(Qt::AlignCenter);
		lpItem->setData(QVariant::fromValue(m_pictureList[x]));
		m_lpThumbnailViewModel->appendRow(lpItem);

		insertPath(m_pictureList[x]->filePath(), m_lpRootItem);
	}

	ui->m_lpFolderView->expandAll();

	m_lpFolderSortFilterProxyModel->sort(0);
	m_lpThumbnailSortFilterProxyModel->sort(0);

	m_lpFilterPanel->onTitleChanged();
	m_lpFilterPanel->onPersonChanged();
	m_lpFilterPanel->onLocationChanged();
	m_lpFilterPanel->onTagChanged();

	ui->m_lpStatusBar->showMessage(tr("done."), 3);

	m_lpThumbnailSortFilterProxyModel->invalidate();

	showCount();
}

QStandardItem*	findItem(QStandardItemModel* lpModel, QModelIndex parent, const QString& text)
{
	for(int x = 0;x < lpModel->rowCount(parent);x++)
	{
		QModelIndex	index	= lpModel->index(x, 0, parent);
		if(lpModel->data(index, Qt::UserRole+1).toString() == text)
		{
			return(lpModel->itemFromIndex(index));
		}

		if(lpModel->hasChildren(index))
		{
			QStandardItem*	lpItem	= findItem(lpModel, index, text);
			if(lpItem)
				return(lpItem);
		}
	}
	return(nullptr);
}

void cMainWindow::cleanFolderTree(const QString& folder)
{
	if(m_pictureList.hasPath(folder))
		return;

	QStandardItem*	lpItem	= findItem(m_lpFolderViewModel, QModelIndex(), folder);

	if(!lpItem)
		return;

	if(lpItem->hasChildren())
		return;

	QModelIndex	indexSource	= m_lpFolderViewModel->indexFromItem(lpItem);
	QModelIndex	indexParent	= indexSource.parent();

	QString		szFolder	= folder;

	while(indexParent.isValid() && !folder.isEmpty())
	{
		m_lpFolderViewModel->removeRow(indexSource.row(), indexParent);

		if(!szFolder.contains("/"))
			break;

		szFolder	= szFolder.left(szFolder.lastIndexOf("/"));

		indexSource	= indexParent;
		indexParent	= indexSource.parent();
		QStandardItem*	lpItem	= m_lpFolderViewModel->itemFromIndex(indexSource);
		if(!lpItem)
			break;

		if(m_pictureList.hasPath(lpItem->data(Qt::UserRole+1).toString()))
			break;

//		if(indexSource.child(0, 0).isValid())
		if(m_lpFolderViewModel->index(0, 0, indexSource).isValid())
			break;
	}

	QDir	dir;
	szFolder	= m_pictureLibrary.rootPath() + "/" + folder;

	while(szFolder.length() > m_pictureLibrary.rootPath().length())
	{
		dir.setPath(szFolder);
		if(dir.isEmpty())
			dir.rmdir(szFolder);
		else
			break;

		szFolder	= szFolder.left(szFolder.lastIndexOf("/"));
	}
}

void cMainWindow::showCount()
{
	qint32	iCount			= m_lpThumbnailViewModel->rowCount();
	qint32	iFilter			= m_lpThumbnailSortFilterProxyModel->rowCount();
	qint32	iSelected		= ui->m_lpThumbnailView->selectionModel()->selectedRows().count();

	ui->m_lpStatusBar->showMessage(QString("count: %1, filter: %2, selected: %3").arg(iCount).arg(iFilter).arg(iSelected));
}

void cMainWindow::onThumbnailSelected(const QItemSelection& /*selection*/, const QItemSelection& /*previous*/)
{
	cPictureList	pictureList;

	for(int x = 0;x < ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count();x++)
	{
		QModelIndex		index	= ui->m_lpThumbnailView->selectionModel()->selectedIndexes()[x];
		if(!index.isValid())
			return;

		pictureList.append(m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>());
	}
	ui->m_lpToolBoxInfo->setPicture(pictureList);
	ui->m_lpToolBoxPerson->setPicture(pictureList);
	ui->m_lpToolBoxLocation->setPicture(pictureList);
	ui->m_lpToolBoxTags->setPicture(pictureList);

	showCount();
}

void cMainWindow::onThumbnailDoubleClicked(const QModelIndex& index)
{
	if(!index.isValid())
		return;

	cPicture*		lpPicture	= m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>();
	QFile			file(m_pictureLibrary.rootPath() + "/" + lpPicture->filePath() + "/" + lpPicture->fileName());

	if(!file.exists())
		return;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	cImageViewer	imageViewer(this);

	cImage			image(file.fileName());
	QApplication::restoreOverrideCursor();

	if(image.isNull())
		return;

	imageViewer.setImage(&image);
	imageViewer.exec();
}

void cMainWindow::onFolderSelected(const QItemSelection& /*selection*/, const QItemSelection& /*previous*/)
{
	if(m_bLoading)
		return;

	QModelIndex		index	= ui->m_lpFolderView->selectionModel()->selectedIndexes()[0];
	if(!index.isValid())
		return;

	m_lpThumbnailSortFilterProxyModel->setFilterPath(m_lpFolderSortFilterProxyModel->data(index, Qt::UserRole+1).toString());

	showCount();
}

void cMainWindow::setCurrentFile(const QString& fileName)
{
	QSettings	settings;
	QStringList	files	= settings.value("file/recentFiles").toStringList();
	files.removeAll(fileName);
	files.prepend(fileName);
	while(files.size() > MaxRecentFiles)
		files.removeLast();

	settings.setValue("file/recentFiles", files);

	updateRecentFileActions();
}

void cMainWindow::updateRecentFileActions()
{
	QSettings	settings;
	QStringList	files			= settings.value("file/recentFiles").toStringList();

	int			numRecentFiles	= qMin(files.size(), static_cast<int>(MaxRecentFiles));

	for(int i = 0; i < numRecentFiles; i++)
	{
		QString	text	= tr("&%1 %2").arg(i + 1).arg(QFileInfo(files[i]).fileName());
		m_lpRecentFileAction[i]->setText(text);
		m_lpRecentFileAction[i]->setData(files[i]);
		m_lpRecentFileAction[i]->setVisible(true);
	}

	for(int j = numRecentFiles; j < MaxRecentFiles; j++)
		m_lpRecentFileAction[j]->setVisible(false);

	m_lpSeparatorRecent->setVisible(numRecentFiles > 0);
}

void cMainWindow::openRecentFile()
{
	QAction*	lpAction	= qobject_cast<QAction*>(sender());
	if(lpAction)
	{
		QSettings	settings;
		QString		szPath	= lpAction->data().toString();
		if(szPath.isEmpty())
			return;

		if(!m_pictureLibrary.openDatabase(szPath))
			return;

		loadData(true);

		setCurrentFile(szPath);
		m_szOldPath	= szPath;
		settings.setValue("file/lastPath", QVariant::fromValue(m_szOldPath));

		//		updateWindowTitle();
	}
}

void cMainWindow::onFileNew()
{
//	if(m_bSomethingChanged)
//	{
//		switch(QMessageBox::question(this, tr("Save"), m_lpStoryBook->title() + tr(" has been changed.\nDo you want to save?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
//		{
//		case QMessageBox::Yes:
//			if(!onFileSave())
//				return;
//			break;
//		case QMessageBox::No:
//			break;
//		case QMessageBox::Cancel:
//			return;
//		default:
//			return;
//		}
//	}

//	ui->m_lpMdiArea->closeAllSubWindows();

//	if(m_lpStoryBook)
//		delete m_lpStoryBook;

//	m_lpStoryBook	= new cStoryBook;

//	m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
//	m_lpStoryBook->fillCharacterList(ui->m_lpCharacterList);
//	m_lpStoryBook->fillPlaceList(ui->m_lpPlaceList);
//	m_lpStoryBook->fillObjectList(ui->m_lpObjectList);
//	m_lpStoryBook->fillRechercheList(ui->m_lpRechercheList);

//	updateWindowTitle();
}

void cMainWindow::onFileOpen()
{
	QSettings	settings;
	QString		szPath	= settings.value("file/lastPath", QDir::homePath()).toString();
	szPath	= QFileDialog::getExistingDirectory(this, tr("Open Database"), szPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if(szPath.isEmpty())
		return;

	if(!m_pictureLibrary.openDatabase(szPath))
		return;

	loadData(true);

	setCurrentFile(szPath);
	m_szOldPath	= szPath;
	settings.setValue("file/lastPath", QVariant::fromValue(m_szOldPath));

//	updateWindowTitle();
}

bool cMainWindow::onFileSaveAs()
{
//	QString	szProjectName	= getProjectSaveName();
//	if(szProjectName.isEmpty())
//		return(false);

//	QFile	file(szProjectName);
//	if(file.exists())
//		file.remove();

//	if(!m_lpStoryBook->saveAs(szProjectName))
//		return(false);

//	m_bSomethingChanged	= false;
//	setCurrentFile(szProjectName);
//	updateWindowTitle();

	return(true);
}

void cMainWindow::onFileImport()
{
	cImportDialog	importDialog(m_pictureLibrary.rootPath(), m_pictureList, this);

	importDialog.exec();
	if(importDialog.hasImported())
		displayData();

	showCount();
}

void cMainWindow::onFileExport()
{
	cExportDialog	exportDialog(this);
	if(exportDialog.exec() == QDialog::Rejected)
		return;
}

void cMainWindow::onThumbnailViewContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	menu.addAction(m_lpChangeTitleAction);

	if(ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count() != 1)
		menu.addAction(m_lpChangeDateAction);
	else
		menu.addAction(m_lpChangeDateTimeAction);

	menu.addAction(m_lpSetHDRAction);
	menu.addAction(m_lpUnsetHDRAction);

	menu.exec(ui->m_lpThumbnailView->mapToGlobal(pos));
}

void cMainWindow::onChangeTitle()
{
	QModelIndex			index		= ui->m_lpThumbnailView->selectionModel()->selectedIndexes()[0];
	if(!index.isValid())
		return;

	cPicture*			lpPicture	= m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>();
	QString				szCurTitle	= lpPicture->title();
	QList<cPicture*>	pictureList;

	pictureList.append(lpPicture);

	for(int x = 1;x < ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count();x++)
	{
		index				= ui->m_lpThumbnailView->selectionModel()->selectedIndexes()[x];
		if(!index.isValid())
			return;

		lpPicture			= m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>();
		if(lpPicture->title() != szCurTitle)
			szCurTitle	= "";

		pictureList.append(lpPicture);
	}

	cComboPicker	comboPicker(this);
	comboPicker.setList(m_pictureList.titleList());
	comboPicker.setEditable(true);
	comboPicker.setWindowTitle("Enter new title");
	comboPicker.setSelection(szCurTitle);
	if(comboPicker.exec() == QDialog::Rejected)
		return;

	QString	szNewTitle	= comboPicker.selection();

	for(int x = 0;x < pictureList.count();x++)
	{
		cPicture*	lpPicture	= pictureList[x];
		QString		szPath		= picture2Path(lpPicture, QDateTime(), szNewTitle);

		if(copyFile(nullptr, m_pictureLibrary.rootPath() + "/" +  lpPicture->filePath() + "/" + lpPicture->fileName(),
					m_pictureLibrary.rootPath() + "/" +  szPath + "/" + lpPicture->fileName(), true))
		{
			QString	szOldPath	= lpPicture->filePath();
			lpPicture->setTitle(szNewTitle);
			lpPicture->setFilePath(szPath);

			lpPicture->toDB();
			insertPath(szPath, m_lpRootItem);
			cleanFolderTree(szOldPath);
		}
	}
	m_lpFolderSortFilterProxyModel->sort(0);
	m_lpThumbnailSortFilterProxyModel->invalidate();
	showCount();
}

void cMainWindow::onChangeDate()
{
	QModelIndex			index		= ui->m_lpThumbnailView->selectionModel()->selectedIndexes()[0];
	if(!index.isValid())
		return;

	cPicture*			lpPicture	= m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>();
	QDate				curDate		= lpPicture->dateTime().date();
	QList<cPicture*>	pictureList;

	pictureList.append(lpPicture);

	for(int x = 1;x < ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count();x++)
	{
		index				= ui->m_lpThumbnailView->selectionModel()->selectedIndexes()[x];
		if(!index.isValid())
			return;

		lpPicture			= m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>();
		if(lpPicture->dateTime().date() != curDate)
			curDate	= QDate();

		pictureList.append(lpPicture);
	}

	cDatePicker		datePicker(this);
	datePicker.setDate(curDate);
	if(datePicker.exec() == QDialog::Rejected)
		return;

	QDate	newDate	= datePicker.date();
	if(!newDate.isValid())
		return;

	for(int x = 0;x < pictureList.count();x++)
	{
		cPicture*	lpPicture	= pictureList[x];
		QDateTime	dateTime	= lpPicture->dateTime();
		dateTime.setDate(newDate);
		QString		szPath		= picture2Path(lpPicture, dateTime);

		if(copyFile(nullptr, m_pictureLibrary.rootPath() + "/" +  lpPicture->filePath() + "/" + lpPicture->fileName(),
					m_pictureLibrary.rootPath() + "/" +  szPath + "/" + lpPicture->fileName(), true))
		{
			QString	szOldPath	= lpPicture->filePath();
			lpPicture->setDateTime(dateTime);
			lpPicture->setFilePath(szPath);

			lpPicture->toDB();
			insertPath(szPath, m_lpRootItem);
			cleanFolderTree(szOldPath);
		}
	}
	m_lpFolderSortFilterProxyModel->sort(0);
	m_lpThumbnailSortFilterProxyModel->invalidate();
	showCount();
}

void cMainWindow::onChangeDateTime()
{
	if(ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count() != 1)
		return;

	QModelIndex			index				= ui->m_lpThumbnailView->selectionModel()->selectedIndexes()[0];
	if(!index.isValid())
		return;

	cPicture*			lpPicture			= m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>();

	if(lpPicture->dateTime().isValid())
	{
		cDateTimePicker	dateTimePicker;
		dateTimePicker.setWindowTitle("Date");
		dateTimePicker.setText(QString(tr("Please set a new date for \"%1\".").arg(lpPicture->filePath() + "/" + lpPicture->fileName())));
		dateTimePicker.setImage(lpPicture->thumbnail());

		dateTimePicker.setDateTime(lpPicture->dateTime());
		if(dateTimePicker.exec() == QDialog::Rejected)
			return;

		QString	szPath	= picture2Path(lpPicture, dateTimePicker.dateTime());

		if(copyFile(nullptr, m_pictureLibrary.rootPath() + "/" +  lpPicture->filePath() + "/" + lpPicture->fileName(),
					m_pictureLibrary.rootPath() + "/" +  szPath + "/" + lpPicture->fileName(), true))
		{
			QString	szOldPath	= lpPicture->filePath();
			lpPicture->setDateTime(dateTimePicker.dateTime());
			lpPicture->setFilePath(szPath);

			lpPicture->toDB();
			insertPath(szPath, m_lpRootItem);
			cleanFolderTree(szOldPath);
			m_lpFolderSortFilterProxyModel->sort(0);

			m_lpThumbnailSortFilterProxyModel->invalidate();
		}
		showCount();
	}
}

void cMainWindow::onSetHDR()
{
	QModelIndex			index;
	cPicture*			lpPicture;
	QList<cPicture*>	pictureList;

	for(int x = 0;x < ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count();x++)
	{
		index				= ui->m_lpThumbnailView->selectionModel()->selectedIndexes()[x];
		if(!index.isValid())
			return;

		lpPicture			= m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>();
		pictureList.append(lpPicture);
	}

	for(int x = 0;x < pictureList.count();x++)
	{
		cPicture*	lpPicture	= pictureList[x];
		QString		szPath		= picture2Path(lpPicture, QDateTime(), QString(), 1);

		if(copyFile(nullptr, m_pictureLibrary.rootPath() + "/" +  lpPicture->filePath() + "/" + lpPicture->fileName(),
					m_pictureLibrary.rootPath() + "/" +  szPath + "/" + lpPicture->fileName(), true))
		{
			QString	szOldPath	= lpPicture->filePath();
			lpPicture->setHDR(true);
			lpPicture->setFilePath(szPath);

			lpPicture->toDB();
			insertPath(szPath, m_lpRootItem);
			cleanFolderTree(szOldPath);
		}
	}
	m_lpFolderSortFilterProxyModel->sort(0);
	m_lpThumbnailSortFilterProxyModel->invalidate();
}

void cMainWindow::onUnsetHDR()
{
	QModelIndex			index;
	cPicture*			lpPicture;
	QList<cPicture*>	pictureList;

	for(int x = 0;x < ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count();x++)
	{
		index				= ui->m_lpThumbnailView->selectionModel()->selectedIndexes()[x];
		if(!index.isValid())
			return;

		lpPicture			= m_lpThumbnailSortFilterProxyModel->data(index, Qt::UserRole+1).value<cPicture*>();
		pictureList.append(lpPicture);
	}

	for(int x = 0;x < pictureList.count();x++)
	{
		cPicture*	lpPicture	= pictureList[x];
		QString		szPath		= picture2Path(lpPicture, QDateTime(), QString(), 0);

		if(copyFile(nullptr, m_pictureLibrary.rootPath() + "/" +  lpPicture->filePath() + "/" + lpPicture->fileName(),
					m_pictureLibrary.rootPath() + "/" +  szPath + "/" + lpPicture->fileName(), true))
		{
			QString	szOldPath	= lpPicture->filePath();
			lpPicture->setHDR(false);
			lpPicture->setFilePath(szPath);

			lpPicture->toDB();
			insertPath(szPath, m_lpRootItem);
			cleanFolderTree(szOldPath);
		}
	}
	m_lpFolderSortFilterProxyModel->sort(0);
	m_lpThumbnailSortFilterProxyModel->invalidate();
}

void cMainWindow::onTagAdded(cTag* /*lpTag*/)
{
}

void cMainWindow::onTagRemoved(cTag* /*lpTag*/)
{
}

void cMainWindow::onTagEdited(cTag* /*lpTag*/)
{
}

void cMainWindow::onTagListChanged()
{
	m_lpFilterPanel->updateTagList();
	showCount();
}

void cMainWindow::onPersonAdded(cPerson* /*lpPerson*/)
{
}

void cMainWindow::onPersonRemoved(cPerson* /*lpPerson*/)
{
}

void cMainWindow::onPersonEdited(cPerson* /*lpPerson*/)
{
}

void cMainWindow::onPersonListChanged()
{
	m_lpFilterPanel->updatePersonList();
	showCount();
}

void cMainWindow::onLocationAdded(cLocation* /*lpLocation*/)
{
}

void cMainWindow::onLocationRemoved(cLocation* /*lpLocation*/)
{
}

void cMainWindow::onLocationEdited(cLocation* /*lpLocation*/)
{
}

void cMainWindow::onLocationListChanged()
{
	m_lpFilterPanel->updateLocationList();
}

void cMainWindow::onFilterTitleChanged(QStringList titleList)
{
	if(m_bLoading)
		return;

	m_lpThumbnailSortFilterProxyModel->setTitleList(titleList);
	showCount();
}

void cMainWindow::onFilterPersonChanged(QList<qint32> idList, bool bAnd)
{
	if(m_bLoading)
		return;

	m_lpThumbnailSortFilterProxyModel->setPersonList(idList, bAnd);
	showCount();
}

void cMainWindow::onFilterLocationChanged(QList<qint32> idList, bool bAnd)
{
	if(m_bLoading)
		return;

	m_lpThumbnailSortFilterProxyModel->setLocationList(idList, bAnd);
	showCount();
}

void cMainWindow::onFilterTagChanged(QList<qint32> idList, bool bAnd)
{
	if(m_bLoading)
		return;

	m_lpThumbnailSortFilterProxyModel->setTagList(idList, bAnd);
	showCount();
}
