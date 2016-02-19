#ifndef EXAMPLEFILEFACTORY_H
#define EXAMPLEFILEFACTORY_H

#include <spriterengine/override/filefactory.h>

namespace SpriterEngine
{

	class SpriterFileFactory : public FileFactory
	{
	public:
		SpriterFileFactory();
		
		ImageFile *newImageFile(const std::string &initialFilePath, point initialDefaultPivot) override;

		SoundFile *newSoundFile(const std::string &initialFilePath) override;

		SpriterFileDocumentWrapper *newScmlDocumentWrapper() override;
	};

}

#endif // EXAMPLEFILEFACTORY_H
