#ifndef CIMAGE_H
#define CIMAGE_H


#include <QImage>


/**
 * @brief
 *
 */
class cImage : public QImage
{
public:
	cImage();
	/**
	 * @brief
	 *
	 * @param size
	 * @param format
	 */
	cImage(const QSize &size, QImage::Format format);
	/**
	 * @brief
	 *
	 * @param width
	 * @param height
	 * @param format
	 */
	cImage(int width, int height, QImage::Format format);
	/**
	 * @brief
	 *
	 * @param data
	 * @param width
	 * @param height
	 * @param format
	 * @param cleanupFunction
	 * @param cleanupInfo
	 */
	cImage(uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	/**
	 * @brief
	 *
	 * @param data
	 * @param width
	 * @param height
	 * @param format
	 * @param cleanupFunction
	 * @param cleanupInfo
	 */
	cImage(const uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	/**
	 * @brief
	 *
	 * @param data
	 * @param width
	 * @param height
	 * @param bytesPerLine
	 * @param format
	 * @param cleanupFunction
	 * @param cleanupInfo
	 */
	cImage(uchar *data, int width, int height, int bytesPerLine, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	/**
	 * @brief
	 *
	 * @param data
	 * @param width
	 * @param height
	 * @param bytesPerLine
	 * @param format
	 * @param cleanupFunction
	 * @param cleanupInfo
	 */
	cImage(const uchar *data, int width, int height, int bytesPerLine, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr);
	/**
	 * @brief
	 *
	 * @param fileName
	 * @param format
	 */
	cImage(const QString &fileName, const char *format = nullptr);
	/**
	 * @brief
	 *
	 * @param image
	 */
	cImage(const QImage &image);
	/**
	 * @brief
	 *
	 * @param other
	 */
	cImage(QImage &&other);

	/**
	 * @brief
	 *
	 * @param fileName
	 * @param format
	 * @return bool
	 */
	bool	load(const QString &fileName, const char *format = nullptr);

private:
	/**
	 * @brief
	 *
	 * @param fileName
	 * @return bool
	 */
	bool	loadRAW(const QString &fileName);
};

#endif // CIMAGE_H
