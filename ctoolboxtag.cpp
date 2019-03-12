/*!
 \file cToolBoxTag.cpp

*/

#include "ctoolboxtag.h"
#include "ui_ctoolboxtag.h"

#include <QAction>
#include <QMenu>

#include <QInputDialog>

#include <QMessageBox>


cToolBoxTag::cToolBoxTag(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cToolBoxTag),
	m_bLoading(true),
	m_bEditing(false)
{
	initUI();
	createActions();
}

cToolBoxTag::~cToolBoxTag()
{
	delete ui;
}

void cToolBoxTag::initUI()
{
	ui->setupUi(this);

	m_lpTagListModel	= new QStandardItemModel;
	ui->m_lpTagList->setModel(m_lpTagListModel);

	ui->m_lpEdit->setEnabled(false);
	ui->m_lpDelete->setEnabled(false);
}

void cToolBoxTag::createActions()
{
	m_lpTagAddAction		= new QAction(tr("add tag"), this);
	m_lpTagAddAction->setStatusTip(tr("add a new tag"));
	connect(m_lpTagAddAction,						&QAction::triggered,							this,	&cToolBoxTag::onTagAdd);
	connect(ui->m_lpAdd,							&QPushButton::clicked,							this,	&cToolBoxTag::onTagAdd);

	m_lpTagEditAction	= new QAction(tr("edit tag"), this);
	m_lpTagEditAction->setStatusTip(tr("edit this tag"));
	connect(m_lpTagEditAction,						&QAction::triggered,							this,	&cToolBoxTag::onTagEdit);
	connect(ui->m_lpEdit,							&QPushButton::clicked,							this,	&cToolBoxTag::onTagEdit);

	m_lpTagDeleteAction	= new QAction(tr("delete tag"), this);
	m_lpTagDeleteAction->setStatusTip(tr("delete this tag"));
	connect(m_lpTagDeleteAction,					&QAction::triggered,							this,	&cToolBoxTag::onTagDelete);
	connect(ui->m_lpDelete,							&QPushButton::clicked,							this,	&cToolBoxTag::onTagDelete);

	connect(ui->m_lpTagList->selectionModel(),		&QItemSelectionModel::selectionChanged,			this,	&cToolBoxTag::onTagSelected);

	connect(m_lpTagListModel,	SIGNAL(dataChanged(QModelIndex,	QModelIndex, QVector<int>)),	SLOT(tagChanged(QModelIndex, QModelIndex, QVector<int>)));
	connect(ui->m_lpTagList,						&QTreeView::customContextMenuRequested,			this,	&cToolBoxTag::onTagViewContextMenu);
	connect(m_lpTagListModel,						&QStandardItemModel::itemChanged,				this,	&cToolBoxTag::onTagChanged);
}

void cToolBoxTag::clearTagList()
{
	m_lpTagListModel->clear();
}

void cToolBoxTag::setTagList(cTagList* lpTagList)
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

void cToolBoxTag::setPicture(cPictureList& pictureList)
{
	m_bLoading	= true;

	m_pictureList.clear();

	for(int i = 0;i < m_lpTagListModel->rowCount();i++)
	{
		QStandardItem*	lpItem		= m_lpTagListModel->item(i, 0);
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
		cTagList&	tagList	= (*i)->tagList();

		for(cTagList::iterator j = tagList.begin();j != tagList.end();j++)
		{
			if(list.contains((*j)->id()))
				list[(*j)->id()] ++;
			else
				list.insert((*j)->id(), 1);
		}
	}

	for(int i = 0;i < m_lpTagListModel->rowCount();i++)
	{
		QStandardItem*	lpItem		= m_lpTagListModel->item(i, 0);
		cTag*			lpTag		= lpItem->data().value<cTag*>();

		if(list.contains(lpTag->id()))
		{
			if(list[lpTag->id()] == count)
				lpItem->setCheckState(Qt::Checked);
			else
				lpItem->setCheckState(Qt::PartiallyChecked);
		}
	}
	m_bLoading	= false;
}

void cToolBoxTag::onTagSelected(const QItemSelection& /*selection*/, const QItemSelection& /*previous*/)
{
	if(ui->m_lpTagList->selectionModel()->selectedIndexes().count() == 1)
	{
		ui->m_lpEdit->setEnabled(true);
		ui->m_lpDelete->setEnabled(true);
	}
	else if(ui->m_lpTagList->selectionModel()->selectedIndexes().count() > 1)
	{
		ui->m_lpEdit->setEnabled(false);
		ui->m_lpDelete->setEnabled(true);
	}
}

