
#include "Actors/BuffBlock.h"

#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"
#include "Modules/CoreModule/GameEngine.h"
#include "Modules/MathModule/Vector2D.h"

#include "Actors/Buff.h"

void ABuffBlock::OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent)
{
	static int BuffNumber = 0;

	Vector2D Position = Vector2D(GetActorPosition().X(), GetActorPosition().Y() - GetActorSize().Y() - 10.f);
	GameEngine::GetGameEngine()->CreateActor<ABuff>(Position, Vector2D::UnitVector, "Buff" + std::to_string(BuffNumber));

	++BuffNumber;

	ABlock::OnCollision(AnotherActor, AnotherCollisionComponent);
}
