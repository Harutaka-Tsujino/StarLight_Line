#ifndef PREVIEW_DATA_H
#define PREVIEW_DATA_H

#include <windows.h>

#include <ctime>

struct PreviewData
{
public:
	INT m_totalTime_partHour = NULL;
	INT m_totalTime_partMin	 = NULL;

	tm* pLastPlayTm = nullptr;

	INT m_maxScore = 0;
	INT m_clearNum = 0;
};

#endif //! PREVIEW_DATA_H
