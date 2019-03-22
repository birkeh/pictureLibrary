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

	 \fn saveSettings
	*/
	void					saveSettings();

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

	 \fn updatePersonList
	*/
	void					updatePersonList();
	/*!
	 \brief

	 \fn selectedPerson
	 \return QList<qint32>
	*/
	QList<qint32>			selectedPerson();

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

	 \fn updateLocationList
	*/
	void					updateLocationList();
	/*!
	 \brief

	 \fn selectedLocation
	 \return QList<qint32>
	*/
	QList<qint32>			selectedLocation();

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
	/*!
	 \brief

	 \fn updateTagList
	*/
	void					updateTagList();
	/*!
	 \brief

	 \fn selectedTag
	 \return QList<qint32>
	*/
	QList<qint32>			selectedTag();

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

	/*!
	 \brief

	 \fn onPersonChanged
	*/
	void					onPersonChanged();
	/*!
	 \brief

	 \fn onLocationChanged
	*/
	void					onLocationChanged();
	/*!
	 \brief

	 \fn onTagChanged
	*/
	void					onTagChanged();
private slots:
	/*!
	 \brief

	 \fn onPersonFilter
	 \param bToggle
	*/
	void					onPersonFilter(bool bToggle);
	/*!
	 \brief

	 \fn onPersonAnd
	 \param bToggle
	*/
	void					onPersonAnd(bool bToggle);
	/*!
	 \brief

	 \fn onPersonChanged
	 \param topLeft
	 \param bottomright
	 \param roles
	*/
	void					onPersonChanged(const QModelIndex& topLeft, const QModelIndex& bottomright, const QVector<int>& roles);
	/*!
	 \brief

	 \fn onLocationFilter
	 \param bToggle
	*/
	void					onLocationFilter(bool bToggle);
	/*!
	 \brief

	 \fn onLocationAnd
	 \param bToggle
	*/
	void					onLocationAnd(bool bToggle);
	/*!
	 \brief

	 \fn onLocationChanged
	 \param topLeft
	 \param bottomright
	 \param roles
	*/
	void					onLocationChanged(const QModelIndex& topLeft, const QModelIndex& bottomright, const QVector<int>& roles);
	/*!
	 \brief

	 \fn onTagFilter
	 \param bToggle
	*/
	void					onTagFilter(bool bToggle);
	/*!
	 \brief

	 \fn onTagAnd
	 \param bToggle
	*/
	void					onTagAnd(bool bToggle);
	/*!
	 \brief

	 \fn onTagChanged
	 \param topLeft
	 \param bottomright
	 \param roles
	*/
	void					onTagChanged(const QModelIndex& topLeft, const QModelIndex& bottomright, const QVector<int>& roles);
signals:
	/*!
	 \brief

	 \fn personChanged
	 \param idList
	*/
	void					personChanged(QList<qint32> idList, bool bAnd);
	/*!
	 \brief

	 \fn locationChanged
	 \param idList
	*/
	void					locationChanged(QList<qint32> idList, bool bAnd);
	/*!
	 \brief

	 \fn tagChanged
	 \param idList
	*/
	void					tagChanged(QList<qint32> idList, bool bAnd);
};

#endif // CFILTERPANEL_H
