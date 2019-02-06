#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cexif.h"

#include <QMainWindow>


namespace Ui {
class cMainWindow;
}

/**
 * @brief
 *
 */
class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	/**
	 * @brief
	 *
	 * @param parent
	 */
	explicit cMainWindow(QWidget *parent = nullptr);
	/**
	 * @brief
	 *
	 */
	~cMainWindow();

private:
	Ui::cMainWindow*	ui; /**< TODO: describe */
	cEXIFTagList		m_exifTagList; /**< TODO: describe */
};

#endif // CMAINWINDOW_H
