/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_CONTROLS_HPP
#define INDIE_STUDIO_CONTROLS_HPP

#include <map>
#include <queue>

class Controls {
public:
	enum keyIS {
		ERROR = -1,
		KEY_A = 0,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_SPACE,
		KEY_ESC,
		KEY_ENTER,
		KEY_BACKSPACE,
		KEY_ARROW_UP,
		KEY_ARROW_DOWN,
		KEY_ARROW_LEFT,
		KEY_ARROW_RIGHT,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		MAX_KEY
	};

	enum actions {
		UNDEFINED = -1,
		MOVE_UP = 0,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		BOMB,
		MAX_ACTION
	};

	Controls(const Controls &controls) = delete;
	Controls(Controls &&controls) = delete;
	Controls &operator=(const Controls &controls) = delete;

public:
	static Controls *getInstance();

	bool	isKeyPressed(const keyIS &key) const noexcept;
	void	changeKeyStatus(const keyIS &key, const bool &status) noexcept;
	bool	isEmpty() const noexcept;
	keyIS	getNextKey() const noexcept;
	void	eraseNextKey() noexcept;
	void	addNewKey(const keyIS &key) noexcept;
	const std::wstring	getKeyName(const Controls::keyIS &key) const;

private:
	explicit	Controls();
	static Controls	singleton;

private:
	std::map<keyIS, bool>	_pressedKeysMap;
	std::queue<keyIS>	_pressedKeysVector;
	std::map<Controls::keyIS, std::wstring>	_keysName;
};

#endif //INDIE_STUDIO_CONTROLS_HPP
