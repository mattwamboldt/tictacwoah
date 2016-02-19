#include "sdlboneinstanceinfo.h"

#include <spriterengine/global/settings.h>

namespace SpriterEngine
{

	SdlBoneInstanceInfo::SdlBoneInstanceInfo(point initialSize) :
		BoneInstanceInfo(initialSize)
	{
		// TODO: The engine does not yet support rendering of vector shapes

		/*boneShape.setPointCount(4);

		boneShape.setPoint(0, sf::Vector2f(0, initialSize.y/2.0));
		boneShape.setPoint(1, sf::Vector2f(4, 0));
		boneShape.setPoint(2, sf::Vector2f(initialSize.x, initialSize.y/2.0));
		boneShape.setPoint(3, sf::Vector2f(4, initialSize.y));

		boneShape.setOrigin(0, initialSize.y/2.0);

		boneShape.setFillColor(sf::Color(0, 0, 255, 50));

		boneShape.setOutlineColor(sf::Color::White);
		boneShape.setOutlineThickness(1);*/
	}

	void SdlBoneInstanceInfo::render()
	{
		if (Settings::renderDebugBones)
		{
			/*
			boneShape.setPosition(getPosition().x, getPosition().y);
			boneShape.setRotation(toDegrees(getAngle()));
			boneShape.setScale(getScale().x, getScale().y);
			renderWindow->draw(boneShape);*/
		}
	}

}
