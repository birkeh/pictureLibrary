#include "cfilterpanel.h"
#include "ui_cfilterpanel.h"

#include <QSettings>


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

void cFilterPanel::saveSettings()
{
	QSettings		settings;
	QStringList		szIDs;

	for(int x = 0;x < m_lpTitleListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpTitleListModel->item(x, 0);

		if(lpItem->checkState() == Qt::Checked)
			szIDs.append(lpItem->text());
	}
	settings.setValue("filter/title", QVariant::fromValue(szIDs));
	settings.setValue("filter/titleActive", QVariant::fromValue(ui->m_lpTitleFilter->isChecked()));

	for(int x = 0;x < m_lpPersonListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpPersonListModel->item(x, 0);

		if(lpItem->checkState() == Qt::Checked)
		{
			cPerson*	lpPerson		= lpItem->data(Qt::UserRole+1).value<cPerson*>();
			if(lpPerson)
				szIDs.append(QString::number(lpPerson->id()));
		}
	}
	settings.setValue("filter/person", QVariant::fromValue(szIDs));
	settings.setValue("filter/personActive", QVariant::fromValue(ui->m_lpPersonFilter->isChecked()));
	settings.setValue("filter/personAnd", QVariant::fromValue(ui->m_lpPersonAnd->isChecked()));
	szIDs.clear();

	for(int x = 0;x < m_lpLocationListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpLocationListModel->item(x, 0);

		if(lpItem->checkState() == Qt::Checked)
		{
			cLocation*	lpLocation		= lpItem->data(Qt::UserRole+1).value<cLocation*>();
			if(lpLocation)
				szIDs.append(QString::number(lpLocation->id()));
		}
	}
	settings.setValue("filter/location", QVariant::fromValue(szIDs));
	settings.setValue("filter/locationActive", QVariant::fromValue(ui->m_lpLocationFilter->isChecked()));
	settings.setValue("filter/locationAnd", QVariant::fromValue(ui->m_lpLocationAnd->isChecked()));
	szIDs.clear();

	for(int x = 0;x < m_lpTagListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpTagListModel->item(x, 0);

		if(lpItem->checkState() == Qt::Checked)
		{
			cTag*	lpTag		= lpItem->data(Qt::UserRole+1).value<cTag*>();
			if(lpTag)
				szIDs.append(QString::number(lpTag->id()));
		}
	}
	settings.setValue("filter/tag", QVariant::fromValue(szIDs));
	settings.setValue("filter/tagActive", QVariant::fromValue(ui->m_lpTagFilter->isChecked()));
	settings.setValue("filter/tagAnd", QVariant::fromValue(ui->m_lpTagsAnd->isChecked()));
}

void cFilterPanel::initUI()
{
	ui->setupUi(this);

	m_lpTitleListModel		= new QStandardItemModel;
	ui->m_lpTitleList->setModel(m_lpTitleListModel);

	m_lpPersonListModel		= new QStandardItemModel;
	ui->m_lpPersonList->setModel(m_lpPersonListModel);

	m_lpLocationListModel	= new QStandardItemModel;
	ui->m_lpLocationList->setModel(m_lpLocationListModel);

	m_lpTagListModel	= new QStandardItemModel;
	ui->m_lpTagList->setModel(m_lpTagListModel);

	QSettings	settings;

	ui->m_lpTitleFilter->setChecked(settings.value("filter/titleActive", true).toBool());

	ui->m_lpPersonFilter->setChecked(settings.value("filter/personActive", true).toBool());
	ui->m_lpPersonAnd->setChecked(settings.value("filter/personAnd", true).toBool());
	ui->m_lpPersonOr->setChecked(!settings.value("filter/personAnd", true).toBool());

	ui->m_lpLocationFilter->setChecked(settings.value("filter/locationActive", true).toBool());
	ui->m_lpLocationAnd->setChecked(settings.value("filter/locationAnd", true).toBool());
	ui->m_lpLocationOr->setChecked(!settings.value("filter/locationAnd", true).toBool());

	ui->m_lpTagFilter->setChecked(settings.value("filter/tagActive", true).toBool());
	ui->m_lpTagsAnd->setChecked(settings.value("filter/tagAnd", true).toBool());
	ui->m_lpTagsOr->setChecked(!settings.value("filter/tagAnd", true).toBool());
}

