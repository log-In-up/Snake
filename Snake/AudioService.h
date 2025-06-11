#pragma once
#include "ResourceLoader.h"

namespace Snake
{
	enum class SoundSettings : std::uint32_t
	{
		Sound = 1 << 0,
		Music = 1 << 1,

		Default = Sound | Music
	};

	class AudioService
	{
	protected:
		ResourceData& resourceData;
		uint32_t soundSettingsBitMask;
	public:
		AudioService(ResourceData& resourceData);
		~AudioService();

		bool IsEnabled(SoundSettings settings);
		void PlayLose();
		void PlaySelectMenuItem();
		void PlaySnakeHit();
		void PlayStartSession();
		void SetPlayBackground(bool value);
		void SetSettings(SoundSettings settings);
	};
}