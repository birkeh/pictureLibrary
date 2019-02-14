#ifndef CDATETIMEPICKER_H
#define CDATETIMEPICKER_H


#include <QDialog>
#include <QImage>


namespace Ui {
class cDateTimePicker;
}

class cDateTimePicker : public QDialog
{
	Q_OBJECT

public:
	explicit cDateTimePicker(QWidget *parent = nullptr);
	~cDateTimePicker();

	void					setText(const QString& szText);
	void					setImage(const QImage& image);
	void					setDateTime(const QDateTime dateTime);
	QDateTime				dateTime();
private:
	Ui::cDateTimePicker*	ui;
};

#endif // CDATETIMEPICKER_H
