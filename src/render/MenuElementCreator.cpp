/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by moi,
*/

#include "render/MenuElement.hpp"
#include "render/MenuElementCreator.hpp"

render::MenuElement render::MenuElementCreator::createButton(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos, const std::wstring &text)
{
	render::MenuElement element;

	element.type = ElementType::Button;
	element.idParent = parentID;
	element.position = pos;
	element.text = text;
	element.v_text = std::vector<std::wstring>();
	element.path = "";
	element.check = false;
	element.color = { 0, 0, 0, 0 };
	element.range = irr::core::vector2di();
	element.step = 0;
	return element;
}

render::MenuElement render::MenuElementCreator::createCheckBox(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos, const std::wstring &text, bool checked)
{
	render::MenuElement element;

	element.type = ElementType::CheckBox;
	element.idParent = parentID;
	element.position = pos;
	element.text = text;
	element.v_text = std::vector<std::wstring>();
	element.path = "";
	element.check = checked;
	element.color = { 0, 0, 0, 0 };
	element.range = irr::core::vector2di();
	element.step = 0;
	return element;
}

render::MenuElement render::MenuElementCreator::createComboBox(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos, const std::vector<std::wstring> &choices)
{
	render::MenuElement element;

	element.type = ElementType::ComboBox;
	element.idParent = parentID;
	element.position = pos;
	element.text = std::wstring();
	element.v_text = choices;
	element.path = "";
	element.check = false;
	element.color = { 0, 0, 0, 0 };
	element.range = irr::core::vector2di();
	element.step = 0;
	return element;
}

render::MenuElement render::MenuElementCreator::createEditBox(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos, const std::wstring &text, bool border)
{
	render::MenuElement element;

	element.type = ElementType::EditBox;
	element.idParent = parentID;
	element.position = pos;
	element.text = text;
	element.v_text = std::vector<std::wstring>();
	element.path = "";
	element.check = border;
	element.color = { 0, 0, 0, 0 };
	element.range = irr::core::vector2di();
	element.step = 0;
	return element;
}

render::MenuElement render::MenuElementCreator::createImage(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos, const std::wstring &text, const std::string &path, bool transparency)
{
	render::MenuElement element;

	element.type = ElementType::Image;
	element.idParent = parentID;
	element.position = pos;
	element.text = text;
	element.v_text = std::vector<std::wstring>();
	element.path = path;
	element.check = transparency;
	element.color = { 0, 0, 0, 0 };
	element.range = irr::core::vector2di();
	element.step = 0;
	return element;
}

render::MenuElement render::MenuElementCreator::createFader(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos, const irr::video::SColor &color)
{
	render::MenuElement element;

	element.type = ElementType::InOutFader;
	element.idParent = parentID;
	element.position = pos;
	element.text = std::wstring();
	element.v_text = std::vector<std::wstring>();
	element.path = "";
	element.check = false;
	element.color = color;
	element.range = irr::core::vector2di();
	element.step = 0;
	return element;
}

render::MenuElement render::MenuElementCreator::createListBox(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos, const std::vector<std::wstring> &choices, bool drawBackground)
{
	render::MenuElement element;

	element.type = ElementType::ListBox;
	element.idParent = parentID;
	element.position = pos;
	element.text = std::wstring();
	element.v_text = choices;
	element.path = "";
	element.check = drawBackground;
	element.color = { 0, 0, 0, 0 };
	element.range = irr::core::vector2di();
	element.step = 0;
	return element;
}

render::MenuElement render::MenuElementCreator::createScrollBar(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos, bool horizontal, const irr::core::vector2di &range, int step)
{
	render::MenuElement element;

	element.type = ElementType::ScrollBar;
	element.idParent = parentID;
	element.position = pos;
	element.text = std::wstring();
	element.v_text = std::vector<std::wstring>();
	element.path = "";
	element.check = horizontal;
	element.color = { 0, 0, 0, 0 };
	element.range = range;
	element.step = step;
	return element;
}

render::MenuElement render::MenuElementCreator::createText(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos, const std::wstring &text, bool border, const irr::video::SColor &color)
{
	render::MenuElement element;

	element.type = ElementType::Text;
	element.idParent = parentID;
	element.position = pos;
	element.text = text;
	element.v_text = std::vector<std::wstring>();
	element.path = "";
	element.check = border;
	element.color = color;
	element.range = irr::core::vector2di();
	element.step = 0;
	return element;
}

render::MenuElement render::MenuElementCreator::createTab(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos, const std::wstring &text)
{
	render::MenuElement element;

	element.type = ElementType::Tab;
	element.idParent = parentID;
	element.position = pos;
	element.text = text;
	element.v_text = std::vector<std::wstring>();
	element.path = "";
	element.check = false;
	element.color = { 0, 0, 0, 0 };
	element.range = irr::core::vector2di();
	element.step = 0;
	return element;
}

render::MenuElement render::MenuElementCreator::createTabControl(unsigned int parentID,
	const irr::core::rect<irr::s32> &pos)
{
	render::MenuElement element;

	element.type = ElementType::TabControl;
	element.idParent = parentID;
	element.position = pos;
	element.text = L"";
	element.v_text = std::vector<std::wstring>();
	element.path = "";
	element.check = true;
	element.color = { 0, 0, 0, 0 };
	element.range = irr::core::vector2di();
	element.step = 0;
	return element;
}