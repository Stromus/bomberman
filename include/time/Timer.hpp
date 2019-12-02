/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_TIMER_HPP
#define INDIE_STUDIO_TIMER_HPP

#include <map>
#include <chrono>

namespace timer {
	struct Tick {
		std::chrono::steady_clock::time_point	last;
		std::chrono::milliseconds		pausedTime;
		double	tick;
		int	nb_ticked;
	};

	class Timer {
	public:
		Timer(const Timer &timer) = delete;
		Timer(Timer &&timer) = delete;
		Timer& operator=(const Timer &timer) = delete;

	public:
		static Timer *getInstance();

	public:
		int	getTick(int id) noexcept;
		int	newTick(double tickDuration) noexcept;
		void	deleteTick(int id) noexcept;
		void	deleteAllTicks() noexcept;
		void	activatePause() noexcept;
		void	desactivatePause() noexcept;

	private:
		explicit	Timer() = default;
		static Timer	singleton;

	private:
		std::map<int, Tick>			_registredTicks;
		std::chrono::steady_clock::time_point	_activePause;
	};
}

#endif //INDIE_STUDIO_TIMER_HPP
