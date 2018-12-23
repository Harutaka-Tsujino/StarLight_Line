#ifndef SOUND_H
#define SOUND_H

#include <windows.h>
#include <tchar.h>

#include <SoundsManager.h>

class Sound
{
public:
	Sound()
	{
		m_soundsManager.Initialize();
	}

	~Sound() {};

	inline VOID AddFile(const TCHAR* pFilePath, const TCHAR* pKey)
	{
		m_soundsManager.AddFile(pFilePath, pKey);
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

private:
	SoundLib::SoundsManager m_soundsManager;
};

#endif // !SOUND_H
