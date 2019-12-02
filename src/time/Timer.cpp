/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#if defined(__WIN32__)
	#include <Windows.h>
#endif
#include <iostream>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <exception>
#include <thread>
#include <irrTypes.h>
#include "time/Timer.hpp"

timer::Timer timer::Timer::singleton;

timer::Timer *timer::Timer::getInstance()
{
	return &singleton;
}

int timer::Timer::getTick(int id) noexcept
{
	std::chrono::milliseconds timeElapsed;

	timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _registredTicks[id].last);
	timeElapsed -= _registredTicks[id].pausedTime;
	auto duration = static_cast<double>(timeElapsed.count());
	auto nb_tick = static_cast<int>(duration / _registredTicks[id].tick);
	nb_tick -= _registredTicks[id].nb_ticked;
	_registredTicks[id].nb_ticked += nb_tick;
	return (nb_tick);
}

void timer::Timer::activatePause() noexcept
{
	_activePause = std::chrono::steady_clock::now();
}

void timer::Timer::desactivatePause() noexcept
{
	for (auto &tick : _registredTicks)
		tick.second.pausedTime += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _activePause);
}

int timer::Timer::newTick(double tickDuration) noexcept
{
	timer::Tick tick;

	tick.last = std::chrono::steady_clock::now();
	tick.tick = tickDuration;
	tick.pausedTime = std::chrono::milliseconds::zero();
	tick.nb_ticked = 0;
	for (int i = 0;; ++i) {
		try {
			_registredTicks.at(i);
		}
		catch (const std::out_of_range &e) {
			static_cast<void>(e);
			_registredTicks[i] = tick;
			return (i);
		}
	}
}

void timer::Timer::deleteTick(int id) noexcept
{
	_registredTicks.erase(id);
}

void timer::Timer::deleteAllTicks() noexcept
{
	for (auto it = _registredTicks.begin(); it != _registredTicks.end(); it = _registredTicks.begin())
		deleteTick(it->first);
	desactivatePause();
}
