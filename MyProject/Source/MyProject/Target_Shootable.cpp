#include "Target_Shootable.h"

DEFINE_LOG_CATEGORY_STATIC(LogTargetShootable, Display, All);

ATarget_Shootable::ATarget_Shootable()
{
	//Constructor.
	_CurrentHealth = _MaxHealth;
}

void ATarget_Shootable::ShottedAt(float damage)
{
	UE_LOG(LogTargetShootable, Display, TEXT("TARGET_SHOOTABLE is Shot AT"));
	TakeDamage(damage);
	//ColorChange();
}

void ATarget_Shootable::ColorChange()
{
	_StaticMesh->SetMaterial(0, MaterialTwo);
}

void ATarget_Shootable::TakeDamage(float damage)
{
	_CurrentHealth -= damage;
	if(_CurrentHealth <= 0)
	{
		//Target lost all HP.
		TargetDeath();
	}
}

void ATarget_Shootable::TargetDeath()
{
	//Play Death animation here.
	ColorChange();
}


