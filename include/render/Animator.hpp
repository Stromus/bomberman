/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Stromus,
*/

#include "Irrlicht.hpp"

namespace render {

	class Animator {
	public:
		static void initalizeTextureBeam();

		static void addBeam(irr::core::vector2di pos, int size, int dir, irr::video::SColor color);
		static void addRotationAnimator(render::MeshNode *mesh, const irr::core::vector3df rotationSpeed);

	private:
		static irr::core::array<irr::video::ITexture*> textures;
	};

}