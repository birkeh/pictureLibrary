/*!
 \file ctoolboxperson.h

*/

#ifndef CTOOLBOXPERSON_H
#define CTOOLBOXPERSON_H


#include "cperson.h"
#include "cpicture.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelection>


namespace Ui {
class cToolBoxPerson;
}

/*!
 \brief

 \class cToolBoxPerson ctoolboxperson.h "ctoolboxperson.h"
*/
class cToolBoxPerson : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cToolBoxPerson
	 \param parent
	*/
	explicit cToolBoxPerson(QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cToolBoxPerson
	*/
	~cToolBoxPerson();

	/*!
	 \brief

	 \param lpPersonList
	 \fn setPersonList
	*/
	void					setPersonList(cPersonList* lpPersonList);

	/*!
	 \brief

	 \fn setPicture
	 \param pictureList
	*/
	void					setPicture(cPictureList& pictureList);
private:
	Ui::cToolBoxPerson*		ui;						/*!< TODO: describe */
	QStandardItemModel*		m_lpPersonListModel;	/*!< TODO: describe */
	cPersonList*			m_lpPersonList;			/*!< TODO: describe */
	cPictureList			m_pictureList;			/*!< TODO: describe */
	bool					m_bLoading;				/*!< TODO: describe */

	QAction*				m_lpPersonAddAction;	/*!< TODO: describe */
	QAction*				m_lpPersonEditAction;	/*!< TODO: describe */
	QAction*				m_lpPersonDeleteAction;	/*!< TODO: describe */

	bool					m_bEditing;				/*!< TODO: describe */

	/*!
	 \brief

	 \fn initUI
	*/
	void					initUI();
	/*!
	 \brief

	 \fn createActions
	*/
	void					createActions();

private slots:
	/*!
	 \brief

	 \fn onPersonSelected
	 \param selection
	 \param previous
	*/
	void					onPersonSelected(const QItemSelection& selection, const QItemSelection& previous);
	/*!
	 \brief

	 \fn personChanged
	 \param topLeft
	 \param bottomright
	 \param roles
	*/
	void					personChanged(const QModelIndex& topLeft, const QModelIndex& bottomright, const QVector<int>& roles);
	/*!
	 \brief

	 \fn onPersonAdd
	*/
	void					onPersonAdd();
	/*!
	 \brief

	 \fn onPersonEdit
	*/
	void					onPersonEdit();
	/*!
	 \brief

	 \fn onPersonDelete
	*/
	void					onPersonDelete();

	/*!
	 \brief

	 \fn onPersonViewContextMenu
	 \param pos
	*/
	void					onPersonViewContextMenu(const QPoint& pos);

	/*!
	 \brief

	 \fn onPersonChanged
	 \param lpItem
	*/
	void					onPersonChanged(QStandardItem* lpItem);
};

#endif // CTOOLBOXPERSON_H
