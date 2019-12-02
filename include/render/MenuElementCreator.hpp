/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by peut-etre moi,
*/

#include "MenuElement.hpp"

namespace render {

	class MenuElementCreator {
	public:
		MenuElementCreator() = default;
		~MenuElementCreator() = default;

		static MenuElement createButton(unsigned int parentID, const irr::core::rect<irr::s32> &pos,
			const std::wstring &text);
		static MenuElement createCheckBox(unsigned int parentID, const irr::core::rect<irr::s32> &pos,
			const std::wstring &text, bool checked);
		static MenuElement createComboBox(unsigned int parentID, const irr::core::rect<irr::s32> &pos,
			const std::vector<std::wstring> &choices);
		static MenuElement createEditBox(unsigned int parentID, const irr::core::rect<irr::s32> &pos,
			const std::wstring &text, bool border);
		static MenuElement createImage(unsigned int parentID, const irr::core::rect<irr::s32> &pos,
			const std::wstring &text, const std::string &path, bool transparency);
		static MenuElement createFader(unsigned int parentID, const irr::core::rect<irr::s32> &pos,
			const irr::video::SColor &color);
		static MenuElement createListBox(unsigned int parentID, const irr::core::rect<irr::s32> &pos,
			const std::vector<std::wstring> &choices, bool drawBackground);
		static MenuElement createScrollBar(unsigned int parentID, const irr::core::rect<irr::s32> &pos,
			bool horizontal, const irr::core::vector2di &range, int step);
		static MenuElement createText(unsigned int parentID, const irr::core::rect<irr::s32> &pos,
			const std::wstring &text, bool border, const irr::video::SColor &color = {255, 0, 0, 0});
		static MenuElement createTab(unsigned int parentID, const irr::core::rect<irr::s32> &pos,
			const std::wstring &text);
		static MenuElement createTabControl(unsigned int parentID, const irr::core::rect<irr::s32> &pos);
	};

}