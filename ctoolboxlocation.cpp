#include "ctoolboxlocation.h"
#include "ui_ctoolboxlocation.h"

#include <QAction>
#include <QMenu>

#include <QInputDialog>

#include <QMessageBox>


cToolBoxLocation::cToolBoxLocation(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cToolBoxLocation),
	m_bLoading(true),
	m_bEditing(false)
{
	initUI();
	createActions();
}

cToolBoxLocation::~cToolBoxLocation()
{
	delete ui;
}

void cToolBoxLocation::initUI()
{
	ui->setupUi(this);

	m_lpLocationListModel	= new QStandardItemModel;
	ui->m_lpLocationList->setModel(m_lpLocationListModel);

	ui->m_lpEdit->setEnabled(false);
	ui->m_lpDelete->setEnabled(false);
}

void cToolBoxLocation::createActions()
{
	m_lpLocationAddAction		= new QAction(tr("add location"), this);
	m_lpLocationAddAction->setStatusTip(tr("add a new location"));
	connect(m_lpLocationAddAction,					&QAction::triggered,							this,	&cToolBoxLocation::onLocationAdd);
	connect(ui->m_lpAdd,							&QPushButton::clicked,							this,	&cToolBoxLocation::onLocationAdd);

	m_lpLocationEditAction	= new QAction(tr("edit location"), this);
	m_lpLocationEditAction->setStatusTip(tr("edit this location"));
	connect(m_lpLocationEditAction,					&QAction::triggered,							this,	&cToolBoxLocation::onLocationEdit);
	connect(ui->m_lpEdit,							&QPushButton::clicked,							this,	&cToolBoxLocation::onLocationEdit);

	m_lpLocationDeleteAction	= new QAction(tr("delete location"), this);
	m_lpLocationDeleteAction->setStatusTip(tr("delete this location"));
	connect(m_lpLocationDeleteAction,				&QAction::triggered,							this,	&cToolBoxLocation::onLocationDelete);
	connect(ui->m_lpDelete,							&QPushButton::clicked,							this,	&cToolBoxLocation::onLocationDelete);

	connect(ui->m_lpLocationList->selectionModel(),	&QItemSelectionModel::selectionChanged,			this,	&cToolBoxLocation::onLocationSelected);

	connect(m_lpLocationListModel,	SIGNAL(dataChanged(QModelIndex,	QModelIndex, QVector<int>)),	SLOT(locationChanged(QModelIndex, QModelIndex, QVector<int>)));
	connect(ui->m_lpLocationList,					&QTreeView::customContextMenuRequested,			this,	&cToolBoxLocation::onLocationViewContextMenu);
	connect(m_lpLocationListModel,					&QStandardItemModel::itemChanged,				this,	&cToolBoxLocation::onLocationChanged);
}

void cToolBoxLocation::setLocationList(cLocationList* lpLocationList)
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

void cToolBoxLocation::setPicture(cPictureList& pictureList)
{
	m_bLoading	= true;

	m_pictureList.clear();

	for(int i = 0;i < m_lpLocationListModel->rowCount();i++)
	{
		QStandardItem*	lpItem		= m_lpLocationListModel->item(i, 0);
		lpItem->setCheckState(Qt::Unchecked);
	}

	if(!pictureList.count())
	{
		m_bLoading	= false;
		return;
	}

	QHash<qint32, qint32>	list;
	qint32					count	= pictureList.count();

	for(cPictureList::iterator i = pictureList.begin();i != pictureList.end();i++)
	{
		m_pictureList.add(*i, true);
		cLocationList&	locationList	= (*i)->locationList();

		for(cLocationList::iterator j = locationList.begin();j != locationList.end();j++)
		{
			if(list.contains((*j)->id()))
				list[(*j)->id()] ++;
			else
				list.insert((*j)->id(), 1);
		}
	}

	for(int i = 0;i < m_lpLocationListModel->rowCount();i++)
	{
		QStandardItem*	lpItem		= m_lpLocationListModel->item(i, 0);
		cLocation*		lpLocation	= lpItem->data().value<cLocation*>();

		if(list.contains(lpLocation->id()))
		{
			if(list[lpLocation->id()] == count)
				lpItem->setCheckState(Qt::Checked);
			else
				lpItem->setCheckState(Qt::PartiallyChecked);
		}
	}
	m_bLoading	= false;
}

void cToolBoxLocation::onLocationSelected(const QItemSelection& /*selection*/, const QItemSelection& /*previous*/)
{
	if(ui->m_lpLocationList->selectionModel()->selectedIndexes().count() == 1)
	{
		ui->m_lpEdit->setEnabled(true);
		ui->m_lpDelete->setEnabled(true);
	}
	else if(ui->m_lpLocationList->selectionModel()->selectedIndexes().count() > 1)
	{
		ui->m_lpEdit->setEnabled(false);
		ui->m_lpDelete->setEnabled(true);
	}
}

