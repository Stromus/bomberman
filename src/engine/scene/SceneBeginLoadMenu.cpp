/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "settings/Scale.hpp"
#include "sound/Music.hpp"
#include "time/Timer.hpp"
#include "settings/Language.hpp"
#include "engine/scene/SceneBeginLoadMenu.hpp"

engine::SceneBeginLoadMenu::SceneBeginLoadMenu()
{
	_tickID = timer::Timer::getInstance()->newTick(5500);

	addInGraphElem(1, render::MenuElementCreator::createImage(0, Scale::scaleRes(0, 0, 1920, 1080),
		L"Default Text", "res/sprite/img/background_loading_screen.jpg", false));
	addInGraphElem(2, render::MenuElementCreator::createFader(0, Scale::scaleRes(0, 0, 1920, 1080), {1, 1, 1, 0}));
	_menuDisplay = new render::MenuDisplay(_graphElem);
	Music::getInstance()->play(Music::INTRO, false);
}

void engine::SceneBeginLoadMenu::analyseEvent(std::pair<int, render::eventData> &event,
	engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	(void)lastScene;
	(void)loadGame;
	if (timer::Timer::getInstance()->getTick(_tickID) >= 1) {
		timer::Timer::getInstance()->deleteTick(_tickID);
		index = IGuiScene::SCENE_MAIN_MENU;
		Music::getInstance()->play(Music::MENU, true);
	}
}