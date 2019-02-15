#ifndef CTHUMBNAILFILTERPROXYMODEL_H
#define CTHUMBNAILFILTERPROXYMODEL_H


#include <QSortFilterProxyModel>


/**
 * @brief
 *
 */
class cThumbnailFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	cThumbnailFilterProxyModel(QObject* parent = nullptr);

	/**
	 * @brief
	 *
	 * @return QString
	 */
	QString					filterPath();
	/**
	 * @brief
	 *
	 * @param szPath
	 */
	void					setFilterPath(const QString& szPath);

protected:
	/**
	 * @brief
	 *
	 * @param sourceRow
	 * @param sourceParent
	 * @return bool
	 */
	bool					filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
	QString					m_szPath; /**< TODO: describe */
};

#endif // CTHUMBNAILFILTERPROXYMODEL_H
