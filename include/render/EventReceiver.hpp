/*
** EPITECH PROJECT, 2021
** indie_studio
** File Description:
** Created by simong,
*/
#ifndef INDIE_STUDIO_EVENTRECEIVER_HPP
#define INDIE_STUDIO_EVENTRECEIVER_HPP

#include "Irrlicht.hpp"
#include "settings/Controls.hpp"

namespace render {
	class EventReceiver : public irr::IEventReceiver {
	public:
		EventReceiver() = default;
		~EventReceiver() = default;

	public:
		// Remember whether each key is down or up
		bool OnEvent(const irr::SEvent &event);

	private:
		// Equivalence Controlls;:keyIS-irr::EKEY_CODE
		std::map<irr::EKEY_CODE, Controls::keyIS> keyEq = {
			{irr::KEY_KEY_A, Controls::keyIS::KEY_A},
			{irr::KEY_KEY_B, Controls::keyIS::KEY_B},
			{irr::KEY_KEY_C, Controls::keyIS::KEY_C},
			{irr::KEY_KEY_D, Controls::keyIS::KEY_D},
			{irr::KEY_KEY_E, Controls::keyIS::KEY_E},
			{irr::KEY_KEY_F, Controls::keyIS::KEY_F},
			{irr::KEY_KEY_G, Controls::keyIS::KEY_G},
			{irr::KEY_KEY_H, Controls::keyIS::KEY_H},
			{irr::KEY_KEY_I, Controls::keyIS::KEY_I},
			{irr::KEY_KEY_J, Controls::keyIS::KEY_J},
			{irr::KEY_KEY_K, Controls::keyIS::KEY_K},
			{irr::KEY_KEY_L, Controls::keyIS::KEY_L},
			{irr::KEY_KEY_M, Controls::keyIS::KEY_M},
			{irr::KEY_KEY_N, Controls::keyIS::KEY_N},
			{irr::KEY_KEY_O, Controls::keyIS::KEY_O},
			{irr::KEY_KEY_P, Controls::keyIS::KEY_P},
			{irr::KEY_KEY_Q, Controls::keyIS::KEY_Q},
			{irr::KEY_KEY_R, Controls::keyIS::KEY_R},
			{irr::KEY_KEY_S, Controls::keyIS::KEY_S},
			{irr::KEY_KEY_T, Controls::keyIS::KEY_T},
			{irr::KEY_KEY_U, Controls::keyIS::KEY_U},
			{irr::KEY_KEY_V, Controls::keyIS::KEY_V},
			{irr::KEY_KEY_W, Controls::keyIS::KEY_W},
			{irr::KEY_KEY_X, Controls::keyIS::KEY_X},
			{irr::KEY_KEY_Y, Controls::keyIS::KEY_Y},
			{irr::KEY_KEY_Z, Controls::keyIS::KEY_Z},
			{irr::KEY_KEY_0, Controls::keyIS::KEY_0},
			{irr::KEY_KEY_1, Controls::keyIS::KEY_1},
			{irr::KEY_KEY_2, Controls::keyIS::KEY_2},
			{irr::KEY_KEY_3, Controls::keyIS::KEY_3},
			{irr::KEY_KEY_4, Controls::keyIS::KEY_4},
			{irr::KEY_KEY_5, Controls::keyIS::KEY_5},
			{irr::KEY_KEY_6, Controls::keyIS::KEY_6},
			{irr::KEY_KEY_7, Controls::keyIS::KEY_7},
			{irr::KEY_KEY_8, Controls::keyIS::KEY_8},
			{irr::KEY_KEY_9, Controls::keyIS::KEY_9},
			{irr::KEY_SPACE, Controls::keyIS::KEY_SPACE},
			{irr::KEY_ESCAPE, Controls::keyIS::KEY_ESC},
			{irr::KEY_RETURN, Controls::keyIS::KEY_ENTER},
			{irr::KEY_BACK, Controls::keyIS::KEY_BACKSPACE},
			{irr::KEY_UP, Controls::keyIS::KEY_ARROW_UP},
			{irr::KEY_DOWN, Controls::keyIS::KEY_ARROW_DOWN},
			{irr::KEY_LEFT, Controls::keyIS::KEY_ARROW_LEFT},
			{irr::KEY_RIGHT, Controls::keyIS::KEY_ARROW_RIGHT},
			{irr::KEY_PRIOR, Controls::keyIS::KEY_PAGE_UP},
			{irr::KEY_NEXT, Controls::keyIS::KEY_PAGE_DOWN}
		};
	};
}

#endif /* !INDIE_STUDIO_EVENTRECEIVER_HPP */
