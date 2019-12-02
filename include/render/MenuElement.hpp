/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Stromus,
*/

#ifndef INDIE_STUDIO_MENUELEMENT_HPP
#define INDIE_STUDIO_MENUELEMENT_HPP

#include <string>
#include <vector>
#include <map>
#include <queue>

#include "Irrlicht.hpp"
#include "settings/Controls.hpp"

namespace render {

	enum ElementType {
		Button,
		CheckBox,
		ComboBox,
		EditBox,
		Image,
		InOutFader,
		ListBox,
		ScrollBar,
		Text,
		Tab,
		TabControl,
	};

	struct MenuElement {
		enum ElementType type;
		int idParent;
		irr::core::rect<irr::s32> position;
		std::wstring text;
		std::vector<std::wstring> v_text;
		std::string path;
		bool check;
		irr::video::SColor color;
		irr::core::vector2di range;
		int step;
	};

	struct eventData {
		int position;
		bool checked;
		std::wstring string;
		Controls::keyIS key;
	};

	class MenuDisplay {
	public:
		MenuDisplay(std::map<int, MenuElement> &element);

		void displayMenu();
		void hideMenu();
		void updateEvents();
		void eraseEvent();
		void addEvent(int id, eventData data);
		std::pair<int, eventData> getNextEvent();
		void updateMenu();
		void updateFocus(irr::gui::IGUIElement *parent, bool reverse, int tab);
		void moveSelection(irr::gui::IGUIElement *focus);
		void updateScrollBar(irr::gui::IGUIScrollBar *selected, Controls::keyIS key);
		void updateEditBox(irr::gui::IGUIEditBox * selected, Controls::keyIS key);
		void updateComboBox(irr::gui::IGUIComboBox *selected, Controls::keyIS key);
		void updateListBox(irr::gui::IGUIListBox *selected, Controls::keyIS key);

		void removeMenu();

	public:
		void setValueCheckBox(int id, bool value);
		void setValueComboBox(int id, std::wstring value);
		void setValueEditBox(int id, std::wstring value);
		void setColorTextEditBox(int id, irr::video::SColor color);
		void setValueListBox(int id, std::wstring value);
		void setValueScrollBar(int id, int value);
		void setValueText(int id, std::wstring value);
		void remove(int id);
		void switchNextTab(int id);
		void switchPrevTab(int id);

	private:
		irr::gui::IGUIElement *_root;
		std::map<int, irr::gui::IGUIElement*> _elements;
		std::queue<std::pair<int, eventData>> _events;
		irr::gui::IGUIImage *_select;
		irr::gui::IGUIElement *_selected;

	};

};

#endif
