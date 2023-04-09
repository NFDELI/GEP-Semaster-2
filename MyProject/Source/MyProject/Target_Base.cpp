#include "Target_Base.h"

DEFINE_LOG_CATEGORY_STATIC(LogTargetBase, Display, All);
// Sets default values
ATarget_Base::ATarget_Base()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);
}

// Called when the game starts or when spawned
void ATarget_Base::BeginPlay()
{
	Super::BeginPlay();
}

void ATarget_Base::ShottedAt()
{
	//Do reaction of being shot at here.
	TeleAway();
}

void ATarget_Base::TeleAway()
{
	SetActorLocation(FVector3d(-1000, -1000, -1000));
	UE_LOG(LogTargetBase, Display, TEXT("Teleporting the base Target class!"));
}


