#include "Actors/Ball.h"

#include "Core/Arcanoid.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/AnimSpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/LinearMovementComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

#include "Modules/RenderModule/Texture.h"

#include <algorithm>

ABall::ABall() : ASpriteActor()
{
	mSpriteComponent->SetTexture(new OTexture("Assets\\Sprites\\Ball.png"));
	MovementComponent = AddComponent<CLinearMovementComponent>();

	Collision = AddComponent<CCollisionComponent>();
	Collision->SetCollisionChannel(ECollisionChannel::CCE_DynamicObject1);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::CCE_Player, ECollisionType::CTE_Collide);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::CCE_StaticObject1, ECollisionType::CTE_Collide);

	Collision->OnComponentCollided += MakeDelegate(this, &ABall::OnCollision);

	ResetBall();
};

void ABall::Tick(float deltaTime)
{
	AActor::Tick(deltaTime);

	isCollided = false;

	if (mTransformComponent->GetPosition().Y() < ArcanoidGameEngine::GetArcanoidGameEngine()->GetKillY())
	{
		mOnBallFallOut(this);
	}
}

void ABall::OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent)
{
	if (!isCollided)
	{
		isCollided = true;
		if (AnotherCollisionComponent->GetCollisionChannel() == ECollisionChannel::CCE_Player)
		{
			MovementComponent->SetVelocity(Vector2D((GetActorPosition().X() - AnotherActor->GetActorPosition().X()) / (AnotherActor->GetActorSize().X() / 2), 1.f));
		}
		else
		{
			double AnotherObjHalfSizeY = AnotherActor->GetActorSize().Y() / 2.;

			if (GetActorPosition().Y() > AnotherActor->GetActorPosition().Y() + AnotherObjHalfSizeY ||
				GetActorPosition().Y() < AnotherActor->GetActorPosition().Y() - AnotherObjHalfSizeY)
				MovementComponent->SetVelocity(Vector2D(MovementComponent->GetVelocity().X(), -MovementComponent->GetVelocity().Y()));
			else
				MovementComponent->SetVelocity(Vector2D(-MovementComponent->GetVelocity().X(), MovementComponent->GetVelocity().Y()));
		}
	}
}

void ABall::ResetBall()
{
	mTransformComponent->SetScale(Vector2D::UnitVector);

	MovementComponent->SetSpeed(InitSpeed);
	MovementComponent->SetVelocity(Vector2D(0.2f, 1.f));
}
