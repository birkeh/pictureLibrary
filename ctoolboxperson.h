/*!
 \file ctoolboxperson.h

*/

#ifndef CTOOLBOXPERSON_H
#define CTOOLBOXPERSON_H


#include "cperson.h"
#include "cpicture.h"

#include <QWidget>
#include <QStandardItemModel>


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

private slots:
	/*!
	 \brief

	 \fn personChanged
	 \param topLeft
	 \param bottomright
	 \param roles
	*/
	void					personChanged(const QModelIndex& topLeft, const QModelIndex& bottomright, const QVector<int>& roles);
};

#endif // CTOOLBOXPERSON_H
