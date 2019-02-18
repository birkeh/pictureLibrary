#ifndef CIMPORTDIALOG_H
#define CIMPORTDIALOG_H


#include <QDialog>
#include <QStandardItemModel>
#include <QCloseEvent>
#include <QItemSelection>

#include "cthumbnailfilterproxymodel.h"


namespace Ui {
class cImportDialog;
}

/**
 * @brief
 *
 */
class cImportDialog : public QDialog
{
	Q_OBJECT

public:
	/**
	 * @brief
	 *
	 * @param parent
	 */
	explicit cImportDialog(const QString& szRootPath, QWidget *parent = nullptr);
	/**
	 * @brief
	 *
	 */
	~cImportDialog();

	/**
	 * @brief
	 *
	 * @return bool
	 */
	bool						hasImported();

private slots:
	/*!
	 \brief

	 \fn onPathSelect
	*/
	void						onPathSelect();
	/*!
	 \brief

	 \fn onRead
	*/
	void						onRead();
	/*!
	 \brief

	 \fn onImport
	*/
	void						onImport();
	/*!
	 \brief
	 \param selection
	 \param previous
	 \fn onThumbnailSelected
	*/
	void						onThumbnailSelected(const QItemSelection& selection, const QItemSelection& previous);
	/*!
	 \brief
	 \param selection
	 \param previous
	 \fn onThumbnailSelected
	*/
	void						onFolderSelected(const QItemSelection& selection, const QItemSelection& previous);

private:
	Ui::cImportDialog*			ui;										/**< TODO: describe */
	QString						m_szRootPath;							/**< TODO: describe */
	QStandardItemModel*			m_lpFolderViewModel;					/**< TODO: describe */
	QStandardItemModel*			m_lpThumbnailViewModel;					/**< TODO: describe */
	cThumbnailFilterProxyModel*	m_lpThumbnailFilterProxyModel;			/**< TODO: describe */
	bool						m_bLoading;								/**< TODO: describe */
	bool						m_bHasImported;							/**< TODO: describe */
	QStandardItem*				m_lpRootItem;							/**< TODO: describe */

	/*!
	 \brief

	 \fn initUI
	*/
	void						initUI();
	/*!
	 \brief

	 \fn createActions
	*/
	void						createActions();

	/**
	 * @brief
	 *
	 * @param szPath
	 * @param bRecursive
	 */
	void						readDirectory(const QString& szPath, bool bRecursive);

	/**
	 * @brief
	 *
	 */
	void						accept();
	/**
	 * @brief
	 *
	 */
	void						reject();

	/**
	 * @brief
	 *
	 */
	void					savePosition();
protected:
};

#endif // CIMPORTDIALOG_H
