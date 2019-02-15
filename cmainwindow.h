#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cpicturelibrary.h"
#include "csplashscreen.h"
#include "cpicture.h"

#include "cthumbnailfilterproxymodel.h"

#include "ctoolboxinfo.h"

#include <QMainWindow>
#include <QCloseEvent>

#include <QStandardItemModel>
#include <QItemSelection>

#include <QMenu>
#include <QToolBar>

#include <QProgressBar>


namespace Ui {
class cMainWindow;
}

Q_DECLARE_METATYPE(QList<QStandardItem*>*)

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
	QProgressBar*			m_lpProgressBar;						/**< TODO: describe */
	QStandardItemModel*		m_lpFolderViewModel;					/**< TODO: describe */
	QStandardItemModel*		m_lpThumbnailViewModel;					/**< TODO: describe */
	cThumbnailFilterProxyModel*	m_lpThumbnailFilterProxyModel;		/**< TODO: describe */
	QStandardItem*			m_lpRootItem;							/**< TODO: describe */

	bool					m_bLoading;								/**< TODO: describe */

	cSplashScreen*			m_lpSplashScreen;						/*!< Splash Screen */
	cPictureLibrary			m_pictureLibrary;						/**< TODO: describe */
	cPictureList			m_pictureList;							/**< TODO: describe */

	QMenu*					m_lpFileMenu;							/*!< Pointer to the file menu */

	QToolBar*				m_lpFileToolBar;						/*!< Pointer to the file toolbar */

	QAction*				m_lpFileNewAction;						/*!< TODO: describe */
	QAction*				m_lpFileOpenAction;						/*!< TODO: describe */
	QAction*				m_lpFileImportAction;					/*!< TODO: describe */
	QAction*				m_lpFileQuitAction;						/*!< TODO: describe */

	QAction*				m_lpSeparatorRecent;					/*!< TODO: describe */
	enum { MaxRecentFiles = 5 };									/*!< TODO: describe */
	QAction*				m_lpRecentFileAction[MaxRecentFiles];	/*!< TODO: describe */

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

	 \fn createFileActions
	*/
	void					createFileActions();

	/*!
	 \brief

	 \fn setCurrentFile
	 \param szFileName
	*/
	void					setCurrentFile(const QString& szFileName);
	/*!
	 \brief

	 \fn updateRecentFileActions
	*/
	void					updateRecentFileActions();
	/*!
	 \brief

	 \fn openRecentFile
	*/
	void					openRecentFile();

	/*!
	 \brief

	 \fn loadData
	*/
	void					loadData(bool bProgressBar = false);

	/*!
	 \brief

	 \param szPath
	 \param lpItem
	 \fn insertPath
	*/
	void					insertPath(QString szPath);

protected:
	/*!
	 \brief

	 \fn closeEvent
	 \param event
	*/
	void					closeEvent(QCloseEvent* event);

private slots:
	/*!
	 \brief
	 \param selection
	 \param previous
	 \fn onThumbnailSelected
	*/
	void					onThumbnailSelected(const QItemSelection& selection, const QItemSelection& previous);
	/*!
	 \brief
	 \param selection
	 \param previous
	 \fn onThumbnailSelected
	*/
	void					onFolderSelected(const QItemSelection& selection, const QItemSelection& previous);
	/*!
	 \brief

	 \fn onFileNew
	*/
	void					onFileNew();
	/*!
	 \brief

	 \fn onFileOpen
	*/
	void					onFileOpen();
	/*!
	 \brief

	 \fn onFileImport
	*/
	void					onFileImport();
};

#endif // CMAINWINDOW_H
