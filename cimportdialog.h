#ifndef CIMPORTDIALOG_H
#define CIMPORTDIALOG_H


#include <QDialog>
#include <QCloseEvent>


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
	void on_m_lpPathSelect_clicked();

private:
	Ui::cImportDialog *ui;

protected:
	/*!
	 \brief

	 \fn closeEvent
	 \param event
	*/
	void					closeEvent(QCloseEvent* event);
};

#endif // CIMPORTDIALOG_H
