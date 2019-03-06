/*!
 \file cmainwindow.cpp

*/

#include "common.h"

#include "cmainwindow.h"
#include "cimportdialog.h"

#include "cdatetimepicker.h"

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


cMainWindow::cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
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
	loadData();

	updateRecentFileActions();
}

cMainWindow::~cMainWindow()
{
	delete m_lpThumbnailViewModel;
	delete m_lpFolderViewModel;
	delete m_lpThumbnailSortFilterProxyModel;
	delete m_lpFolderSortFilterProxyModel;

	delete ui;
}

void cMainWindow::initUI()
{
	ui->setupUi(this);

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
}

void cMainWindow::createActions()
{
	setToolButtonStyle(Qt::ToolButtonFollowStyle);

	createFileActions();
	createContextActions();

	connect(ui->m_lpThumbnailView->selectionModel(),	&QItemSelectionModel::selectionChanged,	this,	&cMainWindow::onThumbnailSelected);
	connect(ui->m_lpFolderView->selectionModel(),		&QItemSelectionModel::selectionChanged,	this,	&cMainWindow::onFolderSelected);

	connect(ui->m_lpThumbnailView,						&QListView::customContextMenuRequested,	this,	&cMainWindow::onThumbnailViewContextMenu);
}

void cMainWindow::createContextActions()
{
	m_lpChangeDateAction	= new QAction(tr("change date"), this);
	m_lpChangeDateAction->setStatusTip(tr("change the date of this picture"));
	connect(m_lpChangeDateAction,	&QAction::triggered,	this,	&cMainWindow::onChangeDate);
}

void cMainWindow::loadData(bool bProgressBar)
{
	m_bLoading	= true;

	m_pictureList.clear();
	m_pictureList.load(m_lpSplashScreen, bProgressBar ? m_lpProgressBar : nullptr);

	displayData();

	m_bLoading	= false;
}

void cMainWindow::displayData()
{
	m_lpThumbnailViewModel->clear();
	m_lpFolderViewModel->clear();
	ui->m_lpStatusBar->showMessage(tr("refreshing..."));
	qApp->processEvents();

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
		lpItem->setData(QVariant::fromValue(m_pictureList[x]->filePath()), Qt::UserRole+2);
		m_lpThumbnailViewModel->appendRow(lpItem);

		insertPath(m_pictureList[x]->filePath(), m_lpRootItem);
	}

	ui->m_lpFolderView->expandAll();

	m_lpFolderSortFilterProxyModel->sort(0);
	m_lpThumbnailSortFilterProxyModel->sort(0);

	ui->m_lpStatusBar->showMessage(tr("done."), 3);
}

