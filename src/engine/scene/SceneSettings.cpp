/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <algorithm>
#include "settings/Settings.hpp"
#include "settings/Language.hpp"
#include "engine/scene/SceneSettings.hpp"
#include "settings/Scale.hpp"
#include "settings/Controls.hpp"
#include "exception/SettingsException.hpp"

engine::SceneSettings::SceneSettings()
{
	Settings *settings = Settings::getInstance();

	this->_controls.first.push_back(settings->getKeyByAction(Controls::actions::MOVE_UP, 1));
	this->_controls.first.push_back(settings->getKeyByAction(Controls::actions::MOVE_DOWN, 1));
	this->_controls.first.push_back(settings->getKeyByAction(Controls::actions::MOVE_LEFT, 1));
	this->_controls.first.push_back(settings->getKeyByAction(Controls::actions::MOVE_RIGHT, 1));
	this->_controls.first.push_back(settings->getKeyByAction(Controls::actions::BOMB, 1));

	this->_controls.second.push_back(settings->getKeyByAction(Controls::actions::MOVE_UP, 2));
	this->_controls.second.push_back(settings->getKeyByAction(Controls::actions::MOVE_DOWN, 2));
	this->_controls.second.push_back(settings->getKeyByAction(Controls::actions::MOVE_LEFT, 2));
	this->_controls.second.push_back(settings->getKeyByAction(Controls::actions::MOVE_RIGHT, 2));
	this->_controls.second.push_back(settings->getKeyByAction(Controls::actions::BOMB, 2));

	addInGraphElem(BACKGROUND, render::MenuElementCreator::createImage(0, Scale::scaleRes(0, 0, 1920, 1080),\
	L"Default Text", "res/sprite/img/background_settings.jpg", false));

	addInGraphElem(TITLE, render::MenuElementCreator::createText(0, Scale::scaleRes(850, 40, 1200, 900),
		Language::getInstance()->getTranslate(Language::SETTINGS), false));
	addInGraphElem(TAB_CONTROL, render::MenuElementCreator::createTabControl(0, Scale::scaleRes(50, 50, 1870, 850)));
	createMainTab();
	createControlsTab();
	createLanguageTab();
	addInGraphElem(RETURN, render::MenuElementCreator::createButton(0,\
		Scale::scaleRes(50, 900, 360, 1000), Language::getInstance()->getTranslate(Language::RETURN_MENU)));
	addInGraphElem(PREV_TAB, render::MenuElementCreator::createButton(TAB_CONTROL, Scale::scaleRes(50, 675, 375, 775),\
	Language::getInstance()->getTranslate(Language::PREVIOUS_TAB)));
	addInGraphElem(NEXT_TAB, render::MenuElementCreator::createButton(TAB_CONTROL, Scale::scaleRes(1450, 675, 1775, 775),\
	Language::getInstance()->getTranslate(Language::NEXT_TAB)));

	_menuDisplay = new render::MenuDisplay(_graphElem);
	_menuDisplay->setValueScrollBar(SCROLL_FPS, Settings::getInstance()->getNumberFPS());
	_menuDisplay->setValueScrollBar(SCROLL_SOUND, Settings::getInstance()->getSoundVolume());
	_menuDisplay->setValueScrollBar(SCROLL_MUSIC, Settings::getInstance()->getMusicVolume());
	auto tmp = Settings::getInstance()->getResolution();
	_menuDisplay->setValueComboBox(RESOLUTION, std::to_wstring(tmp.x) + L"x" + std::to_wstring(tmp.y));

	/* set TextColor */
	this->_menuDisplay->setColorTextEditBox(MOVE_UP_1, irr::video::SColor(255, 0, 0, 0));
	this->_menuDisplay->setColorTextEditBox(MOVE_DOWN_1, irr::video::SColor(255, 0, 0, 0));
	this->_menuDisplay->setColorTextEditBox(MOVE_LEFT_1, irr::video::SColor(255, 0, 0, 0));
	this->_menuDisplay->setColorTextEditBox(MOVE_RIGHT_1, irr::video::SColor(255, 0, 0, 0));
	this->_menuDisplay->setColorTextEditBox(BOMB_CTRL_1, irr::video::SColor(255, 0, 0, 0));
	this->_menuDisplay->setColorTextEditBox(MOVE_UP_2, irr::video::SColor(255, 0, 0, 0));
	this->_menuDisplay->setColorTextEditBox(MOVE_DOWN_2, irr::video::SColor(255, 0, 0, 0));
	this->_menuDisplay->setColorTextEditBox(MOVE_LEFT_2, irr::video::SColor(255, 0, 0, 0));
	this->_menuDisplay->setColorTextEditBox(MOVE_RIGHT_2, irr::video::SColor(255, 0, 0, 0));
	this->_menuDisplay->setColorTextEditBox(BOMB_CTRL_2, irr::video::SColor(255, 0, 0, 0));
}

