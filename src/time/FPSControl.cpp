/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <thread>
#include "settings/Settings.hpp"
#include "time/FPSControl.hpp"

FPSControl	FPSControl::singleton;

FPSControl *FPSControl::getInstance()
{
	return &singleton;
}

FPSControl::FPSControl()
	: _numberFPS(Settings::getInstance()->getNumberFPS()),
	_waitTime(1000.0 / _numberFPS),
	_beginLoop(std::chrono::system_clock::now()),
	_endLoop(std::chrono::system_clock::now()),
	_workTime()
{}

void FPSControl::updateWaitTime() noexcept
{
	_numberFPS = Settings::getInstance()->getNumberFPS();
	_waitTime = (1000.0 / _numberFPS);
}

void FPSControl::beginLoop() noexcept
{
	_beginLoop = std::chrono::system_clock::now();
	updateWaitTime();
	_workTime = _beginLoop - _endLoop;
	if (_workTime.count() < _waitTime)
	{
		std::chrono::duration<double, std::milli> delta_ms(_waitTime - _workTime.count());
		auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
		std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
	}
}

void FPSControl::endLoop() noexcept
{
	_endLoop = std::chrono::system_clock::now();
}