QStandardItem*	findItem(QStandardItemModel* lpModel, QModelIndex parent, const QString& text)
{
//	qDebug() << lpModel->rowCount(parent);

	for(int x = 0;x < lpModel->rowCount(parent);x++)
	{
//		qDebug() << lpModel->data(index, Qt::UserRole+2).toString();
		QModelIndex	index	= lpModel->index(x, 0, parent);
		if(lpModel->data(index, Qt::UserRole+2).toString() == text)
			return(lpModel->itemFromIndex(index));

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
	qDebug() << indexSource.row();

	QStandardItem*	lpItem1	= m_lpFolderViewModel->itemFromIndex(indexSource);
	qDebug() << lpItem1->text();

	QModelIndex	indexFilter	= m_lpFolderSortFilterProxyModel->mapFromSource(indexSource);
	qDebug() << indexFilter.row();

	qDebug() << lpItem->text();

	if(indexFilter.isValid())
		m_lpFolderSortFilterProxyModel->removeRow(indexFilter.row());
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

	event->accept();
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

	m_lpFileMenu->addSeparator();

	m_lpFileImportAction		= m_lpFileMenu->addAction(tr("&Import..."), this, &cMainWindow::onFileImport);
	m_lpFileToolBar->addAction(m_lpFileImportAction);

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

void cMainWindow::onThumbnailSelected(const QItemSelection& /*selection*/, const QItemSelection& /*previous*/)
{
	cToolBoxInfo*	lpToolBoxInfo	= static_cast<cToolBoxInfo*>(ui->m_lpToolBox->widget(0));

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

void cMainWindow::onFolderSelected(const QItemSelection& /*selection*/, const QItemSelection& /*previous*/)
{
	if(m_bLoading)
		return;

	QModelIndex		index	= ui->m_lpFolderView->selectionModel()->selectedIndexes()[0];
	if(!index.isValid())
		return;

	m_lpThumbnailSortFilterProxyModel->setFilterPath(m_lpFolderSortFilterProxyModel->data(index, Qt::UserRole+2).toString());
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
//		if(m_lpStoryBook)
//		{
//			if(m_bSomethingChanged)
//			{
//				switch(QMessageBox::question(this, tr("Save"), m_lpStoryBook->title() + tr(" has been changed.\nDo you want to save?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
//				{
//				case QMessageBox::Yes:
//					if(!onFileSave())
//						return;
//					break;
//				case QMessageBox::No:
//					break;
//				case QMessageBox::Cancel:
//					return;
//				default:
//					return;
//				}
//			}
//		}

//		QString	szProjectName	= lpAction->data().toString();
//		if(szProjectName.isEmpty())
//			return;

//		delete m_lpStoryBook;

//		m_lpStoryBook	= new cStoryBook(szProjectName);

//		m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
//		m_lpStoryBook->fillCharacterList(ui->m_lpCharacterList);
//		m_lpStoryBook->fillPlaceList(ui->m_lpPlaceList);
//		m_lpStoryBook->fillObjectList(ui->m_lpObjectList);
//		m_lpStoryBook->fillRechercheList(ui->m_lpRechercheList);

//		setCurrentFile(szProjectName);
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
//	if(m_lpStoryBook)
//	{
//		if(m_bSomethingChanged)
//		{
//			switch(QMessageBox::question(this, tr("Save"), m_lpStoryBook->title() + tr(" has been changed.\nDo you want to save?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
//			{
//			case QMessageBox::Yes:
//				if(!onFileSave())
//					return;
//				break;
//			case QMessageBox::No:
//				break;
//			case QMessageBox::Cancel:
//				return;
//			default:
//				return;
//			}
//		}
//	}

//	QString	szProjectName	= getProjectLoadName();
//	if(szProjectName.isEmpty())
//		return;

//	ui->m_lpMdiArea->closeAllSubWindows();

//	if(m_lpStoryBook)
//		delete m_lpStoryBook;

//	m_lpStoryBook	= new cStoryBook(szProjectName);

//	m_lpStoryBook->fillOutlineList(ui->m_lpOutlineList);
//	m_lpStoryBook->fillCharacterList(ui->m_lpCharacterList);
//	m_lpStoryBook->fillPlaceList(ui->m_lpPlaceList);
//	m_lpStoryBook->fillObjectList(ui->m_lpObjectList);
//	m_lpStoryBook->fillRechercheList(ui->m_lpRechercheList);

//	setCurrentFile(szProjectName);
//	updateWindowTitle();
}

void cMainWindow::onFileImport()
{
	cImportDialog	importDialog(m_pictureLibrary.rootPath(), m_pictureList, this);

	importDialog.exec();
	if(importDialog.hasImported())
		displayData();
}

void cMainWindow::onThumbnailViewContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	if(ui->m_lpThumbnailView->selectionModel()->selectedIndexes().count() != 1)
		return;

	menu.addAction(m_lpChangeDateAction);
	menu.exec(ui->m_lpThumbnailView->mapToGlobal(pos));
}

void cMainWindow::onChangeDate()
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

		lpPicture->setDateTime(dateTimePicker.dateTime());
//		QString			szPath	= QString::number(lpPicture->dateTime().date().year()) + "/" + lpPicture->dateTime().date().toString("yyyy-MM-dd");
		QString			szPath	= picture2Path(lpPicture);
		m_lpThumbnailSortFilterProxyModel->setData(index, QVariant::fromValue(szPath), Qt::UserRole+2);

		if(copyFile(nullptr, m_pictureLibrary.rootPath() + "/" +  lpPicture->filePath() + "/" + lpPicture->fileName(),
					m_pictureLibrary.rootPath() + "/" +  szPath + "/" + lpPicture->fileName(), true))
		{
			QString	szOldPath	= lpPicture->filePath();
			lpPicture->setFilePath(szPath);
			cleanFolderTree(szOldPath);

			lpPicture->toDB();
			insertPath(szPath, m_lpRootItem);
			m_lpFolderSortFilterProxyModel->sort(0);

			m_lpThumbnailSortFilterProxyModel->invalidate();
		}
	}
}
