#ifndef CFILTERPANEL_H
#define CFILTERPANEL_H

#include <QWidget>

namespace Ui {
class cFilterPanel;
}

class cFilterPanel : public QWidget
{
	Q_OBJECT

public:
	explicit cFilterPanel(QWidget *parent = nullptr);
	~cFilterPanel();

private:
	Ui::cFilterPanel *ui;
};

#endif // CFILTERPANEL_H
