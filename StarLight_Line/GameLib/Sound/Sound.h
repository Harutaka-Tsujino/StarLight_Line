#ifndef SOUND_H
#define SOUND_H

#include <windows.h>
#include <tchar.h>

#include <vector>
#include <map>
#include <array>

#include <SoundsManager.h>

class Sound
{
public:
	Sound()
	{
		m_soundsManager.Initialize();
	}

	~Sound() 
	{
		for (auto i : m_simultaneousKeys)
		{
			for (INT si = 0; si < SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX; ++si)
			{
				delete[](i.second.m_pKeys[si]);
			}
		}

		m_simultaneousKeys.clear();
	}

	inline VOID AddFile(const TCHAR* pFilePath, const TCHAR* pKey)
	{
		m_soundsManager.AddFile(pFilePath, pKey);
	}

	inline VOID AddSimultaneousFile(const TCHAR* pFilePath, const TCHAR* pKey)
	{
		size_t tCharLength = _tcsclen(pKey);
		size_t additionalKeyLength = tCharLength + 3;	//! 数字と\0の数足す

		for (INT i = 0; i < SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX; ++i)
		{
			m_simultaneousKeys[pKey].m_pKeys[i] = new TCHAR[additionalKeyLength];

			_tcscpy_s(m_simultaneousKeys[pKey].m_pKeys[i], additionalKeyLength, pKey);

			_itot_s(i, &m_simultaneousKeys[pKey].m_pKeys[i][tCharLength], sizeof(TCHAR) * (1 + (i / SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX)), 10);
			m_simultaneousKeys[pKey].m_pKeys[i][tCharLength + 1 + (i / SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX)] = m_TEXT_END;

			m_soundsManager.AddFile(pFilePath, &m_simultaneousKeys[pKey].m_pKeys[i][0]);
		}
	}

	inline VOID OneShotSimultaneous(const TCHAR* pKey)
	{
		INT currentNum = m_simultaneousKeys[pKey].m_currentPlayNum;
	
		INT prevPrevNum = currentNum - 2;

		if (prevPrevNum < 0) prevPrevNum = SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX + prevPrevNum;

		Stop(&m_simultaneousKeys[pKey].m_pKeys[prevPrevNum][0]);

		OneShotStart(&m_simultaneousKeys[pKey].m_pKeys[currentNum][0]);

		m_simultaneousKeys[pKey].m_currentPlayNum = (currentNum >= (SimultaneousKeys::m_SIMULTANEOUS_NUM_MAX - 1)) ? 0 : ++currentNum;
	}

	inline VOID LoopStart(const TCHAR* pKey)
	{
		m_soundsManager.Start(pKey, true);
	}

	inline VOID OneShotStart(const TCHAR* pKey)
	{
		m_soundsManager.Start(pKey, false);
	}

	inline VOID Pause(const TCHAR* pKey)
	{
		m_soundsManager.Pause(pKey);
	}

	inline VOID Resume(const TCHAR* pKey)
	{
		m_soundsManager.Resume(pKey);
	}

	inline VOID Stop(const TCHAR* pKey)
	{
		m_soundsManager.Stop(pKey);
	}

	inline VOID SetVolume(const TCHAR* pKey, INT vol)
	{
		m_soundsManager.SetVolume(pKey, vol);
	}

private:
	struct SimultaneousKeys
	{
	public:
		static const INT m_SIMULTANEOUS_NUM_MAX = 10;
		TCHAR* m_pKeys[m_SIMULTANEOUS_NUM_MAX];
		INT m_currentPlayNum = 0;
	};

	SoundLib::SoundsManager m_soundsManager;
	
	const TCHAR m_TEXT_END = _T('\0');

	std::map<const TCHAR*, SimultaneousKeys> m_simultaneousKeys;
};

#endif // !SOUND_H
