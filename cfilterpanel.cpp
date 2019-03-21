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
	connect(ui->m_lpPersonFilter,	&QGroupBox::toggled,	this,	&cFilterPanel::onPersonFilter);
	connect(ui->m_lpLocationFilter,	&QGroupBox::toggled,	this,	&cFilterPanel::onLocationFilter);
	connect(ui->m_lpTagFilter,		&QGroupBox::toggled,	this,	&cFilterPanel::onTagFilter);

	connect(ui->m_lpPersonAnd,		&QRadioButton::toggled,	this,	&cFilterPanel::onPersonAnd);
	connect(ui->m_lpLocationAnd,	&QRadioButton::toggled,	this,	&cFilterPanel::onLocationAnd);
	connect(ui->m_lpTagsAnd,		&QRadioButton::toggled,	this,	&cFilterPanel::onTagAnd);

	connect(m_lpPersonListModel,	SIGNAL(dataChanged(QModelIndex,	QModelIndex, QVector<int>)),	SLOT(onPersonChanged(QModelIndex, QModelIndex, QVector<int>)));
	connect(m_lpLocationListModel,	SIGNAL(dataChanged(QModelIndex,	QModelIndex, QVector<int>)),	SLOT(onLocationChanged(QModelIndex, QModelIndex, QVector<int>)));
	connect(m_lpTagListModel,		SIGNAL(dataChanged(QModelIndex,	QModelIndex, QVector<int>)),	SLOT(onTagChanged(QModelIndex, QModelIndex, QVector<int>)));
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

	m_lpPersonListModel->sort(0);

	m_bLoading	= false;
}

void cFilterPanel::updatePersonList()
{
	m_bLoading		= true;

	for(cPersonList::iterator i = m_lpPersonList->begin();i != m_lpPersonList->end();i++)
	{
		if(m_lpPersonListModel->findItems((*i)->name()).isEmpty())
		{
			QStandardItem*	lpItem	= new QStandardItem((*i)->name());
			lpItem->setData(QVariant::fromValue(*i), Qt::UserRole+1);
			lpItem->setCheckable(true);
			m_lpPersonListModel->appendRow(lpItem);
		}
	}

	for(int x = m_lpPersonListModel->rowCount()-1;x >= 0;x--)
	{
		if(!m_lpPersonList->find(m_lpPersonListModel->item(x, 0)->text()))
			m_lpPersonListModel->removeRow(x);
	}

	m_lpPersonListModel->sort(0);

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

void cFilterPanel::updateLocationList()
{
	m_bLoading		= true;

	for(cLocationList::iterator i = m_lpLocationList->begin();i != m_lpLocationList->end();i++)
	{
		if(m_lpLocationListModel->findItems((*i)->name()).isEmpty())
		{
			QStandardItem*	lpItem	= new QStandardItem((*i)->name());
			lpItem->setData(QVariant::fromValue(*i), Qt::UserRole+1);
			lpItem->setCheckable(true);
			m_lpLocationListModel->appendRow(lpItem);
		}
	}

	for(int x = m_lpLocationListModel->rowCount()-1;x >= 0;x--)
	{
		if(!m_lpLocationList->find(m_lpLocationListModel->item(x, 0)->text()))
			m_lpLocationListModel->removeRow(x);
	}

	m_lpLocationListModel->sort(0);

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

void cFilterPanel::updateTagList()
{
	m_bLoading		= true;

	for(cTagList::iterator i = m_lpTagList->begin();i != m_lpTagList->end();i++)
	{
		if(m_lpTagListModel->findItems((*i)->name()).isEmpty())
		{
			QStandardItem*	lpItem	= new QStandardItem((*i)->name());
			lpItem->setData(QVariant::fromValue(*i), Qt::UserRole+1);
			lpItem->setCheckable(true);
			m_lpTagListModel->appendRow(lpItem);
		}
	}

	for(int x = m_lpTagListModel->rowCount()-1;x >= 0;x--)
	{
		if(!m_lpTagList->find(m_lpTagListModel->item(x, 0)->text()))
			m_lpTagListModel->removeRow(x);
	}

	m_lpTagListModel->sort(0);

	m_bLoading	= false;
}

void cFilterPanel::onPersonChanged()
{
	if(m_bLoading)
		return;

	QList<qint32>	idList;

	for(int x = 0;x < m_lpPersonListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpPersonListModel->item(x, 0);

		if(lpItem->checkState() == Qt::Checked)
		{
			cPerson*	lpPerson		= lpItem->data(Qt::UserRole+1).value<cPerson*>();
			if(lpPerson)
				idList.append(lpPerson->id());
		}
	}
	emit personChanged(idList, ui->m_lpPersonAnd->isChecked());
}

void cFilterPanel::onPersonAnd(bool /*bToggle*/)
{
	onPersonChanged();
}

void cFilterPanel::onPersonFilter(bool bToggle)
{
	if(bToggle)
		onPersonChanged();
	else
		emit(personChanged(QList<qint32>(), false));
}

void cFilterPanel::onPersonChanged(const QModelIndex& /*topLeft*/, const QModelIndex& /*bottomright*/, const QVector<int>& /*roles*/)
{
	onPersonChanged();
}

void cFilterPanel::onLocationChanged()
{
	if(m_bLoading)
		return;

	QList<qint32>	idList;

	for(int x = 0;x < m_lpLocationListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpLocationListModel->item(x, 0);

		if(lpItem->checkState() == Qt::Checked)
		{
			cLocation*	lpLocation		= lpItem->data(Qt::UserRole+1).value<cLocation*>();
			if(lpLocation)
				idList.append(lpLocation->id());
		}
	}
	emit locationChanged(idList, ui->m_lpLocationAnd->isChecked());
}

void cFilterPanel::onLocationFilter(bool bToggle)
{
	if(bToggle)
		onLocationChanged();
	else
		emit(locationChanged(QList<qint32>(), false));
}

void cFilterPanel::onLocationAnd(bool /*bToggle*/)
{
	onLocationChanged();
}

void cFilterPanel::onLocationChanged(const QModelIndex& /*topLeft*/, const QModelIndex& /*bottomright*/, const QVector<int>& /*roles*/)
{
	onLocationChanged();
}

void cFilterPanel::onTagChanged()
{
	if(m_bLoading)
		return;

	QList<qint32>	idList;

	for(int x = 0;x < m_lpTagListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpTagListModel->item(x, 0);

		if(lpItem->checkState() == Qt::Checked)
		{
			cTag*	lpTag		= lpItem->data(Qt::UserRole+1).value<cTag*>();
			if(lpTag)
				idList.append(lpTag->id());
		}
	}
	emit tagChanged(idList, ui->m_lpTagsAnd->isChecked());
}

void cFilterPanel::onTagFilter(bool bToggle)
{
	if(bToggle)
		onTagChanged();
	else
		emit(tagChanged(QList<qint32>(), false));
}

void cFilterPanel::onTagAnd(bool /*bToggle*/)
{
	onTagChanged();
}

void cFilterPanel::onTagChanged(const QModelIndex& /*topLeft*/, const QModelIndex& /*bottomright*/, const QVector<int>& /*roles*/)
{
	onTagChanged();
}
