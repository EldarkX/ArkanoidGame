
#include "Actors/Block.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Utils/Delegate/Delegate.h"

ABlock::ABlock() : ASpriteActor()
{
	mSpriteComponent = AddComponent<CSpriteComponent>();

	Collision = AddComponent<CCollisionComponent>();
	Collision->SetCollisionChannel(ECollisionChannel::CCE_StaticObject1);
	//CCE_DynamicObject1 == the player's ball channel
	Collision->SetCollisionResponseToChannel(ECollisionChannel::CCE_DynamicObject1, ECollisionType::CTE_Collide);

	Collision->OnComponentCollided += DelegateLib::MakeDelegate(this, &ABlock::OnCollision);

	OnStartBeingPendingToKill += DelegateLib::MakeDelegate(this, &ABlock::OnStartBeingPendingToKillCallback);
}

void ABlock::OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent)
{
	if (AnotherCollisionComponent->GetCollisionChannel() == ECollisionChannel::CCE_DynamicObject1)
	{
		SetIsPendingToKill(true);
	}
}

void ABlock::OnStartBeingPendingToKillCallback(AActor* Actor)
{
	if (Collision)
	{
		Collision->SetCollisionResponseToAllChannels(ECollisionType::CTE_Ignore);
	}
}

