/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Stromus,
*/

#include <algorithm>
#include <sound/Noise.hpp>
#include "render/MenuElement.hpp"
#include "settings/Settings.hpp"

render::MenuDisplay::MenuDisplay(std::map<int, MenuElement>& element)
{
	Irrlicht *singleton = Irrlicht::getInstance();
	irr::gui::IGUIEnvironment *guiE = singleton->getGUIEnv();
	auto dim = Settings::getInstance()->getResolution();
	int startTabOrder = -1;

	_root = guiE->addTab(irr::core::rect<irr::s32>(0, 0, dim.x, dim.y));
	_root->setVisible(false);
	for (auto pair : element) {
		auto &elem = pair.second;
		irr::gui::IGUIElement *guiElement;
		irr::gui::IGUIElement *parent = (elem.idParent == 0 ? _root : _elements.find(elem.idParent)->second);
		switch (elem.type) {
		case Button:
			guiElement = guiE->addButton(elem.position, parent, -1, elem.text.c_str());
			static_cast<irr::gui::IGUIButton *>(guiElement)->setImage(singleton->getVideo()->getTexture("res/sprite/icon/background_button.png"));
			break;
		case CheckBox:
			guiElement = guiE->addCheckBox(elem.check, elem.position, parent, -1, elem.text.c_str());
			break;
		case ComboBox:
			guiElement = guiE->addComboBox(elem.position, parent, -1);
			for (auto str : elem.v_text) {
				static_cast<irr::gui::IGUIComboBox *>(guiElement)->addItem(str.c_str());
			}
			guiElement->setEnabled(false);
			break;
		case EditBox:
			guiElement = guiE->addEditBox(elem.text.c_str(), elem.position, elem.check, parent, -1);
			guiElement->setEnabled(false);
			break;
		case Image:
			guiElement = guiE->addImage(elem.position, parent, -1, elem.text.c_str(), elem.check);
			static_cast<irr::gui::IGUIImage *>(guiElement)->setScaleImage(true);
			static_cast<irr::gui::IGUIImage *>(guiElement)->setImage(singleton->getVideo()->getTexture(elem.path.c_str()));
			break;
		case InOutFader:
			guiElement = guiE->addInOutFader(&elem.position, parent, -1);
			static_cast<irr::gui::IGUIInOutFader *>(guiElement)->setColor(elem.color);
			static_cast<irr::gui::IGUIInOutFader *>(guiElement)->fadeIn(5000);
			break;
		case ListBox:
			guiElement = guiE->addListBox(elem.position, parent, -1, elem.check);
			for (auto str : elem.v_text) {
				static_cast<irr::gui::IGUIListBox *>(guiElement)->addItem(str.c_str());
			}
			static_cast<irr::gui::IGUIListBox *>(guiElement)->setSelected(0);
			guiElement->setEnabled(false);
			break;
		case ScrollBar:
			guiElement = guiE->addScrollBar(elem.check, elem.position, parent, -1);
			static_cast<irr::gui::IGUIScrollBar *>(guiElement)->setMin(elem.range.X);
			static_cast<irr::gui::IGUIScrollBar *>(guiElement)->setMax(elem.range.Y);
			static_cast<irr::gui::IGUIScrollBar *>(guiElement)->setSmallStep(elem.step);
			break;
		case Text:
			guiElement = guiE->addStaticText(elem.text.c_str(), elem.position, elem.check, true, parent, -1);
			static_cast<irr::gui::IGUIStaticText *>(guiElement)->setOverrideColor(elem.color);
			break;
		case Tab:
			if (parent->getType() == irr::gui::EGUIET_TAB_CONTROL) {
				guiElement = static_cast<irr::gui::IGUITabControl *>(parent)->addTab(elem.text.c_str());
				static_cast<irr::gui::IGUITabControl *>(parent)->setActiveTab(static_cast<irr::gui::IGUITab *>(guiElement));
			} else
				guiElement = guiE->addTab(elem.position, parent, -1);
			break;
		case TabControl:
			guiElement = guiE->addTabControl(elem.position, parent, elem.check, true, -1);
			break;
		}
		if (startTabOrder == -1 && (elem.type == Button || elem.type == CheckBox || elem.type == ComboBox || elem.type == EditBox || elem.type == ListBox || elem.type == ScrollBar))
			startTabOrder = guiElement->getTabOrder();
		if (parent->getType() == irr::gui::EGUIET_TAB_CONTROL && guiElement->getType() != irr::gui::EGUIET_TAB && guiElement->getTabOrder() < startTabOrder + 20)
			guiElement->setTabOrder(startTabOrder + 20);
		_elements.insert(std::pair<irr::s32, irr::gui::IGUIElement*>(pair.first, guiElement));
	}
	for (auto it = _elements.begin(); it != _elements.end(); it++) {
		if (it->second->getType() == irr::gui::EGUIET_TAB_CONTROL)
			static_cast<irr::gui::IGUITabControl *>(it->second)->setActiveTab(0);
	}
	_select = guiE->addImage(irr::core::rect<irr::s32>(0, 0, dim.x, dim.y), _root, -1, L"", true);
	_select->setScaleImage(true);
	_select->setImage(singleton->getVideo()->getTexture("res/sprite/icon/test_selection.png"));
	_select->setVisible(false);
	_selected = nullptr;
}

