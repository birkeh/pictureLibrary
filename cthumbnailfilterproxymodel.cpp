#include "cthumbnailfilterproxymodel.h"


cThumbnailFilterProxyModel::cThumbnailFilterProxyModel(QObject* parent) :
	QSortFilterProxyModel (parent)
{
}

void cThumbnailFilterProxyModel::setFilterPath(const QString &szPath)
{
	m_szPath	= szPath;
	m_szPath.replace("\\", "/");

	invalidateFilter();
}

QString cThumbnailFilterProxyModel::filterPath()
{
	return(m_szPath);
}

bool cThumbnailFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
	QModelIndex	index0	= sourceModel()->index(sourceRow, 0, sourceParent);
	QString		tmp		= sourceModel()->data(index0, Qt::UserRole+2).toString();
	return(sourceModel()->data(index0, Qt::UserRole+2).toString().contains(m_szPath));
}
