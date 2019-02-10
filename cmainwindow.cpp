#include "common.h"

#include "cmainwindow.h"
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
	m_lpSplashScreen(lpSplashScreen)
{
	initUI();
	createActions();
	loadData();
//	cPicture	picture;
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_1371.CR2");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\20181123_125857.jpg");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_1371.CR2");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\tiff\\BSG1.tiff");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_3444.CR2");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_0248_49_50_easyHDR-dramatic-strong.jpg");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_3466_7_8_easyHDR-dramatic-dark.tif");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_0248_49_50_easyHDR-dramatic-strong.jpg");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\DSC_0214.NEF");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\DSC_0215.NEF");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_1652.JPG");
//	picture.toDB();
//	picture.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_1657.JPG");
//	picture.toDB();
}

cMainWindow::~cMainWindow()
{
	delete ui;
}

void cMainWindow::initUI()
{
	ui->setupUi(this);
	m_lpThumbnailViewModel	= new QStandardItemModel;
	ui->m_lpThumbnailView->setModel(m_lpThumbnailViewModel);

	QIcon::setThemeName("TangoMFK");
}

void cMainWindow::createActions()
{
//	setToolButtonStyle(Qt::ToolButtonFollowStyle);
//	createFileActions();
//	createEditActions();
//	createTextActions();
//	createToolsActions();
//	createWindowActions();
//	createHelpActions();

//	createContextActions();

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

void cMainWindow::loadData()
{
	m_pictureList.load();

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

	event->accept();
}