void render::MenuDisplay::displayMenu()
{
	irr::gui::IGUIElement *closestElement = nullptr;

	_root->setVisible(true);
	_root->getNextElement(-1, false, false, _root, closestElement);
	Irrlicht::getInstance()->getGUIEnv()->setFocus(closestElement);
	if (closestElement != nullptr)
		moveSelection(closestElement);
}

void render::MenuDisplay::hideMenu()
{
	_root->setVisible(false);
	eraseEvent();
}

void render::MenuDisplay::updateEvents()
{
	auto guiEnv = Irrlicht::getInstance()->getGUIEnv();
	irr::gui::IGUIElement *focus = guiEnv->getFocus();

	auto it = std::find_if(_elements.begin(), _elements.end(), [focus](auto e) -> bool {
		return e.second == focus;
	});
	if (it == _elements.end())
		return;
	render::eventData data = { 0, false, L"", Controls::ERROR };
	switch (it->second->getType()) {
	case irr::gui::EGUIET_CHECK_BOX:
		data.checked = static_cast<irr::gui::IGUICheckBox *>(it->second)->isChecked();
		addEvent(it->first, data);
		break;
	case irr::gui::EGUIET_COMBO_BOX:
		data.string = static_cast<irr::gui::IGUIComboBox *>(it->second)->getItem(static_cast<irr::gui::IGUIComboBox *>(it->second)->getSelected());
		addEvent(it->first, data);
		break;
	case irr::gui::EGUIET_EDIT_BOX:
		data.string = static_cast<irr::gui::IGUIEditBox *>(it->second)->getText();
		data.key = Controls::getInstance()->getNextKey();
		addEvent(it->first, data);
		break;
	case irr::gui::EGUIET_LIST_BOX:
		data.string = static_cast<irr::gui::IGUIListBox *>(it->second)->getListItem(static_cast<irr::gui::IGUIListBox *>(it->second)->getSelected());
		addEvent(it->first, data);
		break;
	case irr::gui::EGUIET_SCROLL_BAR:
		data.position = static_cast<irr::gui::IGUIScrollBar *>(it->second)->getPos();
		addEvent(it->first, data);
		break;
	default:
		addEvent(it->first, data);
		Noise::getInstance()->play(Noise::MENU_ENTER);
		break;
	}
}

void render::MenuDisplay::eraseEvent()
{
	while (!_events.empty())
		_events.pop();
}

void render::MenuDisplay::addEvent(int id, render::eventData data)
{
	_events.push(std::pair<int, render::eventData>(id, data));
}

std::pair<int, render::eventData> render::MenuDisplay::getNextEvent()
{
	if (_events.empty())
		return std::pair<int, render::eventData>(-1, {0, false, L""});
	std::pair<int, render::eventData> tmp = _events.front();
	_events.pop();
	return tmp;
}

