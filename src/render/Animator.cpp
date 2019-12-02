/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Stromus,
*/

#include "render/Animator.hpp"

irr::core::array<irr::video::ITexture*>	render::Animator::textures = irr::core::array<irr::video::ITexture*>();

void render::Animator::initalizeTextureBeam()
{
	for (irr::s32 g = 7; g > 0; --g)
	{
		irr::core::stringc tmp;
		tmp = "./res/sprite/img/portal";
		tmp += g;
		tmp += ".bmp";
		irr::video::ITexture* t = Irrlicht::getInstance()->getVideo()->getTexture(tmp.c_str());
		textures.push_back(t);
	}
}

void render::Animator::addBeam(irr::core::vector2di pos, int size, int dir, irr::video::SColor color)
{
	auto smgr = Irrlicht::getInstance()->getSceneManager();
	irr::scene::IVolumeLightSceneNode * n = smgr->addVolumeLightSceneNode(0, -1, 32, 32, color, color, \
		irr::core::vector3df(static_cast<irr::f32>(pos.X), 1.5f, static_cast<irr::f32>(pos.Y)), irr::core::vector3df(90, dir * 90.f, 0),\
		irr::core::vector3df(1.f, static_cast<float>(size), 1.f));

	if (n) {
		irr::scene::ISceneNodeAnimator* glow = smgr->createTextureAnimator(textures, 75);
		irr::scene::ISceneNodeAnimator* del = smgr->createDeleteAnimator(525);
		n->addAnimator(glow);
		n->addAnimator(del);
		glow->drop();
		del->drop();
	}
}

void render::Animator::addRotationAnimator(render::MeshNode * mesh, const irr::core::vector3df rotationSpeed)
{
	if (mesh == nullptr)
		return;
	irr::scene::ISceneNodeAnimator *anim = Irrlicht::getInstance()->getSceneManager()->createRotationAnimator(rotationSpeed);
	if (anim) {
		mesh->getNode()->addAnimator(anim);
		anim->drop();
	}
}
