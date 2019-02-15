#ifndef CDATETIMEPICKER_H
#define CDATETIMEPICKER_H


#include <QDialog>
#include <QImage>


namespace Ui {
class cDateTimePicker;
}

/**
 * @brief
 *
 */
class cDateTimePicker : public QDialog
{
	Q_OBJECT

public:
	/**
	 * @brief
	 *
	 * @param parent
	 */
	explicit cDateTimePicker(QWidget *parent = nullptr);
	/**
	 * @brief
	 *
	 */
	~cDateTimePicker();

	/**
	 * @brief
	 *
	 * @param szText
	 */
	void					setText(const QString& szText);
	/**
	 * @brief
	 *
	 * @param image
	 */
	void					setImage(const QImage& image);
	/**
	 * @brief
	 *
	 * @param dateTime
	 */
	void					setDateTime(const QDateTime dateTime);
	/**
	 * @brief
	 *
	 * @return QDateTime
	 */
	QDateTime				dateTime();
private:
	Ui::cDateTimePicker*	ui; /**< TODO: describe */
};

#endif // CDATETIMEPICKER_H
