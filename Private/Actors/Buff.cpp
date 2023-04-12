
#include "Actors/Buff.h"

#include "Modules/RenderModule/Texture.h"
#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/LinearMovementComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"
#include "Modules/MathModule/Vector2D.h"

#include "Utils/Delegate/Delegate.h"

#include "Core/Arcanoid.h"
#include "Actors/Ball.h"

#include <string>

ABuff::ABuff() : ASpriteActor()
{
	Collision = AddComponent<CCollisionComponent>();
	Collision->SetCollisionChannel(ECollisionChannel::CCE_DynamicObject2);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::CCE_Player, ECollisionType::CTE_Collide);

	Collision->OnComponentCollided += MakeDelegate(this, &ABuff::OnCollision);

	MovementComponent = AddComponent<CLinearMovementComponent>();

	//TODO: Change with base values, no magic constants
	MovementComponent->SetVelocity(Vector2D(0.f, -1.f));
	MovementComponent->SetSpeed(150.f);

	int BuffIndex = rand() % 4 + 1;
	SetBuffType(static_cast<EBuffType>(BuffIndex));
	mSpriteComponent->SetTexture(ArcanoidGameEngine::GetArcanoidGameEngine()->GetBuffManager()->GetBuffTexture(BuffType));
}

void ABuff::OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent)
{
	if (GetIsPendingToKill())
		return; 

	Vector2D	CurrentScale;
	float		CurrentSpeed;

	CurrentScale = ArcanoidGameEngine::GetArcanoidGameEngine()->GetBall()->GetActorTransform()->GetScale();
	CurrentSpeed = ArcanoidGameEngine::GetArcanoidGameEngine()->GetBall()->GetMovementComponent()->GetSpeed();
	
	switch (BuffType)
	{
	case EBuffType::BallBigSize:
		ArcanoidGameEngine::GetArcanoidGameEngine()->GetBall()->GetActorTransform()->SetScale(CurrentScale * 1.25f);
		break;
	case EBuffType::BallSlowDown:
		ArcanoidGameEngine::GetArcanoidGameEngine()->GetBall()->GetMovementComponent()->SetSpeed(CurrentSpeed * 0.75f);
		break;
	case EBuffType::BallSmallSize:
		ArcanoidGameEngine::GetArcanoidGameEngine()->GetBall()->GetActorTransform()->SetScale(CurrentScale * 0.75f);
		break;
	case EBuffType::BallSpeedUp:
		ArcanoidGameEngine::GetArcanoidGameEngine()->GetBall()->GetMovementComponent()->SetSpeed(CurrentSpeed * 1.25f);
		break;
	default:
		break;
	}

	SetIsPendingToKill(true);
}

void ABuff::Tick(float deltaTime)
{
	AActor::Tick(deltaTime);

	float UpperBoundY = mTransformComponent->GetPosition().Y() + mSpriteComponent->GetTexture()->GetHeight() / 2.f;
	if (!GetIsPendingToKill() && UpperBoundY < ArcanoidGameEngine::GetArcanoidGameEngine()->GetKillY())
	{
		Collision->SetCollisionResponseToAllChannels(ECollisionType::CTE_Ignore);
		SetIsPendingToKill(true);
	}
}

void ABuff::SetBuffType(EBuffType newBuffType)
{
	BuffType = newBuffType;
}
