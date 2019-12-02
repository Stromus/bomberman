/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "exception/IndieStudioException.hpp"
#include "render/Irrlicht.hpp"
#include "render/Animator.hpp"
#include "engine/scene/GuiManager.hpp"

int	main()
{
	try {
		Irrlicht::getInstance()->loadMeshFactory();
		render::Animator::initalizeTextureBeam();
		Irrlicht::getInstance()->getDevice()->getCursorControl()->setVisible(false);
		irr::gui::IGUISkin *skin = Irrlicht::getInstance()->getGUIEnv()->getSkin();
		irr::gui::IGUIFont *font = Irrlicht::getInstance()->getGUIEnv()->getFont("./res/font/franklin_22px.bmp");
		if (font)
			skin->setFont(font);
		engine::GuiManager	guiManager;
		Irrlicht::getInstance()->removeStartScreen();
		guiManager.startScene();
	}
	catch (const ise::IndieStudioException &error) {
		Irrlicht::getInstance()->getDevice()->drop();
		std::cerr << error.what() << std::endl;
		return 84;
	}
	Irrlicht::getInstance()->getDevice()->drop();
	return 0;
}