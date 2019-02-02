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
#include "../../DataSaver/DataSaver.h"

class ADV :public Obj
{
public:
	explicit ADV(const LONGLONG& stageTime_ms) :Obj(OT_TRANSPARENCY, 0.0f)
	{
		m_pChapter = new Chapter(GetTextPath(), stageTime_ms);
	}

	~ADV()
	{
		delete m_pChapter;
	}

	inline VOID Update()
	{
		if (DataSaver::GetInstance().CurrentZodiacIsCleared())
		{
			return;
		}

		m_pChapter->Update();
	}

	inline VOID Render()
	{
		if (DataSaver::GetInstance().CurrentZodiacIsCleared())
		{
			return;
		}

		m_pChapter->Render();
	}

	inline BOOL IsActive()
	{
		return m_pChapter->IsActive();
	}

private:
	const TCHAR* GetTextPath();

	ADV& operator=(const ADV&) = delete;
	ADV(const ADV&) = delete;

	Chapter* m_pChapter = nullptr;
};

#endif //! ADV_H
