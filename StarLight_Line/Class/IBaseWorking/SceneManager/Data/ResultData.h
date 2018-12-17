#ifndef RESULT_DATA_H
#define RESULT_DATA_H

#include <windows.h>

struct ResultData
{
public:
	INT m_score = 19990618;

	INT m_clearStarMax	= 8;
	INT m_clearStarsNum = 5;

	BOOL m_isFailed = FALSE;
};

#endif // !RESULT_DATA_H
