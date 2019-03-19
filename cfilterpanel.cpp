#include "cfilterpanel.h"
#include "ui_cfilterpanel.h"


cFilterPanel::cFilterPanel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cFilterPanel),
	m_bLoading(false),
	m_lpPersonList(nullptr),
	m_lpLocationList(nullptr),
	m_lpTagList(nullptr)
{
	initUI();
	createActions();
}

cFilterPanel::~cFilterPanel()
{
	delete ui;
}

void cFilterPanel::initUI()
{
	ui->setupUi(this);

	m_lpPersonListModel		= new QStandardItemModel;
	ui->m_lpPersonList->setModel(m_lpPersonListModel);

	m_lpLocationListModel	= new QStandardItemModel;
	ui->m_lpLocationList->setModel(m_lpLocationListModel);

	m_lpTagListModel	= new QStandardItemModel;
	ui->m_lpTagList->setModel(m_lpTagListModel);
}

void cFilterPanel::createActions()
{
}

void cFilterPanel::clearPersonList()
{
	m_lpPersonListModel->clear();
}

void cFilterPanel::setPersonList(cPersonList* lpPersonList)
{
	m_bLoading		= true;

	m_lpPersonList	= lpPersonList;

	for(cPersonList::iterator i = lpPersonList->begin();i != lpPersonList->end();i++)
	{
		QStandardItem*	lpItem	= new QStandardItem((*i)->name());
		lpItem->setData(QVariant::fromValue(*i), Qt::UserRole+1);
		lpItem->setCheckable(true);
		m_lpPersonListModel->appendRow(lpItem);
	}

	m_bLoading	= false;
}

void cFilterPanel::clearLocationList()
{
	m_lpLocationListModel->clear();
}

void cFilterPanel::setLocationList(cLocationList* lpLocationList)
{
	m_bLoading	= true;

	m_lpLocationList	= lpLocationList;

	for(cLocationList::iterator i = lpLocationList->begin();i != lpLocationList->end();i++)
	{
		QStandardItem*	lpItem	= new QStandardItem((*i)->name());
		lpItem->setData(QVariant::fromValue(*i), Qt::UserRole+1);
		lpItem->setCheckable(true);
		m_lpLocationListModel->appendRow(lpItem);
	}

	m_bLoading	= false;
}

void cFilterPanel::clearTagList()
{
	m_lpTagListModel->clear();
}

void cFilterPanel::setTagList(cTagList* lpTagList)
{
	m_bLoading	= true;

	m_lpTagList	= lpTagList;

	for(cTagList::iterator i = lpTagList->begin();i != lpTagList->end();i++)
	{
		QStandardItem*	lpItem	= new QStandardItem((*i)->name());
		lpItem->setData(QVariant::fromValue(*i), Qt::UserRole+1);
		lpItem->setCheckable(true);
		m_lpTagListModel->appendRow(lpItem);
	}

	m_bLoading	= false;
}
