#include "ccopier.h"


static QString toString(HRESULT hr)
{
	_com_error err{hr};
	return QStringLiteral("Error 0x%1: %2").arg((quint32)hr, 8, 16, QLatin1Char('0')).arg(err.ErrorMessage());
}

static QString getLastErrorMsg()
{
	return toString(HRESULT_FROM_WIN32(GetLastError()));
}

cCopier::cCopier(const QString& src, const QString& dst, QObject* parent) :
	QObject(parent),
	m_src(src),
	m_dst(dst)
{
}

cCopier::~cCopier()
{
	stop();
}

void cCopier::stop()
{
	resume();
	m_stop	= TRUE;
}

void cCopier::pause()
{
	m_pause = true;
}

void cCopier::resume()
{
	if(m_pause)
		m_pauseWait.notify_one();
	m_pause = false;
}

void cCopier::newStatus(ULONGLONG part, ULONGLONG whole)
{
	if(part != m_lastPart || whole != m_lastWhole)
	{
		m_lastPart	= part;
		m_lastWhole	= whole;
		emit newStatus(static_cast<int>(part*100/whole));
	}
}

#if _WIN32_WINNT >= _WIN32_WINNT_WIN8
void cCopier::copy()
{
	m_lastPart	= m_lastWhole	= {};
	m_stop		= FALSE;
	m_pause		= false;
	QtConcurrent::run([this]
	{
		COPYFILE2_EXTENDED_PARAMETERS params
		{
			sizeof(COPYFILE2_EXTENDED_PARAMETERS), 0, &m_stop,
			Copier::copyProgress2, this
		};
		auto rc = CopyFile2((PCWSTR)m_src.utf16(), (PCWSTR)m_dst.utf16(), &params);
		if(!SUCCEEDED(rc))
			emit newStatus(toString(rc));
		emit finished();
	});
}

COPYFILE2_MESSAGE_ACTION CALLBACK cCopier::copyProgress2(const COPYFILE2_MESSAGE *message, PVOID context)
{
	COPYFILE2_MESSAGE_ACTION	action	= COPYFILE2_PROGRESS_CONTINUE;
	auto						self	= static_cast<Copier*>(context);

	if(message->Type == COPYFILE2_CALLBACK_CHUNK_FINISHED)
	{
		auto&	info	= message->Info.ChunkFinished;
		self->newStatus(info.uliTotalBytesTransferred.QuadPart, info.uliTotalFileSize.QuadPart);
	}
	else if (message->Type == COPYFILE2_CALLBACK_ERROR)
	{
		auto&	info	= message->Info.Error;
		self->newStatus(info.uliTotalBytesTransferred.QuadPart, info.uliTotalFileSize.QuadPart);
		emit self->newStatus(toString(info.hrFailure));
		action = COPYFILE2_PROGRESS_CANCEL;
	}

	if(self->m_pause)
	{
		QMutexLocker lock{&self->m_pauseMutex};
		self->m_pauseWait.wait(&self->m_pauseMutex);
	}
	return action;
}
#else
void cCopier::copy()
{
	m_lastPart	= m_lastWhole = {};
	m_stop		= FALSE;
	m_pause		= false;
	QtConcurrent::run([this]
	{
		auto	rc	= CopyFileExW((LPCWSTR)m_src.utf16(), (LPCWSTR)m_dst.utf16(), &copyProgress, this, &m_stop, 0);
		if(!rc)
		{
			qDebug() << getLastErrorMsg();
			emit newStatus(-1);
		}
		emit finished();
	});
}

DWORD CALLBACK cCopier::copyProgress(const LARGE_INTEGER totalSize, const LARGE_INTEGER totalTransferred, LARGE_INTEGER, LARGE_INTEGER, DWORD, DWORD, HANDLE, HANDLE, LPVOID data)
{
	auto	self	= static_cast<cCopier*>(data);
	self->newStatus(totalTransferred.QuadPart, totalSize.QuadPart);
	if(self->m_pause)
	{
		QMutexLocker lock{&self->m_pauseMutex};
		self->m_pauseWait.wait(&self->m_pauseMutex);
	}
	return PROGRESS_CONTINUE;
}
#endif