void engine::SceneSettings::createMainTab()
{
	addInGraphElem(MAIN_TAB, render::MenuElementCreator::createTab(TAB_CONTROL, Scale::scaleRes(50, 50, 1870, 850),\
	Language::getInstance()->getTranslate(Language::GENERAL)));
	addInGraphElem(SCROLL_FPS, render::MenuElementCreator::createScrollBar(MAIN_TAB, Scale::scaleRes(475, 125, 1075, 175), true, {30, 300}, 5));
	addInGraphElem(FPS_WORD, render::MenuElementCreator::createText(MAIN_TAB, Scale::scaleRes(150, 120, 500, 200),\
	Language::getInstance()->getTranslate(Language::FRAMERATE), false));
	addInGraphElem(FPS_VALUE, render::MenuElementCreator::createText(MAIN_TAB, Scale::scaleRes(1100, 125, 1250, 200),\
	std::to_wstring(Settings::getInstance()->getNumberFPS()), false));

	addInGraphElem(SCROLL_SOUND, render::MenuElementCreator::createScrollBar(MAIN_TAB, Scale::scaleRes(475, 225, 1075, 275), true, {0, 100}, 2));
	addInGraphElem(SOUND_WORD, render::MenuElementCreator::createText(MAIN_TAB, Scale::scaleRes(150, 220, 450, 300),\
	Language::getInstance()->getTranslate(Language::SOUND_VOLUME), false));
	addInGraphElem(SOUND_VALUE, render::MenuElementCreator::createText(MAIN_TAB, Scale::scaleRes(1100, 225, 1250, 300),\
	std::to_wstring(Settings::getInstance()->getSoundVolume()), false));

	addInGraphElem(SCROLL_MUSIC, render::MenuElementCreator::createScrollBar(MAIN_TAB, Scale::scaleRes(475, 325, 1075, 375), true, {0, 100}, 2));
	addInGraphElem(MUSIC_WORD, render::MenuElementCreator::createText(MAIN_TAB, Scale::scaleRes(150, 320, 450, 400),\
	Language::getInstance()->getTranslate(Language::MUSIC_VOLUME), false));
	addInGraphElem(MUSIC_VALUE, render::MenuElementCreator::createText(MAIN_TAB, Scale::scaleRes(1100, 325, 1250, 400),\
	std::to_wstring(Settings::getInstance()->getMusicVolume()), false));

	addInGraphElem(RESOLUTION_TXT, render::MenuElementCreator::createText(MAIN_TAB, Scale::scaleRes(150, 425, 1500, 500),\
	Language::getInstance()->getTranslate(Language::RESOLUTION_PATCH), false));
	addInGraphElem(RESOLUTION, render::MenuElementCreator::createComboBox(MAIN_TAB, Scale::scaleRes(150, 500, 500, 550), {L"1920x1080", L"1280x720"}));
	addInGraphElem(FULLSCREEN, render::MenuElementCreator::createCheckBox(MAIN_TAB, Scale::scaleRes(150, 565, 700, 625),\
	Language::getInstance()->getTranslate(Language::ACTIVATE_FULLSCREEN),\
		Settings::getInstance()->isFullScreen()));
}

void engine::SceneSettings::createLanguageTab()
{
	Language *languageInstance = Language::getInstance();
	addInGraphElem(LANGUAGE_TAB, render::MenuElementCreator::createTab(TAB_CONTROL,\
	Scale::scaleRes(50, 50, 1870, 850), Language::getInstance()->getTranslate(Language::LANGUAGE)));

	int xBegin = 975;
	int xEnd = 1175;
	int yBegin = 250;
	int yEnd = 350;
	int i = 1;

	Language::languageCode code;
	std::wstring wlanguageName;
	std::string languageName;

	for (auto &language : languageInstance->getLanguagesList()) {
		code = language.code;
		languageName = languageInstance->convertCodeToString(code);
		wlanguageName.assign(languageName.begin(), languageName.end());

		this->_idxLanguagesEvents.push_back(LANGUAGE_TAB + i);
		this->addInGraphElem(LANGUAGE_TAB + i++, render::MenuElementCreator::createButton(LANGUAGE_TAB,\
		Scale::scaleRes(xBegin, yBegin, xEnd, yEnd), wlanguageName));
		this->addInGraphElem(LANGUAGE_TAB + i++, render::MenuElementCreator::createImage(LANGUAGE_TAB,\
		Scale::scaleRes(xBegin - 350, yBegin, xEnd - 350, yEnd), L"", language.flag, false));
		yBegin += 150;
		yEnd += 150;
	}
}

