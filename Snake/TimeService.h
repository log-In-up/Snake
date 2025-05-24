#pragma once

namespace Snake
{
	const float ZERO_DELTA_TIME = 0.f;

	class TimeService
	{
	public:
		TimeService();
		~TimeService();
		float GetDeltaTime();
		void Initialization();
	};

	bool& TimeIsPaused();
	void SetPause(bool value);
};