/*
** EPITECH PROJECT, 2021
** indie_studio
** File Description:
** Created by simong,
*/

#include "render/EventReceiver.hpp"

#include "render/Animator.hpp"

bool render::EventReceiver::OnEvent(const irr::SEvent &event)
{
	try {
		if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
			Controls::getInstance()->changeKeyStatus(keyEq.at(event.KeyInput.Key), event.KeyInput.PressedDown);
			if (event.KeyInput.PressedDown)
				Controls::getInstance()->addNewKey(keyEq.at(event.KeyInput.Key));
			return !(Irrlicht::getInstance()->isDispatchingKey());
		}
	} catch (std::exception e) {
		Controls::getInstance()->addNewKey(Controls::ERROR);
		std::cerr << "Key not supported" << std::endl;
	}
	return false;
}