void engine::SceneSettings::createControlsTab()
{
	Controls *controls = Controls::getInstance();

	addInGraphElem(CTRL_TAB, render::MenuElementCreator::createTab(TAB_CONTROL, Scale::scaleRes(50, 50, 1870, 850),\
	Language::getInstance()->getTranslate(Language::CONTROLS)));

	/* player 1 */
	addInGraphElem(PLAYER1_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(475, 50, 900, 600),
		Language::getInstance()->getTranslate(Language::PLAYER1), false));

	addInGraphElem(MOVE_UP_1, render::MenuElementCreator::createEditBox(CTRL_TAB, Scale::scaleRes(400, 125, 700, 200),
		controls->getKeyName(this->_controls.first[Controls::actions::MOVE_UP]), false));
	addInGraphElem(MOVE_DOWN_1, render::MenuElementCreator::createEditBox(CTRL_TAB, Scale::scaleRes(400, 225, 700, 300),
		controls->getKeyName(this->_controls.first[Controls::actions::MOVE_DOWN]), false));
	addInGraphElem(MOVE_LEFT_1, render::MenuElementCreator::createEditBox(CTRL_TAB, Scale::scaleRes(400, 325, 700, 400),
		controls->getKeyName(this->_controls.first[Controls::actions::MOVE_LEFT]), false));
	addInGraphElem(MOVE_RIGHT_1, render::MenuElementCreator::createEditBox(CTRL_TAB, Scale::scaleRes(400, 425, 700, 500),
		controls->getKeyName(this->_controls.first[Controls::actions::MOVE_RIGHT]), false));
	addInGraphElem(BOMB_CTRL_1, render::MenuElementCreator::createEditBox(CTRL_TAB, Scale::scaleRes(400, 525, 700, 600),
		controls->getKeyName(this->_controls.first[Controls::actions::BOMB]), false));
	
	addInGraphElem(MOVE_UP_1_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(240, 140, 550, 300),
		Language::getInstance()->getTranslate(Language::UP), false));
	addInGraphElem(MOVE_DOWN_1_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(240, 240, 550, 400),
		Language::getInstance()->getTranslate(Language::DOWN), false));
	addInGraphElem(MOVE_LEFT_1_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(240, 340, 550, 500),
		Language::getInstance()->getTranslate(Language::LEFT), false));
	addInGraphElem(MOVE_RIGHT_1_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(240, 440, 550, 600),
		Language::getInstance()->getTranslate(Language::RIGHT), false));
	addInGraphElem(BOMB_1_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(240, 540, 550, 700),
		Language::getInstance()->getTranslate(Language::BOMB), false));

	/* player 2 */
	addInGraphElem(PLAYER2_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(1275, 50, 1600, 600),
		Language::getInstance()->getTranslate(Language::PLAYER2), false));

	addInGraphElem(MOVE_UP_2, render::MenuElementCreator::createEditBox(CTRL_TAB, Scale::scaleRes(1200, 125, 1500, 200),
		controls->getKeyName(this->_controls.second[Controls::actions::MOVE_UP]), false));
	addInGraphElem(MOVE_DOWN_2, render::MenuElementCreator::createEditBox(CTRL_TAB, Scale::scaleRes(1200, 225, 1500, 300),
		controls->getKeyName(this->_controls.second[Controls::actions::MOVE_DOWN]), false));
	addInGraphElem(MOVE_LEFT_2, render::MenuElementCreator::createEditBox(CTRL_TAB, Scale::scaleRes(1200, 325, 1500, 400),
		controls->getKeyName(this->_controls.second[Controls::actions::MOVE_LEFT]), false));
	addInGraphElem(MOVE_RIGHT_2, render::MenuElementCreator::createEditBox(CTRL_TAB, Scale::scaleRes(1200, 425, 1500, 500),
		controls->getKeyName(this->_controls.second[Controls::actions::MOVE_RIGHT]), false));
	addInGraphElem(BOMB_CTRL_2, render::MenuElementCreator::createEditBox(CTRL_TAB, Scale::scaleRes(1200, 525, 1500, 600),
		controls->getKeyName(this->_controls.second[Controls::actions::BOMB]), false));

	addInGraphElem(MOVE_UP_2_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(1040, 140, 1550, 300),
		Language::getInstance()->getTranslate(Language::UP), false));
	addInGraphElem(MOVE_DOWN_2_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(1040, 240, 1550, 400),
		Language::getInstance()->getTranslate(Language::DOWN), false));
	addInGraphElem(MOVE_LEFT_2_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(1040, 340, 1550, 500),
		Language::getInstance()->getTranslate(Language::LEFT), false));
	addInGraphElem(MOVE_RIGHT_2_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(1040, 440, 1550, 600),
		Language::getInstance()->getTranslate(Language::RIGHT), false));
	addInGraphElem(BOMB_2_TXT, render::MenuElementCreator::createText(CTRL_TAB, Scale::scaleRes(1040, 540, 1550, 700),
		Language::getInstance()->getTranslate(Language::BOMB), false));

	/* save controls */
	addInGraphElem(SAVE_CONTROLS, render::MenuElementCreator::createButton(CTRL_TAB, Scale::scaleRes(750, 600, 1050, 700),
		Language::getInstance()->getTranslate(Language::SAVE_CONTROLS)));
}

