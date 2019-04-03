/*!
 \file cmainwindow.h

*/

#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H


#include "cpicturelibrary.h"
#include "csplashscreen.h"
#include "cpicture.h"
#include "ctag.h"
#include "clocation.h"
#include "cperson.h"

#include "cfoldersortfilterproxymodel.h"
#include "cthumbnailsortfilterproxymodel.h"

#include "ctoolboxinfo.h"

#include "cfilterpanel.h"

#include "cimageviewer.h"

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

/*!
 \brief

 \class cMainWindow cmainwindow.h "cmainwindow.h"
*/
class cMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cMainWindow
	 \param lpSplashScreen
	 \param parent
	*/
	explicit cMainWindow(cSplashScreen* lpSplashScreen, QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cMainWindow
	*/
	~cMainWindow();

private:
	Ui::cMainWindow*				ui;										/*!< TODO: describe */
	cFilterPanel*					m_lpFilterPanel;						/*!< TODO: describe */
	QProgressBar*					m_lpProgressBar;						/*!< TODO: describe */
	QStandardItemModel*				m_lpFolderViewModel;					/*!< TODO: describe */
	cFolderSortFilterProxyModel*	m_lpFolderSortFilterProxyModel;			/*!< TODO: describe */
	QStandardItemModel*				m_lpThumbnailViewModel;					/*!< TODO: describe */
	cThumbnailSortFilterProxyModel*	m_lpThumbnailSortFilterProxyModel;		/*!< TODO: describe */
	QStandardItem*					m_lpRootItem;							/*!< TODO: describe */

	bool							m_bLoading;								/*!< TODO: describe */

	cSplashScreen*					m_lpSplashScreen;						/*!< TODO: describe */
	cPictureLibrary					m_pictureLibrary;						/*!< TODO: describe */
	cPictureList					m_pictureList;							/*!< TODO: describe */
	cPersonList						m_personList;							/*!< TODO: describe */
	cLocationList					m_locationList;							/*!< TODO: describe */
	cTagList						m_tagList;								/*!< TODO: describe */

	QString							m_szOldPath;							/*!< TODO: describe */

	QMenu*							m_lpFileMenu;							/*!< TODO: describe */

	QToolBar*						m_lpFileToolBar;						/*!< TODO: describe */

	QAction*						m_lpFileNewAction;						/*!< TODO: describe */
	QAction*						m_lpFileOpenAction;						/*!< TODO: describe */
	QAction*						m_lpFileSaveAsAction;					/*!< TODO: describe */
	QAction*						m_lpFileImportAction;					/*!< TODO: describe */
	QAction*						m_lpFileExportAction;					/*!< TODO: describe */
	QAction*						m_lpFileQuitAction;						/*!< TODO: describe */

	QAction*						m_lpSeparatorRecent;					/*!< TODO: describe */
	enum							{ MaxRecentFiles = 5 };					/*!< TODO: describe */
	QAction*						m_lpRecentFileAction[MaxRecentFiles];	/*!< TODO: describe */

	QAction*						m_lpChangeTitleAction;					/*!< TODO: describe */
	QAction*						m_lpChangeDateAction;					/*!< TODO: describe */
	QAction*						m_lpChangeDateTimeAction;				/*!< TODO: describe */
	QAction*						m_lpSetHDRAction;						/*!< TODO: describe */
	QAction*						m_lpUnsetHDRAction;						/*!< TODO: describe */

	cImageViewer*					m_lpImageViewer;						/*!< TODO: describe */
	QModelIndex						m_imageViewerIndex;						/*!< TODO: describe */

	/*!
	 \brief

	 \fn initUI
	*/
	void							initUI();
	/*!
	 \brief

	 \fn createActions
	*/
	void							createActions();
	/*!
	 \brief

	 \fn createFileActions
	*/
	void							createFileActions();
	/*!
	 \brief

	 \fn createContextActions
	*/
	void							createContextActions();

	/*!
	 \brief

	 \fn setCurrentFile
	 \param szFileName
	*/
	void							setCurrentFile(const QString& szFileName);
	/*!
	 \brief

	 \fn updateRecentFileActions
	*/
	void							updateRecentFileActions();
	/*!
	 \brief

	 \fn openRecentFile
	*/
	void							openRecentFile();

	/*!
	 \brief

	 \fn loadData
	 \param bProgressBar
	*/
	void							loadData(bool bProgressBar = false);
	/*!
	 \brief

	 \fn displayData
	*/
	void							displayData();

	/*!
	 \brief

	 \fn cleanFolderTree
	 \param bProgressBar
	*/
	void							cleanFolderTree(const QString& folder);

	/*!
	 \brief

	 \fn showCount
	*/
	void							showCount();

	/*!
	 \brief

	 \fn viewImage
	*/
	void							viewImage();
protected:
	/*!
	 \brief

	 \fn closeEvent
	 \param event
	*/
	void							closeEvent(QCloseEvent* event);

private slots:
	/*!
	 \brief

	 \fn onThumbnailSelected
	 \param selection
	 \param previous
	*/
	void							onThumbnailSelected(const QItemSelection& selection, const QItemSelection& previous);
	/*!
	 \brief

	 \fn onThumbnailDoubleClicked
	 \param index
	*/
	void							onThumbnailDoubleClicked(const QModelIndex& index);

	/*!
	 \brief

	 \fn onFolderSelected
	 \param selection
	 \param previous
	*/
	void							onFolderSelected(const QItemSelection& selection, const QItemSelection& previous);
	/*!
	 \brief

	 \fn onFileNew
	*/
	void							onFileNew();
	/*!
	 \brief

	 \fn onFileOpen
	*/
	void							onFileOpen();
	/*!
	 \brief

	 \fn onFileSaveAs
	 \return bool
	*/
	bool							onFileSaveAs();
	/*!
	 \brief

	 \fn onFileImport
	*/
	void							onFileImport();
	/*!
	 \brief

	 \fn onFileExport
	*/
	void							onFileExport();

	/*!
	 \brief

	 \fn onThumbnailViewContextMenu
	 \param pos
	*/
	void							onThumbnailViewContextMenu(const QPoint& pos);

	/*!
	 \brief

	 \fn onChangeTitle
	*/
	void							onChangeTitle();
	/*!
	 \brief

	 \fn onChangeDate
	*/
	void							onChangeDate();
	/*!
	 \brief

	 \fn onChangeDateTime
	*/
	void							onChangeDateTime();
	/*!
	 \brief

	 \fn onSetHDR
	*/
	void							onSetHDR();
	/*!
	 \brief

	 \fn onUnsetHDR
	*/
	void							onUnsetHDR();
	/*!
	 \brief

	 \fn onTagAdded
	 \param lpTag
	*/
	void							onTagAdded(cTag* lpTag);
	/*!
	 \brief

	 \fn onTagRemoved
	 \param lpTag
	*/
	void							onTagRemoved(cTag* lpTag);
	/*!
	 \brief

	 \fn onTagEdited
	 \param lpTag
	*/
	void							onTagEdited(cTag* lpTag);
	/*!
	 \brief

	 \fn onTagListChanged
	*/
	void							onTagListChanged();
	/*!
	 \brief

	 \fn onPersonAdded
	 \param lpPerson
	*/
	void							onPersonAdded(cPerson* lpPerson);
	/*!
	 \brief

	 \fn onPersonRemoved
	 \param lpPerson
	*/
	void							onPersonRemoved(cPerson* lpPerson);
	/*!
	 \brief

	 \fn onPersonEdited
	 \param lpPerson
	*/
	void							onPersonEdited(cPerson* lpPerson);
	/*!
	 \brief

	 \fn onPersonListChanged
	*/
	void							onPersonListChanged();
	/*!
	 \brief

	 \fn onLocationAdded
	 \param lpLocation
	*/
	void							onLocationAdded(cLocation* lpLocation);
	/*!
	 \brief

	 \fn onLocationRemoved
	 \param lpLocation
	*/
	void							onLocationRemoved(cLocation* lpLocation);
	/*!
	 \brief

	 \fn onLocationEdited
	 \param lpLocation
	*/
	void							onLocationEdited(cLocation* lpLocation);
	/*!
	 \brief

	 \fn onLocationListChanged
	*/
	void							onLocationListChanged();

	/*!
	 \brief

	 \fn onFilterTitleChanged
	 \param titleList
	*/
	void							onFilterTitleChanged(QStringList titleList);
	/*!
	 \brief

	 \fn onFilterPersonChanged
	 \param idList
	*/
	void							onFilterPersonChanged(QList<qint32> idList, bool bAnd);
	/*!
	 \brief

	 \fn onFilterLocationChanged
	 \param idList
	*/
	void							onFilterLocationChanged(QList<qint32> idList, bool bAnd);
	/*!
	 \brief

	 \fn onFilterTagChanged
	 \param idList
	*/
	void							onFilterTagChanged(QList<qint32> idList, bool bAnd);

	/*!
	 \brief

	 \fn onImageNext
	*/
	void							onImageNext();
	/*!
	 \brief

	 \fn onImagePrev
	*/
	void							onImagePrev();
	/*!
	 \brief

	 \fn onImageLast
	*/
	void							onImageLast();
	/*!
	 \brief

	 \fn onImageFirst
	*/
	void							onImageFirst();
};

#endif // CMAINWINDOW_H
