/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "settings/Controls.hpp"
#include <exception>

Controls	Controls::singleton;

Controls *Controls::getInstance()
{
	return &singleton;
}

Controls::Controls()
{
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_A, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_B, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_C, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_D, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_E, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_F, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_G, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_H, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_I, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_J, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_K, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_L, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_M, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_N, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_O, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_P, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_Q, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_R, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_S, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_T, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_U, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_V, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_W, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_X, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_Y, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_Z, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_0, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_1, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_2, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_3, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_4, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_5, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_6, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_7, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_8, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_9, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_SPACE, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_ESC, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_ENTER, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_BACKSPACE, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_ARROW_UP, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_ARROW_DOWN, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_ARROW_LEFT, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_ARROW_RIGHT, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_PAGE_UP, false));
	_pressedKeysMap.insert(std::pair<keyIS, bool>(KEY_PAGE_DOWN, false));

	_keysName.insert(std::make_pair(ERROR, L"Error"));
	_keysName.insert(std::make_pair(KEY_A, L"A"));
	_keysName.insert(std::make_pair(KEY_B, L"B"));
	_keysName.insert(std::make_pair(KEY_C, L"C"));
	_keysName.insert(std::make_pair(KEY_D, L"D"));
	_keysName.insert(std::make_pair(KEY_E, L"E"));
	_keysName.insert(std::make_pair(KEY_F, L"F"));
	_keysName.insert(std::make_pair(KEY_G, L"G"));
	_keysName.insert(std::make_pair(KEY_H, L"H"));
	_keysName.insert(std::make_pair(KEY_I, L"I"));
	_keysName.insert(std::make_pair(KEY_J, L"J"));
	_keysName.insert(std::make_pair(KEY_K, L"K"));
	_keysName.insert(std::make_pair(KEY_L, L"L"));
	_keysName.insert(std::make_pair(KEY_M, L"M"));
	_keysName.insert(std::make_pair(KEY_N, L"N"));
	_keysName.insert(std::make_pair(KEY_O, L"O"));
	_keysName.insert(std::make_pair(KEY_P, L"P"));
	_keysName.insert(std::make_pair(KEY_Q, L"Q"));
	_keysName.insert(std::make_pair(KEY_R, L"R"));
	_keysName.insert(std::make_pair(KEY_S, L"S"));
	_keysName.insert(std::make_pair(KEY_T, L"T"));
	_keysName.insert(std::make_pair(KEY_U, L"U"));
	_keysName.insert(std::make_pair(KEY_V, L"V"));
	_keysName.insert(std::make_pair(KEY_W, L"W"));
	_keysName.insert(std::make_pair(KEY_X, L"X"));
	_keysName.insert(std::make_pair(KEY_Y, L"Y"));
	_keysName.insert(std::make_pair(KEY_Z, L"Z"));
	_keysName.insert(std::make_pair(KEY_0, L"num0"));
	_keysName.insert(std::make_pair(KEY_1, L"num1"));
	_keysName.insert(std::make_pair(KEY_2, L"num2"));
	_keysName.insert(std::make_pair(KEY_3, L"num3"));
	_keysName.insert(std::make_pair(KEY_4, L"num4"));
	_keysName.insert(std::make_pair(KEY_5, L"num5"));
	_keysName.insert(std::make_pair(KEY_6, L"num6"));
	_keysName.insert(std::make_pair(KEY_7, L"num7"));
	_keysName.insert(std::make_pair(KEY_8, L"num8"));
	_keysName.insert(std::make_pair(KEY_9, L"num9"));
	_keysName.insert(std::make_pair(KEY_SPACE, L"SPACE"));
	_keysName.insert(std::make_pair(KEY_ESC, L"ESC"));
	_keysName.insert(std::make_pair(KEY_ENTER, L"ENTER"));
	_keysName.insert(std::make_pair(KEY_BACKSPACE, L"BACKSPACE"));
	_keysName.insert(std::make_pair(KEY_ARROW_UP, L"UP"));
	_keysName.insert(std::make_pair(KEY_ARROW_DOWN, L"DOWN"));
	_keysName.insert(std::make_pair(KEY_ARROW_LEFT, L"LEFT"));
	_keysName.insert(std::make_pair(KEY_ARROW_RIGHT, L"RIGHT"));
	_keysName.insert(std::make_pair(KEY_PAGE_UP, L"PAGE UP"));
	_keysName.insert(std::make_pair(KEY_PAGE_DOWN, L"PAGE DOWN"));
}

void Controls::changeKeyStatus(const Controls::keyIS &key, const bool &status) noexcept
{
	_pressedKeysMap.at(key) = status;
}

bool Controls::isKeyPressed(const keyIS &key) const noexcept
{
	return _pressedKeysMap.at(key);
}

bool Controls::isEmpty() const noexcept
{
	return _pressedKeysVector.empty();
}

Controls::keyIS Controls::getNextKey() const noexcept
{
	if (_pressedKeysVector.empty())
		return Controls::ERROR;
	return _pressedKeysVector.front();
}

void Controls::eraseNextKey() noexcept
{
	_pressedKeysVector.pop();
}

void Controls::addNewKey(const Controls::keyIS &key) noexcept
{
	_pressedKeysVector.push(key);
}

const std::wstring Controls::getKeyName(const Controls::keyIS &key) const
{
	try {
		return _keysName.at(key);
	}
	catch (const std::out_of_range &e) {
		static_cast<void>(e);
		return (L"ERROR");
	}
}
