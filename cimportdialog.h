#ifndef CIMPORTDIALOG_H
#define CIMPORTDIALOG_H


#include <QDialog>
#include <QStandardItemModel>
#include <QCloseEvent>
#include <QItemSelection>


namespace Ui {
class cImportDialog;
}

class cImportDialog : public QDialog
{
	Q_OBJECT

public:
	explicit cImportDialog(QWidget *parent = nullptr);
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
	Ui::cImportDialog*		ui;
	QStandardItemModel*		m_lpImportListModel;					/**< TODO: describe */

	void					initUI();
	void					createActions();

	void					readDirectory(const QString& szPath, bool bRecursive);

	void					accept();
	void					reject();

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
