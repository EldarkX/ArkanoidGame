
#include "Actors/BuffBlock.h"

#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"
#include "Modules/CoreModule/GameEngine.h"
#include "Modules/MathModule/Vector2D.h"

#include "Actors/Buff.h"

void ABuffBlock::OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent)
{
	static int BuffNumber = 0;
	Vector2D Position = Vector2D(GetActorPosition().X(), GetActorPosition().Y() - GetActorSize().Y() - 10.f);

	auto Buff = GameEngine::GetGameEngine()->CreateActor<ABuff>(Position, Vector2D::UnitVector, "BallBigSize" + BuffNumber);

	Buff->SetBuffType(static_cast<EBuffType>(rand() % 4));

	++BuffNumber;

	SetIsPendingToKill(true);
}