/*!
 \file cimportdialog.h

*/

#ifndef CIMPORTDIALOG_H
#define CIMPORTDIALOG_H


#include <QDialog>
#include <QStandardItemModel>
#include <QCloseEvent>
#include <QItemSelection>

#include "cpicture.h"
#include "cthumbnailsortfilterproxymodel.h"


namespace Ui {
class cImportDialog;
}

/*!
 \brief

 \class cImportDialog cimportdialog.h "cimportdialog.h"
*/
class cImportDialog : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cImportDialog
	 \param szRootPath
	 \param parent
	*/
	explicit cImportDialog(const QString& szRootPath, cPictureList& pictureList, QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cImportDialog
	*/
	~cImportDialog();

	/*!
	 \brief

	 \fn hasImported
	 \return bool
	*/
	bool							hasImported();

private slots:
	/*!
	 \brief

	 \fn onPathSelect
	*/
	void							onPathSelect();
	/*!
	 \brief

	 \fn onRead
	*/
	void							onRead();
	/*!
	 \brief

	 \fn onImport
	*/
	void							onImport();
	/*!
	 \brief

	 \fn onThumbnailSelected
	 \param selection
	 \param previous
	*/
	void							onThumbnailSelected(const QItemSelection& selection, const QItemSelection& previous);
	/*!
	 \brief

	 \fn onFolderSelected
	 \param selection
	 \param previous
	*/
	void							onFolderSelected(const QItemSelection& selection, const QItemSelection& previous);

private:
	Ui::cImportDialog*				ui;									/*!< TODO: describe */
	QString							m_szRootPath;						/*!< TODO: describe */
	cPictureList&					m_pictureList;						/*!< TODO: describe */
	QStandardItemModel*				m_lpFolderViewModel;				/*!< TODO: describe */
	QStandardItemModel*				m_lpThumbnailViewModel;				/*!< TODO: describe */
	cThumbnailSortFilterProxyModel*	m_lpThumbnailSortFilterProxyModel;	/*!< TODO: describe */
	bool							m_bLoading;							/*!< TODO: describe */
	bool							m_bHasImported;						/*!< TODO: describe */
	QStandardItem*					m_lpRootItem;						/*!< TODO: describe */

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

	 \fn readDirectory
	 \param szPath
	 \param bRecursive
	*/
	void							readDirectory(const QString& szPath, bool bRecursive);

	/*!
	 \brief

	 \fn accept
	*/
	void							accept();
	/*!
	 \brief

	 \fn reject
	*/
	void							reject();

	/*!
	 \brief

	 \fn savePosition
	*/
	void						savePosition();
protected:
};

#endif // CIMPORTDIALOG_H