void engine::SceneSettings::checkControlValidity()
{
	size_t count;
	int i = 0;

	for (auto &key : this->_controls.first) {
		count = 0;
		count += std::count(this->_controls.first.begin(), this->_controls.first.end(), key);
		count += std::count(this->_controls.second.begin(), this->_controls.second.end(), key);
		this->_menuDisplay->setColorTextEditBox(i + MOVE_UP_1, irr::video::SColor(255, 0, 0, 0));
		if (count != 1 || key == Controls::keyIS::ERROR) {
			this->_menuDisplay->setColorTextEditBox(i + MOVE_UP_1, irr::video::SColor(255, 255, 0, 0));
			this->_menuDisplay->setValueEditBox(i + MOVE_UP_1, Language::getInstance()->getTranslate(Language::ERROR));
			throw ise::SettingsException(ise::WARNING, "Key " + std::to_string(key) + " set twice or more, or is ERROR");
		}
		i += 1;
	}

	i = 0;
	for (auto &key : this->_controls.second) {
		count = 0;
		count += std::count(this->_controls.first.begin(), this->_controls.first.end(), key);
		count += std::count(this->_controls.second.begin(), this->_controls.second.end(), key);
		this->_menuDisplay->setColorTextEditBox(i + MOVE_UP_2, irr::video::SColor(255, 0, 0, 0));
		if (count != 1) {
			this->_menuDisplay->setColorTextEditBox(i + MOVE_UP_2, irr::video::SColor(255, 255, 0, 0));
			this->_menuDisplay->setValueEditBox(i + MOVE_UP_2, Language::getInstance()->getTranslate(Language::ERROR));
			throw ise::SettingsException(ise::WARNING, "Key " + std::to_string(key) + " set twice or more");
		}
		i += 1;
	}
}

void engine::SceneSettings::changeLanguage(std::pair<int, render::eventData> &event)
{
	Language *language = Language::getInstance();
	Settings *settings = Settings::getInstance();

	auto &languagesList = language->getLanguagesList();
	int nbLanguage = 0;
	for (auto &languageEvent : this->_idxLanguagesEvents) {
		if (event.first == languageEvent) {
			settings->setLanguage(languagesList[nbLanguage].code);
			language->setUpdated(true);
		}
		nbLanguage += 1;
	}
}

