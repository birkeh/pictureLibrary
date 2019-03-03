#ifndef CCOPIER_H
#define CCOPIER_H


#include <QObject>

#include <QtConcurrent>
#include <windows.h>
#include <comdef.h>


class cCopier : public QObject
{
	Q_OBJECT

	BOOL			m_stop;
	QMutex			m_pauseMutex;
	QAtomicInt		m_pause;
	QWaitCondition	m_pauseWait;

	QString			m_src;
	QString			m_dst;
	ULONGLONG		m_lastPart;
	ULONGLONG		m_lastWhole;

	void			newStatus(ULONGLONG part, ULONGLONG whole);

#if _WIN32_WINNT >= _WIN32_WINNT_WIN8
	static COPYFILE2_MESSAGE_ACTION CALLBACK copyProgress2(const COPYFILE2_MESSAGE *message, PVOID context);
#else
   static DWORD CALLBACK copyProgress(LARGE_INTEGER totalSize, LARGE_INTEGER totalTransferred, LARGE_INTEGER streamSize, LARGE_INTEGER streamTransferred, DWORD streamNo, DWORD callbackReason, HANDLE src, HANDLE dst, LPVOID data);
#endif

public:
	explicit cCopier(const QString& src, const QString& dst, QObject* parent = nullptr);
	~cCopier() override;

signals:
	void			newStatus(int percent);
	void			finished();

public slots:
	void			copy();
	void			stop();
	void			pause();
	void			resume();
};

#endif // CCOPIER_H
