#include "RE/S/Sky.h"

#include "RE/T/TESClimate.h"

namespace RE
{
	Sky* Sky::GetSingleton()
	{
		using func_t = decltype(&Sky::GetSingleton);
		REL::Relocation<func_t> func{ Offset::Sky::GetSingleton };
		return func();
	}

	bool Sky::IsRaining() const
	{
		return currentWeather && currentWeather->data.flags.any(TESWeather::WeatherDataFlag::kRainy) && currentWeather->data.precipitationBeginFadeIn * (1.0f / 255.0f) < currentWeatherPct ||
		       lastWeather && lastWeather->data.flags.any(TESWeather::WeatherDataFlag::kRainy) && (lastWeather->data.precipitationEndFadeOut * (1.0f / 255.0f) + 0.001f) > currentWeatherPct;
	}

	bool Sky::IsSnowing() const
	{
		return currentWeather && currentWeather->data.flags.any(TESWeather::WeatherDataFlag::kSnow) && currentWeather->data.precipitationBeginFadeIn * (1.0f / 255.0f) < currentWeatherPct ||
		       lastWeather && lastWeather->data.flags.any(TESWeather::WeatherDataFlag::kSnow) && (lastWeather->data.precipitationEndFadeOut * (1.0f / 255.0f) + 0.001f) > currentWeatherPct;
	}

	float Sky::GetDayBeginTime()
	{
		using enum Flags;

		static REL::Relocation<float*> sunriseBeginTime{ Offset::Sky::SunriseBeginTime };
		static REL::Relocation<float*> dayBeginTime{ Offset::Sky::DayBeginTime };

		if (flags.any(kDayBeginTimeNeedsUpdate)) 
		{
			if (flags.any(kSunriseBeginTimeNeedsUpdate)) 
			{
				if (currentClimate) 
				{
					*sunriseBeginTime = currentClimate->timing.sunrise.begin * 0.16666667f;
					flags.reset(kSunriseBeginTimeNeedsUpdate);
				}
			}
			*dayBeginTime = std::max(*sunriseBeginTime - 0.5f, 0.f);
			flags.reset(kDayBeginTimeNeedsUpdate);
		}
		return *dayBeginTime;
	}

	float Sky::GetNightBeginTime()
	{
		using enum Flags;

		static REL::Relocation<float*> sunsetEndTime{ Offset::Sky::SunsetEndTime };
		static REL::Relocation<float*> nightBeginTime{ Offset::Sky::NightBeginTime };

		if (flags.any(kNightBeginTimeNeedsUpdate)) 
		{
			if (flags.any(kSunsetEndTimeNeedsUpdate)) 
			{
				if (currentClimate) 
				{
					*sunsetEndTime = currentClimate->timing.sunset.end * 0.16666667f;
					flags.reset(kSunsetEndTimeNeedsUpdate);
				}
			}
			*nightBeginTime = std::max(*sunsetEndTime + 0.5f, 23.99f);
			flags.reset(kNightBeginTimeNeedsUpdate);
		}
		return *nightBeginTime;
	}

	float Sky::GetSunriseEndTime()
	{
		using enum Flags;

		static REL::Relocation<float*> sunriseEndTime{ Offset::Sky::SunriseEndTime };

		if (flags.any(kSunriseEndTimeNeedsUpdate)) 
		{
			if (currentClimate) 
			{
				*sunriseEndTime = currentClimate->timing.sunrise.end * 0.16666667f;
				flags.reset(kSunriseEndTimeNeedsUpdate);
			}
		}
		return *sunriseEndTime;
	}

	float Sky::GetSunsetBeginTime()
	{
		using enum Flags;

		static REL::Relocation<float*> sunsetBeginTime{ Offset::Sky::SunsetBeginTime };

		if (flags.any(kSunsetBeginTimeNeedsUpdate)) 
		{
			if (currentClimate) 
			{
				*sunsetBeginTime = currentClimate->timing.sunset.begin * 0.16666667f;
				flags.reset(kSunsetBeginTimeNeedsUpdate);
			}
		}
		return *sunsetBeginTime;
	}