void render::MenuDisplay::updateMenu()
{
	bool reverse = false;
	Irrlicht *singelton = Irrlicht::getInstance();
	irr::gui::IGUIElement *closestElement = nullptr;
	irr::gui::IGUIElement *parent = _root;
	irr::gui::IGUIElement *firstElement = singelton->getGUIEnv()->getFocus();
	Controls *ctrl = Controls::getInstance();
	int tab = -1;

	while (!ctrl->isEmpty()) {
		auto key = ctrl->getNextKey();
		if (_selected != nullptr && _selected->isEnabled()) {
			switch (_selected->getType()) {
			case irr::gui::EGUIET_EDIT_BOX:
				updateEditBox(static_cast<irr::gui::IGUIEditBox *>(_selected), key);
				ctrl->eraseNextKey();
				continue;
			case irr::gui::EGUIET_COMBO_BOX:
				updateComboBox(static_cast<irr::gui::IGUIComboBox *>(_selected), key);
				ctrl->eraseNextKey();
				continue;
			case irr::gui::EGUIET_LIST_BOX:
				updateListBox(static_cast<irr::gui::IGUIListBox *>(_selected), key);
				ctrl->eraseNextKey();
				continue;
			}
		}
		switch (Settings::getInstance()->getAction(key, 1)) {
		case Controls::MOVE_UP:
			reverse = true;
			Noise::getInstance()->play(Noise::noiseID::MENU_SELECTION);
		case Controls::MOVE_DOWN:
 			if (firstElement != nullptr) {
				tab = firstElement->getTabOrder();
				parent = firstElement->getParent();
				firstElement = parent;
				if (parent->getType() == irr::gui::EGUIET_TAB_CONTROL) {
					irr::gui::IGUITabControl *tab_control = static_cast<irr::gui::IGUITabControl *>(parent);
					parent = tab_control->getTab(tab_control->getActiveTab());
				}
			}
			Noise::getInstance()->play(Noise::noiseID::MENU_SELECTION);
			updateFocus(parent, reverse, tab);
			break;
		case Controls::actions::BOMB:
			if (_selected != nullptr && _selected->getType() == irr::gui::EGUIET_CHECK_BOX)
				static_cast<irr::gui::IGUICheckBox *>(_selected)->setChecked(!static_cast<irr::gui::IGUICheckBox *>(_selected)->isChecked());
			else if (_selected != nullptr && (_selected->getType() == irr::gui::EGUIET_EDIT_BOX || \
											  _selected->getType() == irr::gui::EGUIET_COMBO_BOX || \
											  _selected->getType() == irr::gui::EGUIET_LIST_BOX)) {
				_selected->setEnabled(true);
				if (_selected->getType() == irr::gui::EGUIET_EDIT_BOX) {
					Irrlicht::getInstance()->setDispatchKey(true);
					ctrl->eraseNextKey();
					continue;
				}
			}
			updateEvents();
		default:
			if (_selected != nullptr && _selected->getType() == irr::gui::EGUIET_SCROLL_BAR)
				updateScrollBar(static_cast<irr::gui::IGUIScrollBar *>(_selected), key);
			break;
		}
		ctrl->eraseNextKey();
	}
}

void render::MenuDisplay::updateFocus(irr::gui::IGUIElement *parent, bool reverse, int tab)
{
	Irrlicht *singelton = Irrlicht::getInstance();
	irr::gui::IGUIElement *closestElement = nullptr;
	irr::gui::IGUIElement *firstElement = parent;

	if (parent == nullptr) //
		return; //
	if (parent->getNextElement(tab, reverse, false, firstElement, closestElement)) {
		singelton->getGUIEnv()->setFocus(closestElement);
		moveSelection(closestElement);
	} else if (closestElement != nullptr) {
		singelton->getGUIEnv()->setFocus(closestElement);
		moveSelection(closestElement);
	} else {
		if (parent != _root) {
			parent = parent->getParent();
			updateFocus(parent, reverse, tab);
		}
		else if (firstElement != parent) {
			singelton->getGUIEnv()->setFocus(firstElement);
			moveSelection(firstElement);
		} else {
			parent->getNextElement(-1, false, false, parent, closestElement);
			singelton->getGUIEnv()->setFocus(closestElement);
			if (closestElement != nullptr)
				moveSelection(closestElement);
		}
	}
}

void render::MenuDisplay::moveSelection(irr::gui::IGUIElement *focus)
{
	_selected = focus;
	auto pos = focus->getRelativePosition();
	if (pos.UpperLeftCorner.X - pos.getHeight() > 0)
		_select->setRelativePosition(irr::core::rect<irr::s32>(pos.UpperLeftCorner.X - pos.getHeight() - 10, pos.UpperLeftCorner.Y, pos.UpperLeftCorner.X - 10, pos.LowerRightCorner.Y));
	else
		_select->setRelativePosition(irr::core::rect<irr::s32>(pos.LowerRightCorner.X + 10, pos.UpperLeftCorner.Y, pos.LowerRightCorner.X + pos.getHeight() + 10, pos.LowerRightCorner.Y));
	focus->getParent()->addChild(_select);
	_select->setVisible(true);
}

void render::MenuDisplay::updateScrollBar(irr::gui::IGUIScrollBar * selected, Controls::keyIS key)
{
	int pos = selected->getPos();
	switch (Settings::getInstance()->getAction(key, 1)) {
	case Controls::MOVE_LEFT:
		selected->setPos(pos - selected->getSmallStep());
		break;
	case Controls::MOVE_RIGHT:
		selected->setPos(pos + selected->getSmallStep());
		break;
	}
	updateEvents();
}

void render::MenuDisplay::updateEditBox(irr::gui::IGUIEditBox * selected, Controls::keyIS key)
{
	if (key == Controls::KEY_ESC) {
		Irrlicht::getInstance()->setDispatchKey(false);
		_selected->setEnabled(false);
	}
	else
		updateEvents();
}

