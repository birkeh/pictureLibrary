/*!
 \file cToolBoxPerson.cpp

*/

#include "ctoolboxperson.h"
#include "ui_ctoolboxperson.h"

#include <QAction>
#include <QMenu>

#include <QInputDialog>

#include <QMessageBox>


cToolBoxPerson::cToolBoxPerson(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cToolBoxPerson),
	m_bLoading(true),
	m_bEditing(false)
{
	initUI();
	createActions();
}

cToolBoxPerson::~cToolBoxPerson()
{
	delete ui;
}

void cToolBoxPerson::initUI()
{
	ui->setupUi(this);

	m_lpPersonListModel	= new QStandardItemModel;
	ui->m_lpPersonList->setModel(m_lpPersonListModel);

	ui->m_lpEdit->setEnabled(false);
	ui->m_lpDelete->setEnabled(false);
}

void cToolBoxPerson::createActions()
{
	m_lpPersonAddAction		= new QAction(tr("add person"), this);
	m_lpPersonAddAction->setStatusTip(tr("add a new person"));
	connect(m_lpPersonAddAction,					&QAction::triggered,							this,	&cToolBoxPerson::onPersonAdd);
	connect(ui->m_lpAdd,							&QPushButton::clicked,							this,	&cToolBoxPerson::onPersonAdd);

	m_lpPersonEditAction	= new QAction(tr("edit person"), this);
	m_lpPersonEditAction->setStatusTip(tr("edit this person"));
	connect(m_lpPersonEditAction,					&QAction::triggered,							this,	&cToolBoxPerson::onPersonEdit);
	connect(ui->m_lpEdit,							&QPushButton::clicked,							this,	&cToolBoxPerson::onPersonEdit);

	m_lpPersonDeleteAction	= new QAction(tr("delete person"), this);
	m_lpPersonDeleteAction->setStatusTip(tr("delete this person"));
	connect(m_lpPersonDeleteAction,					&QAction::triggered,							this,	&cToolBoxPerson::onPersonDelete);
	connect(ui->m_lpDelete,							&QPushButton::clicked,							this,	&cToolBoxPerson::onPersonDelete);

	connect(ui->m_lpPersonList->selectionModel(),	&QItemSelectionModel::selectionChanged,			this,	&cToolBoxPerson::onPersonSelected);

	connect(m_lpPersonListModel,	SIGNAL(dataChanged(QModelIndex,	QModelIndex, QVector<int>)),	SLOT(personChanged(QModelIndex, QModelIndex, QVector<int>)));
	connect(ui->m_lpPersonList,						&QTreeView::customContextMenuRequested,			this,	&cToolBoxPerson::onPersonViewContextMenu);
	connect(m_lpPersonListModel,					&QStandardItemModel::itemChanged,				this,	&cToolBoxPerson::onPersonChanged);
}

