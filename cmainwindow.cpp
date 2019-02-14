#include "common.h"

#include "cmainwindow.h"
#include "cimportdialog.h"

#include "ui_cmainwindow.h"

#include <QDebug>
#include <QDir>
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
	delete ui;
}

void cMainWindow::initUI()
{
	ui->setupUi(this);
	m_lpThumbnailViewModel	= new QStandardItemModel;
	ui->m_lpThumbnailView->setModel(m_lpThumbnailViewModel);


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
//	createEditActions();
//	createTextActions();
//	createToolsActions();
//	createWindowActions();
//	createHelpActions();

//	createContextActions();

	connect(ui->m_lpThumbnailView->selectionModel(),	&QItemSelectionModel::selectionChanged,				this,	&cMainWindow::onThumbnailSelected);
//	connect(ui->m_lpMainTab,		&QTabWidget::currentChanged,			this,	&cMainWindow::onMainTabCurrentChanged);
//	connect(ui->m_lpMainTab,		&QTabWidget::tabCloseRequested,			this,	&cMainWindow::onMainTabTabCloseRequested);
//	connect(ui->m_lpMdiArea,		&QMdiArea::subWindowActivated,			this,	&cMainWindow::onMdiAreaSubWindowActivated);

//	connect(ui->m_lpOutlineList,	&QTreeView::doubleClicked,				this,	&cMainWindow::onOutlineDoubleClicked);
//	connect(ui->m_lpCharacterList,	&QTreeView::doubleClicked,				this,	&cMainWindow::onCharacterDoubleClicked);
//	connect(ui->m_lpPlaceList,		&QTreeView::doubleClicked,				this,	&cMainWindow::onPlaceDoubleClicked);
//	connect(ui->m_lpObjectList,		&QTreeView::doubleClicked,				this,	&cMainWindow::onObjectDoubleClicked);
//	connect(ui->m_lpRechercheList,	&QTreeView::doubleClicked,				this,	&cMainWindow::onRechercheDoubleClicked);

//	connect(ui->m_lpOutlineList,	&QTreeView::customContextMenuRequested,	this,	&cMainWindow::onOutlineContextMenu);
//	connect(ui->m_lpCharacterList,	&QTreeView::customContextMenuRequested,	this,	&cMainWindow::onCharacterContextMenu);
//	connect(ui->m_lpPlaceList,		&QTreeView::customContextMenuRequested,	this,	&cMainWindow::onPlaceContextMenu);
//	connect(ui->m_lpObjectList,		&QTreeView::customContextMenuRequested,	this,	&cMainWindow::onObjectContextMenu);
//	connect(ui->m_lpRechercheList,	&QTreeView::customContextMenuRequested,	this,	&cMainWindow::onRechercheContextMenu);

//	connect(ui->m_lpOutlineList,	&cTreeView::dropped,					this,	&cMainWindow::onOutlineDropped);
}

void cMainWindow::loadData(bool bProgressBar)
{
	m_pictureList.clear();
	m_lpThumbnailViewModel->clear();

	m_pictureList.load(m_lpSplashScreen, bProgressBar ? m_lpProgressBar : nullptr);

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

		QStandardItem*	lpItem		= new QStandardItem(icon, m_pictureList[x]->fileName());
		lpItem->setTextAlignment(Qt::AlignCenter);
		lpItem->setData(QVariant::fromValue(m_pictureList[x]));
		m_lpThumbnailViewModel->appendRow(lpItem);
	}
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

//	const QIcon	saveIcon		= QIcon::fromTheme("document-save");
//	m_lpFileSaveAction			= m_lpFileMenu->addAction(saveIcon, tr("&Save"), this, &cMainWindow::onFileSave);
//	m_lpFileSaveAction->setShortcut(QKeySequence::Save);
//	m_lpFileSaveAction->setEnabled(false);
//	m_lpFileToolBar->addAction(m_lpFileSaveAction);

//	m_lpFileSaveAsAction		= m_lpFileMenu->addAction(tr("Save &As..."), this, &cMainWindow::onFileSaveAs);
//	m_lpFileSaveAsAction->setPriority(QAction::LowPriority);
//	m_lpFileMenu->addSeparator();

//#ifndef QT_NO_PRINTER
//	const QIcon	printIcon		= QIcon::fromTheme("document-print");
//	m_lpFilePrintAction			= m_lpFileMenu->addAction(printIcon, tr("&Print..."), this, &cMainWindow::onFilePrint);
//	m_lpFilePrintAction->setPriority(QAction::LowPriority);
//	m_lpFilePrintAction->setShortcut(QKeySequence::Print);
//	m_lpFileToolBar->addAction(m_lpFilePrintAction);

//	const QIcon	filePrintIcon	= QIcon::fromTheme("document-print");
//	m_lpFilePrintPreviewAction	= m_lpFileMenu->addAction(filePrintIcon, tr("Print Preview..."), this, &cMainWindow::onFilePrintPreview);

//	const QIcon	exportPdfIcon	= QIcon::fromTheme("document-pdf");
//	m_lpFileExportPDFAction		= m_lpFileMenu->addAction(exportPdfIcon, tr("&Export PDF..."), this, &cMainWindow::onFilePrintPdf);
//	m_lpFileExportPDFAction->setPriority(QAction::LowPriority);
//	m_lpFileExportPDFAction->setShortcut(Qt::CTRL + Qt::Key_D);
//	m_lpFileToolBar->addAction(m_lpFileExportPDFAction);

//	m_lpFileMenu->addSeparator();
//#endif

//	m_lpFilePropertiesAction	= m_lpFileMenu->addAction(tr("P&roperties..."), this, &cMainWindow::onFileProperties);
//	m_lpFilePropertiesAction->setPriority(QAction::LowPriority);
//	m_lpFileMenu->addSeparator();

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

	QStandardItem*	lpItem			= m_lpThumbnailViewModel->itemFromIndex(ui->m_lpThumbnailView->currentIndex());
	cPicture*		lpPicture		= lpItem->data().value<cPicture*>();
	lpToolBoxInfo->setPicture(lpPicture);
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

	int			numRecentFiles	= qMin(files.size(), (int)MaxRecentFiles);

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
	cImportDialog	importDialog(m_pictureLibrary.rootPath(), this);

	importDialog.exec();
	if(importDialog.hasImported())
	{
		m_lpProgressBar->setVisible(true);
		loadData(true);
		m_lpProgressBar->setVisible(false);
	}
}
