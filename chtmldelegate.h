#ifndef CHTMLDELEGATE_H
#define CHTMLDELEGATE_H


#include <QStyledItemDelegate>


class cHTMLDelegate : public QStyledItemDelegate
{
protected:
	void		paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	QSize		sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

#endif // CHTMLDELEGATE_H
