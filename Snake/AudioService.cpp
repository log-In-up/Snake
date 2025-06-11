#include "AudioService.h"

namespace Snake
{
	AudioService::AudioService(ResourceData& resourceData) : resourceData(resourceData)
	{
		soundSettingsBitMask = static_cast<uint32_t>(SoundSettings::Default);
	}

	AudioService::~AudioService()
	{
	}

	bool AudioService::IsEnabled(const SoundSettings settings)
	{
		return soundSettingsBitMask & static_cast<uint32_t>(settings);
	}

	void AudioService::PlayLose()
	{
		if (!IsEnabled(SoundSettings::Sound))
		{
			return;
		}

		resourceData.lose.play();
	}

	void AudioService::PlaySelectMenuItem()
	{
		if (!IsEnabled(SoundSettings::Sound))
		{
			return;
		}

		resourceData.menu.play();
	}

	void AudioService::PlaySnakeHit()
	{
		if (!IsEnabled(SoundSettings::Sound))
		{
			return;
		}
		resourceData.snakeHit.play();
	}

	void AudioService::PlayStartSession()
	{
		if (!IsEnabled(SoundSettings::Sound))
		{
			return;
		}
		resourceData.startSession.play();
	}

	void AudioService::SetPlayBackground(bool value)
	{
		if (!IsEnabled(SoundSettings::Music))
		{
			return;
		}

		resourceData.background.setLoop(value);

		if (value)
		{
			resourceData.background.play();
		}
		else
		{
			resourceData.background.stop();
		}
	}

	void AudioService::SetSettings(SoundSettings settings)
	{
		soundSettingsBitMask ^= static_cast<uint32_t>(settings);
	}
}