#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cpicturelibrary.h"

#include "cexif.h"
#include "csplashscreen.h"

#include <QMainWindow>
#include <QCloseEvent>


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
	 * @param lpSplashScreen
	 * @param parent
	 */
	explicit cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent = nullptr);
	/**
	 * @brief
	 *
	 */
	~cMainWindow();

private:
	Ui::cMainWindow*	ui;										/**< TODO: describe */
	cSplashScreen*		m_lpSplashScreen;						/*!< Splash Screen */
	cEXIFTagList		m_exifTagList;							/**< TODO: describe */
	cPictureLibrary		m_pictureLibrary;						/**< TODO: describe */

	/*!
	 \brief

	 \fn initUI
	*/
	void				initUI();
	/*!
	 \brief

	 \fn createActions
	*/
	void				createActions();

protected:
	/*!
	 \brief

	 \fn closeEvent
	 \param event
	*/
	void				closeEvent(QCloseEvent* event);
};

#endif // CMAINWINDOW_H