void cToolBoxTag::tagChanged(const QModelIndex& /*topLeft*/, const QModelIndex& /*bottomright*/, const QVector<int>& /*roles*/)
{
	if(!m_pictureList.count())
		return;

	if(m_bLoading)
		return;

	for(int x = 0;x < m_lpTagListModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpTagListModel->item(x, 0);

		if(lpItem->checkState() != Qt::PartiallyChecked)
		{
			cTag*	lpTag		= lpItem->data(Qt::UserRole+1).value<cTag*>();
			if(lpTag)
			{
				for(cPictureList::iterator i = m_pictureList.begin();i != m_pictureList.end();i++)
				{
					if(lpItem->checkState() == Qt::Checked)
						(*i)->addTag(lpTag);
					else if(lpItem->checkState() == Qt::Unchecked)
						(*i)->removeTag(lpTag);
				}
			}
		}
	}

	for(cPictureList::iterator i = m_pictureList.begin();i != m_pictureList.end();i++)
		(*i)->toDB();
}

void cToolBoxTag::onTagAdd()
{
	QInputDialog	input(this);

	input.setLabelText(tr("name:"));
	input.setWindowTitle(tr("New Tag"));
	if(input.exec() == QDialog::Rejected)
		return;

	if(input.textValue().isEmpty())
		return;

	cTag*			lpTag	= new cTag;
	lpTag->setName(input.textValue());
	if(!lpTag->toDB())
	{
		delete lpTag;
		return;
	}

	m_lpTagList->add(lpTag);

	m_bLoading	= true;

	QStandardItem*	lpItem	= new QStandardItem(lpTag->name());
	lpItem->setData(QVariant::fromValue(lpTag), Qt::UserRole+1);
	lpItem->setCheckable(true);
	m_lpTagListModel->appendRow(lpItem);
	m_lpTagListModel->sort(0);

	m_bLoading	= false;
}

void cToolBoxTag::onTagEdit()
{
	if(ui->m_lpTagList->selectionModel()->selectedIndexes().count() != 1)
		return;

	QStandardItem*	lpItem		= m_lpTagListModel->itemFromIndex(ui->m_lpTagList->selectionModel()->selectedIndexes()[0]);
	if(!lpItem)
		return;

	cTag*			lpTag		= lpItem->data(Qt::UserRole+1).value<cTag*>();
	if(!lpTag)
		return;

	QInputDialog	input(this);

	input.setLabelText(tr("name:"));
	input.setWindowTitle(tr("Edit Tag"));
	input.setTextValue(lpTag->name());

	if(input.exec() == QDialog::Rejected)
		return;

	if(input.textValue().isEmpty())
		return;

	lpItem->setText(input.textValue());
}

void cToolBoxTag::onTagDelete()
{
	for(int x = ui->m_lpTagList->selectionModel()->selectedIndexes().count()-1;x >= 0; x--)
	{
		QModelIndex			index		= ui->m_lpTagList->selectionModel()->selectedIndexes()[x];
		QStandardItem*		lpItem		= m_lpTagListModel->itemFromIndex(index);
		if(lpItem)
		{
			cTag*			lpTag		= lpItem->data(Qt::UserRole+1).value<cTag*>();
			if(lpTag)
			{
				if(QMessageBox::question(this, tr("Delete Tag"), QString(tr("Are you sure you want to delete %1?")).arg(lpTag->name())) == QMessageBox::Yes)
				{
					if(!m_lpTagList->remove(lpTag))
						QMessageBox::critical(this, tr("Delete Tag"), QString(tr("%1 is in use and can't be deleted!")).arg(lpTag->name()));
					else
						m_lpTagListModel->removeRow(index.row());
				}
			}
		}
	}

}

void cToolBoxTag::onTagViewContextMenu(const QPoint& pos)
{
	QMenu			menu(this);

	menu.addAction(m_lpTagAddAction);

	if(ui->m_lpTagList->selectionModel()->selectedIndexes().count() == 1)
		menu.addAction(m_lpTagEditAction);
	if(ui->m_lpTagList->selectionModel()->selectedIndexes().count() >= 1)
		menu.addAction(m_lpTagDeleteAction);

	menu.exec(ui->m_lpTagList->mapToGlobal(pos));
}

void cToolBoxTag::onTagChanged(QStandardItem* lpItem)
{
	if(m_bEditing)
		return;

	cTag*	lpTag	= lpItem->data(Qt::UserRole+1).value<cTag*>();
	if(!lpTag)
		return;

	if(lpItem->text() == lpTag->name())
		return;

	QString		szOldName	= lpTag->name();
	lpTag->setName(lpItem->text());
	if(!lpTag->toDB())
	{
		QMessageBox::critical(this, tr("ERROR"), QString(tr("%1 already exists.").arg(lpItem->text())));
		m_bEditing	= true;
		lpItem->setText(szOldName);
		lpTag->setName(szOldName);
		m_bEditing	= false;
	}
}
