#include "ctoolboxperson.h"
#include "ui_ctoolboxperson.h"


cToolBoxPerson::cToolBoxPerson(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cToolBoxPerson),
	m_bLoading(true)
{
	ui->setupUi(this);

	m_lpPersonListModel	= new QStandardItemModel;
	ui->m_lpPersonList->setModel(m_lpPersonListModel);

	connect(m_lpPersonListModel, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), SLOT(personChanged(QModelIndex, QModelIndex, QVector<int>)));
}

cToolBoxPerson::~cToolBoxPerson()
{
	delete ui;
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
