
#include "Core/BuffManager.h"
#include "Modules/RenderModule/Texture.h"

#include <iostream>

bool BuffManager::Initialize()
{
	BuffTextures = {
		{ EBuffType::BallBigSize, new OTexture("Assets\\Sprites\\BuffBallBigSize.png") },
		{ EBuffType::BallSlowDown, new OTexture("Assets\\Sprites\\BuffBallSlowDown.png") },
		{ EBuffType::BallSmallSize, new OTexture("Assets\\Sprites\\BuffBallSmallSize.png") },
		{ EBuffType::BallSpeedUp, new OTexture("Assets\\Sprites\\BuffBallSpeedUp.png") } };

	return true;
}

OTexture* BuffManager::GetBuffTexture(EBuffType BuffType) const
{
	if (BuffTextures.count(BuffType) > 0)
	{
		return BuffTextures.at(BuffType);
	}
	else
	{
		std::cout << "BuffManager::GetBuffTexture() : Failed to find a proper texture" << std::endl;
	}
	return nullptr;
}

void BuffManager::Terminate()
{
	for (auto& BuffTexture : BuffTextures)
	{
		delete BuffTexture.second;
	}
	BuffTextures.clear();
}

