#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <SDL_mixer.h>

enum SfxType
{
	Coin = 0,
	BtnClick,
	GameOver,
	Poop,
	Move
};

enum BgmType
{
	BGM00 = 0,
	BGM01,
	BGM02,
	BGM03
};

class AudioManager
{
public:
	static AudioManager* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new AudioManager();
		return s_pInstance;
	}
	~AudioManager();
	void init();
	void PlaySFX(SfxType type);
	void StopSFX(SfxType type) { Mix_HaltChannel(type); }
	void StopAllSFX() { Mix_HaltChannel(-1); }
	void PlayBGM();
	void PauseBGM() { Mix_PauseMusic(); }
	void ResumeBGM() { Mix_ResumeMusic(); }
	void StopBGM() { Mix_HaltMusic(); }
	void SetSFXVolume(int value);
	void SetBGMVolume(int value);
	void clean();

private:
	AudioManager();
	static AudioManager* s_pInstance;
	Mix_Chunk* m_sfxs[5];
	Mix_Music* m_bgms[4];
	int m_sfxVolume, m_bgmVolume;
};

typedef AudioManager TheAudioManager;