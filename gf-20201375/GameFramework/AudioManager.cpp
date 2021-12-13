#include "AudioManager.h"
#include <random>
#include <charconv>

AudioManager* AudioManager::s_pInstance = 0;

const char* m_sfxPaths[] =
	{
		"Assets/Audio/SFX/Coin.wav",
		"Assets/Audio/SFX/BtnClick.mp3",
		"Assets/Audio/SFX/GameOver.wav",
		"Assets/Audio/SFX/Poop.mp3",
		"Assets/Audio/SFX/Move.mp3"
	};

const char* m_bgmPaths[] =
	{
		"Assets/Audio/BGM/BGM00.wav",
		"Assets/Audio/BGM/BGM01.wav",
		"Assets/Audio/BGM/BGM02.wav",
		"Assets/Audio/BGM/BGM03.wav"
	};

AudioManager::AudioManager()
{
#ifdef WIN32
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
#endif

	init();
}

void AudioManager::init()
{
#ifdef WIN32
	for(int i = 0; i < 5; i++)
		m_sfxs[i] = Mix_LoadWAV(m_sfxPaths[i]);

	for(int i = 0; i < 4; i++)
		m_bgms[i] = Mix_LoadMUS(m_bgmPaths[i]);

	SetBGMVolume(20);
	SetSFXVolume(70);
	Mix_VolumeChunk(m_sfxs[SfxType::Move], 30);
#endif 
}

void AudioManager::PlaySFX(SfxType type)
{
#ifdef WIN32
	switch (type)
	{
	case SfxType::Coin: Mix_PlayChannel(0, m_sfxs[SfxType::Coin], 0); break;
	case SfxType::BtnClick: Mix_PlayChannel(1, m_sfxs[SfxType::BtnClick], 0); break;
	case SfxType::GameOver: Mix_PlayChannel(2, m_sfxs[SfxType::GameOver], 0); break;
	case SfxType::Poop: Mix_PlayChannel(3, m_sfxs[SfxType::Poop], 0); break;
	case SfxType::Move: Mix_PlayChannel(4, m_sfxs[SfxType::Move], -1); break;
	default: break;
	}
#endif
}

void AudioManager::PlayBGM()
{
#ifdef WIN32
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 3);

	int randNum = dis(gen);

	Mix_PlayMusic(m_bgms[randNum], -1);
#endif
}

void AudioManager::SetSFXVolume(int value)
{
	if (value >= 0 && value <= 100)
		m_sfxVolume = value;
	else
		m_sfxVolume = 50;

#ifdef WIN32
	for (int i = 0; i < 5; i++)
		Mix_VolumeChunk(m_sfxs[i], m_sfxVolume);

#endif // WIN32
}

void AudioManager::SetBGMVolume(int value)
{
	if (value >= 0 && value <= 100)
		m_bgmVolume = value;
	else
		m_bgmVolume = 50;

#ifdef WIN32
	Mix_VolumeMusic(m_bgmVolume);
#endif
}

void AudioManager::clean()
{
#ifdef WIN32
	Mix_CloseAudio();
#endif
}

AudioManager::~AudioManager()
{
	clean();
}