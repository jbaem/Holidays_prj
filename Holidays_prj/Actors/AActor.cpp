#include "AActor.h"

#include "../Singletons/ResourceManager.h"

AActor::AActor(ResourceID InID)
{
	Image = ResourceManager::GetInstance().GetImage(InID);
}

