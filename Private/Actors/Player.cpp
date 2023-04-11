
#include "Actors/Player.h"

#include "Actors/PlayerController.h"

#include "Modules/CoreModule/GameEngine.h"
#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/LinearMovementComponent.h"

#include "Modules/PhysicsModule/CollisionManager.h"
#include "Modules/RenderModule/Texture.h"
#include "Modules/ObjectModule/Object/Actor/Components/AnimSpriteComponent.h"

APlayer::APlayer() : ASpriteActor()
{
	mSpriteComponent->SetTexture(new OTexture("Assets\\Sprites\\player.png"));

	MovementComponent = AddComponent<CLinearMovementComponent>();

	Collision = AddComponent<CCollisionComponent>();
	Collision->SetCollisionChannel(ECollisionChannel::CCE_Player);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::CCE_DynamicObject1, ECollisionType::CTE_Collide);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::CCE_DynamicObject2, ECollisionType::CTE_Collide);

	PlayerController = AddComponent<CPlayerController>();

	MovementComponent->SetSpeed(InitSpeed);
}

void APlayer::Tick(float deltaTime)
{
	AActor::Tick(deltaTime);

	if (GetActorPosition().X() < -GameEngine::GetGameEngine()->GetWindowHalfWidth() + GetActorSize().X() / 2)
	{
		SetActorPosition(Vector2D(-GameEngine::GetGameEngine()->GetWindowHalfWidth() + GetActorSize().X() / 2, GetActorPosition().Y()));
	}
	else if (GetActorPosition().X() > GameEngine::GetGameEngine()->GetWindowHalfWidth() - GetActorSize().X() / 2)
	{
		SetActorPosition(Vector2D(GameEngine::GetGameEngine()->GetWindowHalfWidth() - GetActorSize().X() / 2, GetActorPosition().Y()));
	}
}
