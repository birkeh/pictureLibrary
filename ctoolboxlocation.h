/*!
 \file ctoolboxlocation.h

*/

#ifndef CTOOLBOXLOCATION_H
#define CTOOLBOXLOCATION_H


#include "clocation.h"
#include "cpicture.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelection>


namespace Ui {
class cToolBoxLocation;
}

/*!
 \brief

 \class cToolBoxLocation ctoolboxlocation.h "ctoolboxlocation.h"
*/
class cToolBoxLocation : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cToolBoxLocation
	 \param parent
	*/
	explicit cToolBoxLocation(QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cToolBoxLocation
	*/
	~cToolBoxLocation();

	/*!
	 \brief

	 \fn clearLocationList
	*/
	void					clearLocationList();
	/*!
	 \brief

	 \param lpLocationList
	 \fn setLocationList
	*/
	void					setLocationList(cLocationList* lpLocationList);

	/*!
	 \brief

	 \fn setPicture
	 \param pictureList
	*/
	void					setPicture(cPictureList& pictureList);

private:
	Ui::cToolBoxLocation*	ui;							/*!< TODO: describe */
	QStandardItemModel*		m_lpLocationListModel;		/*!< TODO: describe */
	cLocationList*			m_lpLocationList;			/*!< TODO: describe */
	cPictureList			m_pictureList;				/*!< TODO: describe */
	bool					m_bLoading;					/*!< TODO: describe */

	QAction*				m_lpLocationAddAction;		/*!< TODO: describe */
	QAction*				m_lpLocationEditAction;		/*!< TODO: describe */
	QAction*				m_lpLocationDeleteAction;	/*!< TODO: describe */

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

	 \fn onLocationSelected
	 \param selection
	 \param previous
	*/
	void					onLocationSelected(const QItemSelection& selection, const QItemSelection& previous);
	/*!
	 \brief

	 \fn locationChanged
	 \param topLeft
	 \param bottomright
	 \param roles
	*/
	void					locationChanged(const QModelIndex& topLeft, const QModelIndex& bottomright, const QVector<int>& roles);
	/*!
	 \brief

	 \fn onLocationAdd
	*/
	void					onLocationAdd();
	/*!
	 \brief

	 \fn onLocationEdit
	*/
	void					onLocationEdit();
	/*!
	 \brief

	 \fn onLocationDelete
	*/
	void					onLocationDelete();

	/*!
	 \brief

	 \fn onLocationViewContextMenu
	 \param pos
	*/
	void					onLocationViewContextMenu(const QPoint& pos);

	/*!
	 \brief

	 \fn onLocationChanged
	 \param lpItem
	*/
	void					onLocationChanged(QStandardItem* lpItem);
};

#endif // CTOOLBOXLOCATION_H
