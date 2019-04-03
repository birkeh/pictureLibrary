#include "cstyleddelegate.h"

#include <QPainter>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>

#include <QDebug>


void cStyledDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QStyleOptionViewItem	options	= option;
	initStyleOption(&options, index);

	bool			bBold	= index.data(STYLEDDELEGATE_BOLD).toBool();
	bool			bItalic	= index.data(STYLEDDELEGATE_ITALIC).toBool();
	QColor			color	= index.data(STYLEDDELEGATE_COLOR).value<QColor>();

	options.font.setBold(bBold);
	options.font.setItalic(bItalic);
	if(color.isValid())
		options.palette.setColor(QPalette::Text, color);

	QStyledItemDelegate::paint(painter, options, index);
}

//QSize cStyledDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
//{
//	QStyleOptionViewItem	options	= option;
//	initStyleOption(&options, index);

//	QTextDocument doc;
//	doc.setHtml(options.text);
//	doc.setTextWidth(options.rect.width());
//	return QSize(static_cast<int>(doc.idealWidth()), static_cast<int>(doc.size().height()));
//}
