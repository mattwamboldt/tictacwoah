#include "filefactory.h"

#include <spriterengine/override/imagefile.h>
#include <spriterengine/override/soundfile.h>

#include "..\xmlwrapper\tinyxmlspriterfiledocumentwrapper.h"

#include "sdlimagefile.h"
#include "sdlsoundfile.h"

namespace SpriterEngine
{

	SpriterFileFactory::SpriterFileFactory()
	{
	}

	ImageFile * SpriterFileFactory::newImageFile(const std::string &initialFilePath, point initialDefaultPivot)
	{
		return new SdlImageFile(initialFilePath, initialDefaultPivot);
	}

	SoundFile * SpriterFileFactory::newSoundFile(const std::string & initialFilePath)
	{
		return new SdlSoundFile(initialFilePath);
	}

	SpriterFileDocumentWrapper * SpriterFileFactory::newScmlDocumentWrapper()
	{
		return new TinyXmlSpriterFileDocumentWrapper();
	}
}