void cToolBoxLocation::locationChanged(const QModelIndex& /*topLeft*/, const QModelIndex& /*bottomright*/, const QVector<int>& /*roles*/)
{
	if(!m_pictureList.count())
		return;

	if(m_bLoading)
		return;

	for(int x = 0;x < m_lpLocationListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpLocationListModel->item(x, 0);

		if(lpItem->checkState() != Qt::PartiallyChecked)
		{
			cLocation*	lpLocation		= lpItem->data(Qt::UserRole+1).value<cLocation*>();
			if(lpLocation)
			{
				for(cPictureList::iterator i = m_pictureList.begin();i != m_pictureList.end();i++)
				{
					if(lpItem->checkState() == Qt::Checked)
						(*i)->addLocation(lpLocation);
					else if(lpItem->checkState() == Qt::Unchecked)
						(*i)->removeLocation(lpLocation);
				}
			}
		}
	}

	for(cPictureList::iterator i = m_pictureList.begin();i != m_pictureList.end();i++)
		(*i)->toDB();
}

void cToolBoxLocation::onLocationAdd()
{
	QInputDialog	input(this);

	input.setLabelText(tr("name:"));
	input.setWindowTitle(tr("New Location"));
	if(input.exec() == QDialog::Rejected)
		return;

	if(input.textValue().isEmpty())
		return;

	cLocation*	lpLocation	= new cLocation;
	lpLocation->setName(input.textValue());
	if(!lpLocation->toDB())
	{
		delete lpLocation;
		return;
	}

	m_lpLocationList->add(lpLocation);

	m_bLoading	= true;

	QStandardItem*	lpItem	= new QStandardItem(lpLocation->name());
	lpItem->setData(QVariant::fromValue(lpLocation), Qt::UserRole+1);
	lpItem->setCheckable(true);
	m_lpLocationListModel->appendRow(lpItem);
	m_lpLocationListModel->sort(0);

	m_bLoading	= false;
}

void cToolBoxLocation::onLocationEdit()
{
	if(ui->m_lpLocationList->selectionModel()->selectedIndexes().count() != 1)
		return;

	QStandardItem*	lpItem		= m_lpLocationListModel->itemFromIndex(ui->m_lpLocationList->selectionModel()->selectedIndexes()[0]);
	if(!lpItem)
		return;

	cLocation*		lpLocation	= lpItem->data(Qt::UserRole+1).value<cLocation*>();
	if(!lpLocation)
		return;

	QInputDialog	input(this);

	input.setLabelText(tr("name:"));
	input.setWindowTitle(tr("Edit Location"));
	input.setTextValue(lpLocation->name());

	if(input.exec() == QDialog::Rejected)
		return;

	if(input.textValue().isEmpty())
		return;

	lpItem->setText(input.textValue());
}

void cToolBoxLocation::onLocationDelete()
{
	for(int x = ui->m_lpLocationList->selectionModel()->selectedIndexes().count()-1;x >= 0; x--)
	{
		QModelIndex			index		= ui->m_lpLocationList->selectionModel()->selectedIndexes()[x];
		QStandardItem*		lpItem		= m_lpLocationListModel->itemFromIndex(index);
		if(lpItem)
		{
			cLocation*		lpLocation	= lpItem->data(Qt::UserRole+1).value<cLocation*>();
			if(lpLocation)
			{
				if(QMessageBox::question(this, tr("Delete Location"), QString(tr("Are you sure you want to delete %1?")).arg(lpLocation->name())) == QMessageBox::Yes)
				{
					if(!m_lpLocationList->remove(lpLocation))
						QMessageBox::critical(this, tr("Delete Location"), QString(tr("%1 is in use and can't be deleted!")).arg(lpLocation->name()));
					else
						m_lpLocationListModel->removeRow(index.row());
				}
			}
		}
	}

}

void cToolBoxLocation::onLocationViewContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	menu.addAction(m_lpLocationAddAction);

	if(ui->m_lpLocationList->selectionModel()->selectedIndexes().count() == 1)
		menu.addAction(m_lpLocationEditAction);
	if(ui->m_lpLocationList->selectionModel()->selectedIndexes().count() >= 1)
		menu.addAction(m_lpLocationDeleteAction);

	menu.exec(ui->m_lpLocationList->mapToGlobal(pos));
}

void cToolBoxLocation::onLocationChanged(QStandardItem* lpItem)
{
	if(m_bEditing)
		return;

	cLocation*	lpLocation	= lpItem->data(Qt::UserRole+1).value<cLocation*>();
	if(!lpLocation)
		return;

	if(lpItem->text() == lpLocation->name())
		return;

	QString		szOldName	= lpLocation->name();
	lpLocation->setName(lpItem->text());
	if(!lpLocation->toDB())
	{
		QMessageBox::critical(this, tr("ERROR"), QString(tr("%1 already exists.").arg(lpItem->text())));
		m_bEditing	= true;
		lpItem->setText(szOldName);
		lpLocation->setName(szOldName);
		m_bEditing	= false;
	}
}
