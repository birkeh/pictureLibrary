#ifndef CFILTERPANEL_H
#define CFILTERPANEL_H


#include "ctag.h"
#include "cperson.h"
#include "clocation.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelection>


namespace Ui {
class cFilterPanel;
}

class cFilterPanel : public QWidget
{
	Q_OBJECT

public:
	explicit cFilterPanel(QWidget *parent = nullptr);
	~cFilterPanel();

	/*!
	 \brief

	 \fn clearPersonList
	*/
	void					clearPersonList();
	/*!
	 \brief

	 \param lpPersonList
	 \fn setPersonList
	*/
	void					setPersonList(cPersonList* lpPersonList);

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

	 \fn clearTagList
	*/
	void					clearTagList();
	/*!
	 \brief

	 \param lpTagList
	 \fn setTagList
	*/
	void					setTagList(cTagList* lpTagList);

private:
	Ui::cFilterPanel*		ui;
	bool					m_bLoading;					/*!< TODO: describe */

	QStandardItemModel*		m_lpPersonListModel;		/*!< TODO: describe */
	cPersonList*			m_lpPersonList;				/*!< TODO: describe */

	QStandardItemModel*		m_lpLocationListModel;		/*!< TODO: describe */
	cLocationList*			m_lpLocationList;			/*!< TODO: describe */

	QStandardItemModel*		m_lpTagListModel;			/*!< TODO: describe */
	cTagList*				m_lpTagList;				/*!< TODO: describe */

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
};

#endif // CFILTERPANEL_H
