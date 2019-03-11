/*!
 \file ctoolboxtag.h

*/

#ifndef CTOOLBOXTAG_H
#define CTOOLBOXTAG_H


#include "ctag.h"
#include "cpicture.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelection>


namespace Ui {
class cToolBoxTag;
}

/*!
 \brief

 \class cToolBoxTag ctoolboxtag.h "ctoolboxtag.h"
*/
class cToolBoxTag : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cToolBoxTag
	 \param parent
	*/
	explicit cToolBoxTag(QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cToolBoxTag
	*/
	~cToolBoxTag();

	/*!
	 \brief

	 \param lpTagList
	 \fn setTagList
	*/
	void					setTagList(cTagList* lpTagList);

	/*!
	 \brief

	 \fn setPicture
	 \param pictureList
	*/
	void					setPicture(cPictureList& pictureList);

private:
	Ui::cToolBoxTag*		ui;							/*!< TODO: describe */
	QStandardItemModel*		m_lpTagListModel;			/*!< TODO: describe */
	cTagList*				m_lpTagList;				/*!< TODO: describe */
	cPictureList			m_pictureList;				/*!< TODO: describe */
	bool					m_bLoading;					/*!< TODO: describe */

	QAction*				m_lpTagAddAction;			/*!< TODO: describe */
	QAction*				m_lpTagEditAction;			/*!< TODO: describe */
	QAction*				m_lpTagDeleteAction;		/*!< TODO: describe */

	bool					m_bEditing;					/*!< TODO: describe */

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

	 \fn onTagSelected
	 \param selection
	 \param previous
	*/
	void					onTagSelected(const QItemSelection& selection, const QItemSelection& previous);
	/*!
	 \brief

	 \fn tagChanged
	 \param topLeft
	 \param bottomright
	 \param roles
	*/
	void					tagChanged(const QModelIndex& topLeft, const QModelIndex& bottomright, const QVector<int>& roles);
	/*!
	 \brief

	 \fn onTagAdd
	*/
	void					onTagAdd();
	/*!
	 \brief

	 \fn onTagEdit
	*/
	void					onTagEdit();
	/*!
	 \brief

	 \fn onTagDelete
	*/
	void					onTagDelete();

	/*!
	 \brief

	 \fn onTagViewContextMenu
	 \param pos
	*/
	void					onTagViewContextMenu(const QPoint& pos);

	/*!
	 \brief

	 \fn onTagChanged
	 \param lpItem
	*/
	void					onTagChanged(QStandardItem* lpItem);
};

#endif // CTOOLBOXTAG_H
