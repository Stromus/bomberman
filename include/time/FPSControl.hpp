/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_FPSCONTROL_HPP
#define INDIE_STUDIO_FPSCONTROL_HPP

#include <chrono>

class FPSControl {
public:
	FPSControl(const FPSControl &fpsControl) = delete;
	FPSControl(FPSControl &&fpsControl) = delete;
	FPSControl& operator=(const FPSControl &fpsControl) = delete;

public:
	static FPSControl	*getInstance();
	void			beginLoop() noexcept;
	void			endLoop() noexcept;

private:
	explicit FPSControl();
	static FPSControl	singleton;

	void	updateWaitTime() noexcept;

private:
	int	_numberFPS;
	double	_waitTime;
	std::chrono::system_clock::time_point		_beginLoop;
	std::chrono::system_clock::time_point		_endLoop;
	std::chrono::duration<double, std::milli>	_workTime;
};

#endif //INDIE_STUDIO_FPSCONTROL_HPP
