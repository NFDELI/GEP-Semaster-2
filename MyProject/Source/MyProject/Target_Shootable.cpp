#include "Target_Shootable.h"

DEFINE_LOG_CATEGORY_STATIC(LogTargetShootable, Display, All);

void ATarget_Shootable::ShottedAt()
{
	UE_LOG(LogTargetShootable, Display, TEXT("Firing hitscan weapon class"));
}
