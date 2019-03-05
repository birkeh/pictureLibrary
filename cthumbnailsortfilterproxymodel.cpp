/*!
 \file cthumbnailfilterproxymodel.cpp

*/

#include "cthumbnailsortfilterproxymodel.h"


cThumbnailSortFilterProxyModel::cThumbnailSortFilterProxyModel(QObject* parent) :
	QSortFilterProxyModel (parent)
{
}

void cThumbnailSortFilterProxyModel::setFilterPath(const QString &szPath)
{
	m_szPath	= szPath;
	m_szPath.replace("\\", "/");

	invalidateFilter();
}

QString cThumbnailSortFilterProxyModel::filterPath()
{
	return(m_szPath);
}

bool cThumbnailSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
	QModelIndex	index0	= sourceModel()->index(sourceRow, 0, sourceParent);
	QString		tmp		= sourceModel()->data(index0, Qt::UserRole+2).toString();
	return(sourceModel()->data(index0, Qt::UserRole+2).toString().startsWith(m_szPath));
}