void cToolBoxPerson::setPersonList(cPersonList* lpPersonList)
{
	m_bLoading	= true;

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

void cToolBoxPerson::setPicture(cPictureList& pictureList)
{
	m_bLoading	= true;

	m_pictureList.clear();

	for(int i = 0;i < m_lpPersonListModel->rowCount();i++)
	{
		QStandardItem*	lpItem		= m_lpPersonListModel->item(i, 0);
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
		cPersonList&	personList	= (*i)->personList();

		for(cPersonList::iterator j = personList.begin();j != personList.end();j++)
		{
			if(list.contains((*j)->id()))
				list[(*j)->id()] ++;
			else
				list.insert((*j)->id(), 1);
		}
	}

	for(int i = 0;i < m_lpPersonListModel->rowCount();i++)
	{
		QStandardItem*	lpItem		= m_lpPersonListModel->item(i, 0);
		cPerson*		lpPerson	= lpItem->data().value<cPerson*>();

		if(list.contains(lpPerson->id()))
		{
			if(list[lpPerson->id()] == count)
				lpItem->setCheckState(Qt::Checked);
			else
				lpItem->setCheckState(Qt::PartiallyChecked);
		}
	}
	m_bLoading	= false;
}

void cToolBoxPerson::onPersonSelected(const QItemSelection& /*selection*/, const QItemSelection& /*previous*/)
{
	if(ui->m_lpPersonList->selectionModel()->selectedIndexes().count() == 1)
	{
		ui->m_lpEdit->setEnabled(true);
		ui->m_lpDelete->setEnabled(true);
	}
	else if(ui->m_lpPersonList->selectionModel()->selectedIndexes().count() > 1)
	{
		ui->m_lpEdit->setEnabled(false);
		ui->m_lpDelete->setEnabled(true);
	}
}

void cToolBoxPerson::personChanged(const QModelIndex& /*topLeft*/, const QModelIndex& /*bottomright*/, const QVector<int>& /*roles*/)
{
	if(!m_pictureList.count())
		return;

	if(m_bLoading)
		return;

	for(int x = 0;x < m_lpPersonListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpPersonListModel->item(x, 0);

		if(lpItem->checkState() != Qt::PartiallyChecked)
		{
			cPerson*	lpPerson		= lpItem->data(Qt::UserRole+1).value<cPerson*>();
			if(lpPerson)
			{
				for(cPictureList::iterator i = m_pictureList.begin();i != m_pictureList.end();i++)
				{
					if(lpItem->checkState() == Qt::Checked)
						(*i)->addPerson(lpPerson);
					else if(lpItem->checkState() == Qt::Unchecked)
						(*i)->removePerson(lpPerson);
				}
			}
		}
	}

	for(cPictureList::iterator i = m_pictureList.begin();i != m_pictureList.end();i++)
		(*i)->toDB();
}

void cToolBoxPerson::onPersonAdd()
{
	QInputDialog	input(this);

	input.setLabelText(tr("name:"));
	input.setWindowTitle(tr("New Person"));
	if(input.exec() == QDialog::Rejected)
		return;

	if(input.textValue().isEmpty())
		return;

	cPerson*	lpPerson	= new cPerson;
	lpPerson->setName(input.textValue());
	if(!lpPerson->toDB())
	{
		delete lpPerson;
		return;
	}

	m_lpPersonList->add(lpPerson);

	m_bLoading	= true;

	QStandardItem*	lpItem	= new QStandardItem(lpPerson->name());
	lpItem->setData(QVariant::fromValue(lpPerson), Qt::UserRole+1);
	lpItem->setCheckable(true);
	m_lpPersonListModel->appendRow(lpItem);
	m_lpPersonListModel->sort(0);

	m_bLoading	= false;
}

void cToolBoxPerson::onPersonEdit()
{
	if(ui->m_lpPersonList->selectionModel()->selectedIndexes().count() != 1)
		return;

	QStandardItem*	lpItem		= m_lpPersonListModel->itemFromIndex(ui->m_lpPersonList->selectionModel()->selectedIndexes()[0]);
	if(!lpItem)
		return;

	cPerson*		lpPerson	= lpItem->data(Qt::UserRole+1).value<cPerson*>();
	if(!lpPerson)
		return;

	QInputDialog	input(this);

	input.setLabelText(tr("name:"));
	input.setWindowTitle(tr("Edit Person"));
	input.setTextValue(lpPerson->name());

	if(input.exec() == QDialog::Rejected)
		return;

	if(input.textValue().isEmpty())
		return;

	lpItem->setText(input.textValue());
}

void cToolBoxPerson::onPersonDelete()
{
	for(int x = ui->m_lpPersonList->selectionModel()->selectedIndexes().count()-1;x >= 0; x--)
	{
		QModelIndex			index		= ui->m_lpPersonList->selectionModel()->selectedIndexes()[x];
		QStandardItem*		lpItem		= m_lpPersonListModel->itemFromIndex(index);
		if(lpItem)
		{
			cPerson*		lpPerson	= lpItem->data(Qt::UserRole+1).value<cPerson*>();
			if(lpPerson)
			{
				if(QMessageBox::question(this, tr("Delete Person"), QString(tr("Are you sure you want to delete %1?")).arg(lpPerson->name())) == QMessageBox::Yes)
				{
					if(!m_lpPersonList->remove(lpPerson))
						QMessageBox::critical(this, tr("Delete Person"), QString(tr("%1 is in use and can't be deleted!")).arg(lpPerson->name()));
					else
						m_lpPersonListModel->removeRow(index.row());
				}
			}
		}
	}

}

void cToolBoxPerson::onPersonViewContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	menu.addAction(m_lpPersonAddAction);

	if(ui->m_lpPersonList->selectionModel()->selectedIndexes().count() == 1)
		menu.addAction(m_lpPersonEditAction);
	if(ui->m_lpPersonList->selectionModel()->selectedIndexes().count() >= 1)
		menu.addAction(m_lpPersonDeleteAction);

	menu.exec(ui->m_lpPersonList->mapToGlobal(pos));
}

void cToolBoxPerson::onPersonChanged(QStandardItem* lpItem)
{
	if(m_bEditing)
		return;

	cPerson*	lpPerson	= lpItem->data(Qt::UserRole+1).value<cPerson*>();
	if(!lpPerson)
		return;

	if(lpItem->text() == lpPerson->name())
		return;

	QString		szOldName	= lpPerson->name();
	lpPerson->setName(lpItem->text());
	if(!lpPerson->toDB())
	{
		QMessageBox::critical(this, tr("ERROR"), QString(tr("%1 already exists.").arg(lpItem->text())));
		m_bEditing	= true;
		lpItem->setText(szOldName);
		lpPerson->setName(szOldName);
		m_bEditing	= false;
	}
}