void render::MenuDisplay::updateComboBox(irr::gui::IGUIComboBox * selected, Controls::keyIS key)
{
	if (key == Controls::KEY_SPACE) {
		_selected->setEnabled(false);
		return;
	}
	irr::s32 item = selected->getSelected();
	switch (Settings::getInstance()->getAction(key, 1)) {
	case Controls::MOVE_UP:
		if (item - 1 < 0)
			selected->setSelected(selected->getItemCount() - 1);
		else
			selected->setSelected(item - 1);
		break;
	case Controls::MOVE_DOWN:
		if (item + 1 >= static_cast<irr::s32>(selected->getItemCount()))
			selected->setSelected(0);
		else
			selected->setSelected(item + 1);
		break;
	}
	updateEvents();
}

void render::MenuDisplay::updateListBox(irr::gui::IGUIListBox * selected, Controls::keyIS key)
{
	if (key == Controls::KEY_SPACE) {
		_selected->setEnabled(false);
		return;
	}
	irr::s32 item = selected->getSelected();
	switch (Settings::getInstance()->getAction(key, 1)) {
	case Controls::MOVE_UP:
		if (item - 1 < 0)
			selected->setSelected(selected->getItemCount() - 1);
		else
			selected->setSelected(item - 1);
		break;
	case Controls::MOVE_DOWN:
		if (item + 1 >= static_cast<irr::s32>(selected->getItemCount()))
			selected->setSelected(0);
		else
			selected->setSelected(item + 1);
		break;
	}
	updateEvents();
}

void render::MenuDisplay::removeMenu()
{
	_root->remove();
	_elements.clear();
}

void render::MenuDisplay::setValueCheckBox(int id, bool value)
{
	irr::gui::IGUICheckBox *element = static_cast<irr::gui::IGUICheckBox *>(_elements[id]);

	element->setChecked(value);
}

void render::MenuDisplay::setValueComboBox(int id, std::wstring value)
{
	irr::gui::IGUIComboBox *element = static_cast<irr::gui::IGUIComboBox *>(_elements[id]);

	unsigned int i = 0;
	while (i < element->getItemCount() && std::wcscmp(element->getItem(i), value.c_str()))
		i++;
	if (i == element->getItemCount())
		return;
	element->setSelected(i);
}

void render::MenuDisplay::setValueEditBox(int id, std::wstring value)
{
	irr::gui::IGUIEditBox *element = static_cast<irr::gui::IGUIEditBox *>(_elements[id]);

	element->setText(value.c_str());
}

void render::MenuDisplay::setValueListBox(int id, std::wstring value)
{
	irr::gui::IGUIListBox *element = static_cast<irr::gui::IGUIListBox *>(_elements[id]);

	unsigned int i = 0;
	while (i < element->getItemCount() && std::wcscmp(element->getListItem(i), value.c_str()))
		i++;
	if (i == element->getItemCount())
		return;
	element->setSelected(i);
}

void render::MenuDisplay::setValueScrollBar(int id, int value)
{
	irr::gui::IGUIScrollBar *element = static_cast<irr::gui::IGUIScrollBar *>(_elements[id]);

	element->setPos(value);
}

void render::MenuDisplay::setValueText(int id, std::wstring value)
{
	irr::gui::IGUIStaticText *element = static_cast<irr::gui::IGUIStaticText *>(_elements[id]);

	element->setText(value.c_str());
}

void render::MenuDisplay::remove(int id)
{
	irr::gui::IGUIElement *element = _elements[id];

	updateFocus(element->getParent(), false, element->getTabOrder());
	element->remove();
	_elements.erase(id);
}

void render::MenuDisplay::switchNextTab(int id)
{
	irr::gui::IGUITabControl *element = static_cast<irr::gui::IGUITabControl *>(_elements[id]);
	int active = element->getActiveTab();

	if (active + 1 >= element->getTabCount())
		element->setActiveTab(0);
	else
		element->setActiveTab(active + 1);
}

void render::MenuDisplay::switchPrevTab(int id)
{
	irr::gui::IGUITabControl *element = static_cast<irr::gui::IGUITabControl *>(_elements[id]);
	int active = element->getActiveTab();

	if (active - 1 < 0)
		element->setActiveTab(element->getTabCount() - 1);
	else
		element->setActiveTab(active - 1);
}

void render::MenuDisplay::setColorTextEditBox(int id, irr::video::SColor color)
{
	irr::gui::IGUIEditBox *element = static_cast<irr::gui::IGUIEditBox *>(_elements[id]);

	element->enableOverrideColor(true);
	element->setOverrideColor(color);
}
