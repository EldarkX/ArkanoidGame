
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

	MovementComponent->SetVelocity(Vector2D(0.f, -1.f));
	MovementComponent->SetSpeed(150.f);
}

void ABuff::SetBuffType(EBuffType newBuffType)
{
	BuffType = newBuffType;

	std::string path;

	switch (BuffType)
	{
	case EBuffType::BallBigSize:
		path = "Assets\\Sprites\\BuffBallBigSize.png";
		break;
	case EBuffType::BallSlowDown:
		path = "Assets\\Sprites\\BuffBallSlowDown.png";
		break;
	case EBuffType::BallSmallSize:
		path = "Assets\\Sprites\\BuffBallSmallSize.png";
		break;
	case EBuffType::BallSpeedUp:
		path = "Assets\\Sprites\\BuffBallSpeedUp.png";
		break;
	}

	mSpriteComponent->SetTexture(new OTexture(path));
}

void ABuff::OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent)
{
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
	}

	SetIsPendingToKill(true);
}

void ABuff::Tick(float deltaTime)
{
	AActor::Tick(deltaTime);

	if (mTransformComponent->GetPosition().Y() < -GameEngine::GetGameEngine()->GetWindowHalfHeight())
	{
		SetIsPendingToKill(true);
	}
}