void engine::SceneSettings::changeControls(std::pair<int, render::eventData> &event)
{
	Controls *controls = Controls::getInstance();
	Settings *settings = Settings::getInstance();
	int i;

	switch (event.first) {
	case MOVE_UP_1:
		if (!event.second.string.empty()) {
			this->_controls.first[static_cast<int>(Controls::actions::MOVE_UP)] = event.second.key;
			this->_menuDisplay->setValueEditBox(MOVE_UP_1, controls->getKeyName(event.second.key));
		}
		break;
	case MOVE_DOWN_1:
		if (!event.second.string.empty()) {
			this->_controls.first[static_cast<int>(Controls::actions::MOVE_DOWN)] = event.second.key;
			this->_menuDisplay->setValueEditBox(MOVE_DOWN_1, controls->getKeyName(event.second.key));
		}
		break;
	case MOVE_LEFT_1:
		if (!event.second.string.empty()) {
			this->_controls.first[static_cast<int>(Controls::actions::MOVE_LEFT)] = event.second.key;
			this->_menuDisplay->setValueEditBox(MOVE_LEFT_1, controls->getKeyName(event.second.key));
		}
		break;
	case MOVE_RIGHT_1:
		if (!event.second.string.empty()) {
			this->_controls.first[static_cast<int>(Controls::actions::MOVE_RIGHT)] = event.second.key;
			this->_menuDisplay->setValueEditBox(MOVE_RIGHT_1, controls->getKeyName(event.second.key));
		}
		break;
	case BOMB_CTRL_1:
		if (!event.second.string.empty()) {
			this->_controls.first[static_cast<int>(Controls::actions::BOMB)] = event.second.key;
			this->_menuDisplay->setValueEditBox(BOMB_CTRL_1, controls->getKeyName(event.second.key));
		}
		break;

	case MOVE_UP_2:
		if (!event.second.string.empty()) {
			this->_controls.second[static_cast<int>(Controls::actions::MOVE_UP)] = event.second.key;
			this->_menuDisplay->setValueEditBox(MOVE_UP_2, controls->getKeyName(event.second.key));
		}
		break;
	case MOVE_DOWN_2:
		if (!event.second.string.empty()) {
			this->_controls.second[static_cast<int>(Controls::actions::MOVE_DOWN)] = event.second.key;
			this->_menuDisplay->setValueEditBox(MOVE_DOWN_2, controls->getKeyName(event.second.key));
		}
		break;
	case MOVE_LEFT_2:
		if (!event.second.string.empty()) {
			this->_controls.second[static_cast<int>(Controls::actions::MOVE_LEFT)] = event.second.key;
			this->_menuDisplay->setValueEditBox(MOVE_LEFT_2, controls->getKeyName(event.second.key));
		}
		break;
	case MOVE_RIGHT_2:
		if (!event.second.string.empty()) {
			this->_controls.second[static_cast<int>(Controls::actions::MOVE_RIGHT)] = event.second.key;
			this->_menuDisplay->setValueEditBox(MOVE_RIGHT_2, controls->getKeyName(event.second.key));
		}
		break;
	case BOMB_CTRL_2:
		if (!event.second.string.empty()) {
			this->_controls.second[static_cast<int>(Controls::actions::BOMB)] = event.second.key;
			this->_menuDisplay->setValueEditBox(BOMB_CTRL_2, controls->getKeyName(event.second.key));
		}
		break;
	case SAVE_CONTROLS:
		try {
			this->checkControlValidity();
		}
		catch (const ise::SettingsException &e) {
			std::cerr << e.what() << std::endl;
			return;
		}
		i = 0;
		for (auto &key : this->_controls.first) {
			settings->setAction(static_cast<Controls::actions>(i), key, 1);
			i += 1;
		}
		i = 0;
		for (auto &key : this->_controls.second) {
			settings->setAction(static_cast<Controls::actions>(i), key, 2);
			i += 1;
		}
		break;
	default:
		this->changeLanguage(event);
		break;
	}
}

void engine::SceneSettings::analyseEvent(std::pair<int, render::eventData> &event,
	engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	switch (event.first) {
	case SCROLL_FPS:
		Settings::getInstance()->setNumberFPS(event.second.position);
		_menuDisplay->setValueText(FPS_VALUE, std::to_wstring(Settings::getInstance()->getNumberFPS()));
		break;
	case SCROLL_SOUND:
		Settings::getInstance()->setSoundVolume(event.second.position);
		_menuDisplay->setValueText(SOUND_VALUE, std::to_wstring(Settings::getInstance()->getSoundVolume()));
		break;
	case SCROLL_MUSIC:
		Settings::getInstance()->setMusicVolume(event.second.position);
		_menuDisplay->setValueText(MUSIC_VALUE, std::to_wstring(Settings::getInstance()->getMusicVolume()));
		break;
	case RESOLUTION: {
		std::wstring result = event.second.string;
		Settings::getInstance()->setResolution(
			{static_cast<unsigned int>(std::stoi(result)),\
			static_cast<unsigned int>(std::stoi(result.substr(result.find('x') + 1)))});
		break;
	}
	case FULLSCREEN:
		Settings::getInstance()->setFullScreen(event.second.checked);
		break;
	case RETURN:
		index = lastScene;
		break;
	case PREV_TAB:
		_menuDisplay->switchPrevTab(TAB_CONTROL);
		break;
	case NEXT_TAB:
		_menuDisplay->switchNextTab(TAB_CONTROL);
		break;
	default:
		this->changeControls(event);
		break;
	}
}
