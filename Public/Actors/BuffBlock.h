#pragma once

#include "Actors/Block.h"

class ABuffBlock : public ABlock
{
public:
	void	OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent) override;
};