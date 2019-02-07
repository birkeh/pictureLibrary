#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QLabel>


cMainWindow::cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::cMainWindow),
	m_lpSplashScreen(lpSplashScreen)
{
	initUI();
	createActions();

	cEXIF	exif(&m_exifTagList);
//	exif.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\20181123_125857.jpg");
//	exif.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_1371.CR2");
//	exif.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\tiff\\BSG1.tiff");
//	exif.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_3444.CR2");
//	exif.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_0248_49_50_easyHDR-dramatic-strong.jpg");
//	exif.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_3466_7_8_easyHDR-dramatic-dark.tif");
	exif.fromFile(QDir::homePath() + "\\OneDrive - WINDESIGN\\exif-samples-master\\IMG_0248_49_50_easyHDR-dramatic-strong.jpg");

	QList<QImage>	previewList	= exif.previewList();
	for(int i = 0;i < previewList.count();i++)
	{
		QLabel*	lpLabel	= new QLabel;
		lpLabel->setPixmap(QPixmap::fromImage(previewList[i]));
		ui->m_lpMainLayout->addWidget(lpLabel);
	}
}

cMainWindow::~cMainWindow()
{
	delete ui;
}

void cMainWindow::initUI()
{
	ui->setupUi(this);

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
