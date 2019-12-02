/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Music.hpp>
#include "settings/Scale.hpp"
#include "settings/Language.hpp"
#include "engine/scene/SceneCredits.hpp"

engine::SceneCredits::SceneCredits()
{
	addInGraphElem(BACKGROUND, render::MenuElementCreator::createImage(0, Scale::scaleRes(0, 0, 1920, 1080),\
	L"Default Text", "res/sprite/img/background_credits.jpg", false));
	addInGraphElem(RETURN, render::MenuElementCreator::createButton(0,\
	Scale::scaleRes(50, 900, 360, 1000), Language::getInstance()->getTranslate(Language::RETURN_MENU)));
	addInGraphElem(JUSTIN_IMAGE, render::MenuElementCreator::createImage(0, Scale::scaleRes(335, 175, 585, 425),\
	L"Default Text", "res/sprite/icon/credits_justin.png", true));
	addInGraphElem(JUSTIN_TEXT, render::MenuElementCreator::createText(0, Scale::scaleRes(350, 450, 600, 500), L"Jardiparapluie", false));
	addInGraphElem(MELVYN_IMAGE, render::MenuElementCreator::createImage(0, Scale::scaleRes(820, 215, 1070, 465),\
	L"Default Text", "res/sprite/icon/credits_melvyn.png", true));
	addInGraphElem(MELVYN_TEXT, render::MenuElementCreator::createText(0, Scale::scaleRes(900, 450, 1100, 500), L"Khalyn", false));
	addInGraphElem(NICOLAS_IMAGE, render::MenuElementCreator::createImage(0, Scale::scaleRes(1335, 215, 1585, 465),\
	L"Default Text", "res/sprite/icon/credits_nicolas.png", true));
	addInGraphElem(NICOLAS_TEXT, render::MenuElementCreator::createText(0, Scale::scaleRes(1365, 450, 1615, 500), L"Hitmastaz", false));
	addInGraphElem(SIMON_IMAGE, render::MenuElementCreator::createImage(0, Scale::scaleRes(560, 550, 810, 800),\
	L"Default Text", "res/sprite/icon/credits_simon.png", true));
	addInGraphElem(SIMON_TEXT, render::MenuElementCreator::createText(0, Scale::scaleRes(630, 825, 880, 875), L"Simon", false));
	addInGraphElem(GRAVILLON_IMAGE, render::MenuElementCreator::createImage(0, Scale::scaleRes(1110, 570, 1360, 820),\
	L"Default Text", "res/sprite/icon/credits_gravillon.png", true));
	addInGraphElem(GRAVILLON_TEXT, render::MenuElementCreator::createText(0, Scale::scaleRes(1175, 825, 1325, 875), L"Gravillon", false)); 
	_menuDisplay = new render::MenuDisplay(_graphElem);
}

void engine::SceneCredits::analyseEvent(std::pair<int, render::eventData> &event,
	engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	(void)lastScene;
	(void)loadGame;
	switch (event.first) {
	case RETURN:
		Music::getInstance()->play(Music::MENU, true);
		index = IGuiScene::SCENE_MAIN_MENU;
		break;
	default: break;
	}
}
