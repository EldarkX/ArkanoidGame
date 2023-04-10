#include "Actors/Ball.h"

#include "Modules/CoreModule/GameEngine.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/AnimSpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/LinearMovementComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

#include "Modules/RenderModule/Texture.h"

#include <algorithm>

Ball::Ball() : ASpriteActor()
{
	mSpriteComponent->SetTexture(new OTexture("Assets\\Sprites\\Ball.png"));
	MovementComponent = AddComponent<CLinearMovementComponent>();

	Collision = AddComponent<CCollisionComponent>();
	Collision->SetCollisionChannel(ECollisionChannel::CCE_DynamicObject1);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::CCE_Player, ECollisionType::CTE_Collide);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::CCE_StaticObject1, ECollisionType::CTE_Collide);

	Collision->OnComponentCollided += MakeDelegate(this, &Ball::OnCollision);

	MovementComponent->SetSpeed(400.f);

	MovementComponent->SetVelocity(Vector2D(0.2f, 1.f));
};

void Ball::Tick(float deltaTime)
{
	AActor::Tick(deltaTime);

	isCollided = false;

	if (mTransformComponent->GetPosition().Y() < -GameEngine::GetGameEngine()->GetWindowHalfHeight())
	{
		mOnBallFallOut(this);
	}
}

void Ball::OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent)
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