void cFilterPanel::createActions()
{
	connect(ui->m_lpTitleFilter,	&QGroupBox::toggled,	this,	&cFilterPanel::onTitleFilter);
	connect(ui->m_lpPersonFilter,	&QGroupBox::toggled,	this,	&cFilterPanel::onPersonFilter);
	connect(ui->m_lpLocationFilter,	&QGroupBox::toggled,	this,	&cFilterPanel::onLocationFilter);
	connect(ui->m_lpTagFilter,		&QGroupBox::toggled,	this,	&cFilterPanel::onTagFilter);

	connect(ui->m_lpPersonAnd,		&QRadioButton::toggled,	this,	&cFilterPanel::onPersonAnd);
	connect(ui->m_lpLocationAnd,	&QRadioButton::toggled,	this,	&cFilterPanel::onLocationAnd);
	connect(ui->m_lpTagsAnd,		&QRadioButton::toggled,	this,	&cFilterPanel::onTagAnd);

	connect(m_lpTitleListModel,		SIGNAL(dataChanged(QModelIndex,	QModelIndex, QVector<int>)),	SLOT(onTitleChanged(QModelIndex, QModelIndex, QVector<int>)));
	connect(m_lpPersonListModel,	SIGNAL(dataChanged(QModelIndex,	QModelIndex, QVector<int>)),	SLOT(onPersonChanged(QModelIndex, QModelIndex, QVector<int>)));
	connect(m_lpLocationListModel,	SIGNAL(dataChanged(QModelIndex,	QModelIndex, QVector<int>)),	SLOT(onLocationChanged(QModelIndex, QModelIndex, QVector<int>)));
	connect(m_lpTagListModel,		SIGNAL(dataChanged(QModelIndex,	QModelIndex, QVector<int>)),	SLOT(onTagChanged(QModelIndex, QModelIndex, QVector<int>)));
}

void cFilterPanel::clearTitleList()
{
	m_lpTitleListModel->clear();
}

void cFilterPanel::setTitleList(QStringList titleList)
{
	m_bLoading		= true;

	QSettings		settings;
	QStringList		szIDs;

	szIDs			= settings.value("filter/title").toStringList();

	m_lpTitleListModel->clear();

	for(QStringList::iterator i = titleList.begin();i != titleList.end();i++)
	{
		QStandardItem*	lpItem	= new QStandardItem(*i);
		lpItem->setCheckable(true);
		m_lpTitleListModel->appendRow(lpItem);
		if(szIDs.contains(*i))
			lpItem->setCheckState(Qt::Checked);
	}

	m_lpPersonListModel->sort(0);

	m_bLoading	= false;
}

void cFilterPanel::updateTitleList(QStringList& titleList)
{
	m_bLoading		= true;

	for(QStringList::iterator i = titleList.begin();i != titleList.end();i++)
	{
		if(m_lpTitleListModel->findItems(*i).isEmpty())
		{
			QStandardItem*	lpItem	= new QStandardItem(*i);
			lpItem->setCheckable(true);
			m_lpTitleListModel->appendRow(lpItem);
		}
	}

	m_lpPersonListModel->sort(0);

	m_bLoading	= false;
}

QStringList cFilterPanel::selectedTitle()
{
	QStringList	titleList;

	for(int x = 0;x < m_lpTitleListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpTitleListModel->item(x, 0);

		if(lpItem->checkState() == Qt::Checked)
			titleList.append(lpItem->text());
	}
	return(titleList);
}

void cFilterPanel::clearPersonList()
{
	m_lpPersonListModel->clear();
}

