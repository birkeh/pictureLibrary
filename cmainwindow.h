#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cpicturelibrary.h"
#include "csplashscreen.h"
#include "cpicture.h"

#include <QMainWindow>
#include <QCloseEvent>

#include <QStandardItemModel>


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
	Ui::cMainWindow*		ui;										/**< TODO: describe */
	QStandardItemModel*		m_lpThumbnailViewModel;					/**< TODO: describe */
	cSplashScreen*			m_lpSplashScreen;						/*!< Splash Screen */
	cPictureLibrary			m_pictureLibrary;						/**< TODO: describe */
	cPictureList			m_pictureList;							/**< TODO: describe */

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

	 \fn loadData
	*/
	void					loadData();

protected:
	/*!
	 \brief

	 \fn closeEvent
	 \param event
	*/
	void					closeEvent(QCloseEvent* event);
};

#endif // CMAINWINDOW_H
