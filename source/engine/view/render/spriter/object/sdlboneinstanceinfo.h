#ifndef SFMLBONEINSTANCEINFO_H
#define SFMLBONEINSTANCEINFO_H

#include <spriterengine/objectinfo/boneinstanceinfo.h>

namespace SpriterEngine
{

	class SdlBoneInstanceInfo : public BoneInstanceInfo
	{
	public:
		SdlBoneInstanceInfo(point initialSize);

		void render() override;

	private:
		point initialSize;
	};

}

#endif // SFMLBONEINSTANCEINFO_H