void cFilterPanel::setPersonList(cPersonList* lpPersonList)
{
	m_bLoading		= true;

	QSettings		settings;
	QStringList		szIDs;

	szIDs			= settings.value("filter/person").toStringList();
	m_lpPersonList	= lpPersonList;

	m_lpPersonListModel->clear();

	for(cPersonList::iterator i = lpPersonList->begin();i != lpPersonList->end();i++)
	{
		QStandardItem*	lpItem	= new QStandardItem((*i)->name());
		lpItem->setData(QVariant::fromValue(*i), Qt::UserRole+1);
		lpItem->setCheckable(true);
		m_lpPersonListModel->appendRow(lpItem);
		if(szIDs.contains(QString::number((*i)->id())))
			lpItem->setCheckState(Qt::Checked);
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

QList<qint32> cFilterPanel::selectedPerson()
{
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
	return(idList);
}

void cFilterPanel::clearLocationList()
{
	m_lpLocationListModel->clear();
}

void cFilterPanel::setLocationList(cLocationList* lpLocationList)
{
	m_bLoading		= true;

	QSettings		settings;
	QStringList		szIDs;

	szIDs			= settings.value("filter/location").toStringList();
	m_lpLocationList	= lpLocationList;

	m_lpPersonListModel->clear();

	for(cLocationList::iterator i = lpLocationList->begin();i != lpLocationList->end();i++)
	{
		QStandardItem*	lpItem	= new QStandardItem((*i)->name());
		lpItem->setData(QVariant::fromValue(*i), Qt::UserRole+1);
		lpItem->setCheckable(true);
		m_lpLocationListModel->appendRow(lpItem);
		if(szIDs.contains(QString::number((*i)->id())))
			lpItem->setCheckState(Qt::Checked);
	}

	m_lpLocationListModel->sort(0);

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

QList<qint32> cFilterPanel::selectedLocation()
{
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
	return(idList);
}

void cFilterPanel::clearTagList()
{
	m_lpTagListModel->clear();
}

void cFilterPanel::setTagList(cTagList* lpTagList)
{
	m_bLoading		= true;

	QSettings		settings;
	QStringList		szIDs;

	szIDs			= settings.value("filter/tag").toStringList();
	m_lpTagList		= lpTagList;

	m_lpTagListModel->clear();

	for(cTagList::iterator i = lpTagList->begin();i != lpTagList->end();i++)
	{
		QStandardItem*	lpItem	= new QStandardItem((*i)->name());
		lpItem->setData(QVariant::fromValue(*i), Qt::UserRole+1);
		lpItem->setCheckable(true);
		m_lpTagListModel->appendRow(lpItem);
		if(szIDs.contains(QString::number((*i)->id())))
			lpItem->setCheckState(Qt::Checked);
	}

	m_lpTagListModel->sort(0);

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

QList<qint32> cFilterPanel::selectedTag()
{
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
	return(idList);
}

void cFilterPanel::onTitleFilter(bool bToggle)
{
	if(bToggle)
		onTitleChanged();
	else {
		emit(titleChanged(QStringList()));
	}
}

void cFilterPanel::onTitleChanged(const QModelIndex& /*topLeft*/, const QModelIndex& /*bottomright*/, const QVector<int>& /*roles*/)
{
	onTitleChanged();
}

void cFilterPanel::onTitleChanged()
{
	if(m_bLoading)
		return;

	QStringList	titleList;

	if(ui->m_lpTitleFilter->isChecked())
	{
		for(int x = 0;x < m_lpTitleListModel->rowCount();x++)
		{
			QStandardItem*	lpItem	= m_lpTitleListModel->item(x, 0);

			if(lpItem->checkState() == Qt::Checked)
				titleList.append(lpItem->text());
		}
	}

	emit titleChanged(titleList);
}

void cFilterPanel::onPersonChanged()
{
	if(m_bLoading)
		return;

	QList<qint32>	idList;

	if(ui->m_lpPersonFilter->isChecked())
	{
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

	if(ui->m_lpLocationFilter->isChecked())
	{
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

	if(ui->m_lpTagFilter->isChecked())
	{
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
