/*!
 \file ctoolboxinfo.h

*/

#ifndef CTOOLBOXINFO_H
#define CTOOLBOXINFO_H


#include "cpicture.h"

#include <QWidget>


namespace Ui {
class cToolBoxInfo;
}

/*!
 \brief

 \class cToolBoxInfo ctoolboxinfo.h "ctoolboxinfo.h"
*/
class cToolBoxInfo : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cToolBoxInfo
	 \param parent
	*/
	explicit cToolBoxInfo(QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cToolBoxInfo
	*/
	~cToolBoxInfo();

	/*!
	 \brief

	 \fn setPicture
	 \param lpPicture
	*/
	void				setPicture(cPicture* lpPicture);
private:
	Ui::cToolBoxInfo*	ui;					/*!< TODO: describe */
};

#endif // CTOOLBOXINFO_H
