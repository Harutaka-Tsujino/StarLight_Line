/// <filename>
/// 
/// </filename>
/// <summary>
///
/// </summary>
/// <author>
/// 
/// </author>

#ifndef ADV_H
#define ADV_H

#include <windows.h>
#include <tchar.h>

#include "../../Obj.h"
#include "../../../../../Data/StageData.h"
#include "Chapter/Chapter.h"

class ADV :public Obj
{
public:
	explicit ADV(const LONGLONG& stageTime_ms);

	~ADV()
	{
		delete m_pChapter;
	}

	inline VOID Update()
	{
		m_pChapter->Update();
	}

	inline VOID Render()
	{
		m_pChapter->Render();
	}

	inline BOOL IsActive()
	{
		return m_pChapter->IsActive();
	}

private:
	ADV& operator=(const ADV&) = delete;
	ADV(const ADV&) = delete;

	Chapter* m_pChapter = nullptr;
};

#endif //! ADV_H
