#ifndef CIMPORTDIALOG_H
#define CIMPORTDIALOG_H


#include <QDialog>
#include <QStandardItemModel>
#include <QCloseEvent>
#include <QItemSelection>


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
	explicit cImportDialog(QWidget *parent = nullptr);
	/**
	 * @brief
	 *
	 */
	~cImportDialog();

private slots:
	/*!
	 \brief

	 \fn onPathSelect
	*/
	void					onPathSelect();
	/*!
	 \brief

	 \fn onRead
	*/
	void					onRead();
	/*!
	 \brief

	 \fn onImport
	*/
	void					onImport();
	/*!
	 \brief
	 \param selection
	 \param previous
	 \fn onThumbnailSelected
	*/
	void					onThumbnailSelected(const QItemSelection& selection, const QItemSelection& previous);

private:
	Ui::cImportDialog*		ui;										/**< TODO: describe */
	QStandardItemModel*		m_lpImportListModel;					/**< TODO: describe */

	void					initUI();
	void					createActions();

	/**
	 * @brief
	 *
	 * @param szPath
	 * @param bRecursive
	 */
	void					readDirectory(const QString& szPath, bool bRecursive);

	/**
	 * @brief
	 *
	 */
	void					accept();
	/**
	 * @brief
	 *
	 */
	void					reject();

	/**
	 * @brief
	 *
	 */
	void					savePosition();
protected:
	/*!
	 \brief

	 \fn closeEvent
	 \param event
	*/
	void					closeEvent(QCloseEvent* event);
};

#endif // CIMPORTDIALOG_H