	void Sky::SetWeather(TESWeather* a_weather, bool a_override, bool a_accelerate)
	{
		using func_t = decltype(&Sky::SetWeather);
		REL::Relocation<func_t> func{ Offset::Sky::SetWeather };
		func(this, a_weather, a_override, a_accelerate);
	}

	void Sky::ForceWeather(TESWeather* a_weather, bool a_override)
	{
		using func_t = decltype(&Sky::ForceWeather);
		REL::Relocation<func_t> func{ Offset::Sky::ForceWeather };
		func(this, a_weather, a_override);
	}

	void Sky::ResetWeather()
	{
		using func_t = decltype(&Sky::ResetWeather);
		REL::Relocation<func_t> func{ Offset::Sky::ResetWeather };
		func(this);
	}

	Sky::FogTimeInfo Sky::GetFogTimeInfo()
	{
		const float dayBeginTime = GetDayBeginTime();
		const float sunriseEndTime = GetSunriseEndTime();
		const float sunsetBeginTime = GetSunsetBeginTime();
		const float nightBeginTime = GetNightBeginTime();

		if (dayBeginTime >= currentGameHour || currentGameHour >= sunriseEndTime) 
		{
			if (sunriseEndTime > currentGameHour || currentGameHour > sunsetBeginTime) 
			{
				if (sunsetBeginTime >= currentGameHour || currentGameHour >= nightBeginTime) 
				{
					return { 0.0f };
				}
				else 
				{
					return { (nightBeginTime - currentGameHour) / (nightBeginTime - sunsetBeginTime) };
				}
			} 
			else 
			{
				return { 1.0f };
			}
		} 
		else 
		{
			return { (currentGameHour - dayBeginTime) / (sunriseEndTime - dayBeginTime) };
		}
	}

	Sky::ColorTimeInfo Sky::GetColorTimeInfo()
	{
		ColorTimeInfo result;

		const float dayBeginTime = GetDayBeginTime();
		const float sunriseEndTime = GetSunriseEndTime();
		const float sunsetBeginTime = GetSunsetBeginTime();
		const float nightBeginTime = GetNightBeginTime();

		if (dayBeginTime >= currentGameHour || currentGameHour >= sunriseEndTime) 
		{
			if (sunriseEndTime > currentGameHour || currentGameHour > sunsetBeginTime) 
			{
				if (sunsetBeginTime >= currentGameHour) 
				{
					if (currentGameHour < nightBeginTime) 
					{
						result.firstTime = TESWeather::ColorTime::kDay;
						if (currentGameHour > dayBeginTime) 
						{
							return result;
						}
					}
				} 
				else if (currentGameHour < nightBeginTime) 
				{
					result.needsTimeInterpolation = true;
					result.firstTime = TESWeather::ColorTime::kSunset;
					const float halfLength = (nightBeginTime - sunsetBeginTime) * 0.5f;
					const float midTime = halfLength + sunsetBeginTime;
					if (currentGameHour >= midTime) 
					{
						result.timePercent = 1.0f - ((currentGameHour - midTime) / halfLength);
						result.secondTime = TESWeather::ColorTime::kNight;
					} 
					else 
					{
						result.timePercent = 1.0f - ((midTime - currentGameHour) / halfLength);
						result.secondTime = TESWeather::ColorTime::kDay;
					}
					return result;
				}
				result.firstTime = TESWeather::ColorTime::kNight;
			} 
			else 
			{
				result.firstTime = TESWeather::ColorTime::kDay;
			}
		} 
		else 
		{
			result.needsTimeInterpolation = true;
			result.firstTime = TESWeather::ColorTime::kSunrise;
			const float halfLength = (sunriseEndTime - dayBeginTime) * 0.5f;
			const float midTime = halfLength + dayBeginTime;
			if (currentGameHour >= midTime) 
			{
				result.timePercent = 1.0f - ((currentGameHour - midTime) / halfLength);
				result.secondTime = TESWeather::ColorTime::kDay;
			} 
			else 
			{
				result.timePercent = 1.0f - ((midTime - currentGameHour) / halfLength);
				result.secondTime = TESWeather::ColorTime::kNight;
			}
		}

		return result;
	}
}
