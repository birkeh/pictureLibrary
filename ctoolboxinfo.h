#ifndef CTOOLBOXINFO_H
#define CTOOLBOXINFO_H


#include "cpicture.h"

#include <QWidget>


namespace Ui {
class cToolBoxInfo;
}

/**
 * @brief
 *
 */
class cToolBoxInfo : public QWidget
{
	Q_OBJECT

public:
	/**
	 * @brief
	 *
	 * @param parent
	 */
	explicit cToolBoxInfo(QWidget *parent = nullptr);
	/**
	 * @brief
	 *
	 */
	~cToolBoxInfo();

	/**
	 * @brief
	 *
	 * @param lpPicture
	 */
	void				setPicture(cPicture* lpPicture);
private:
	Ui::cToolBoxInfo*	ui; /**< TODO: describe */
};

#endif // CTOOLBOXINFO_H
