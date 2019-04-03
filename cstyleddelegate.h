#ifndef CSTYLEDDELEGATE_H
#define CSTYLEDDELEGATE_H


#include <QStyledItemDelegate>


#define STYLEDDELEGATE_BOLD		(Qt::UserRole+10)
#define STYLEDDELEGATE_ITALIC	(Qt::UserRole+11)
#define STYLEDDELEGATE_COLOR	(Qt::UserRole+12)


class cStyledDelegate : public QStyledItemDelegate
{
protected:
	void		paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
//	QSize		sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

#endif // CSTYLEDDELEGATE_H
