
#include "Actors/Block.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Utils/Delegate/Delegate.h"

Block::Block() : ASpriteActor()
{
	mSpriteComponent = AddComponent<CSpriteComponent>();

	Collision = AddComponent<CCollisionComponent>();
	Collision->SetCollisionChannel(ECollisionChannel::CCE_StaticObject1);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::CCE_DynamicObject1, ECollisionType::CTE_Collide);

	Collision->OnComponentCollided += DelegateLib::MakeDelegate(this, &Block::OnCollision);
}

void Block::OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent)
{
	if (AnotherCollisionComponent->GetCollisionChannel() == ECollisionChannel::CCE_DynamicObject1)
		SetIsPendingToKill(true);
}

