
#include "Core/Arcanoid.h"

#include "Core/BuffManager.h"

#include "Actors/Ball.h"
#include "Actors/Player.h"
#include "Actors/Block.h"
#include "Actors/BuffBlock.h"

#include "Modules/ObjectModule/Object/Actor/Components/AnimSpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

#include "Modules/RenderModule/Texture.h"

#include "Utils/Delegate/Delegate.h"
#include "Modules/MathModule/Vector2D.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

ArcanoidGameEngine* ArcanoidGameEngine::mArcanoidGameEngine = nullptr;

//TODO: change with GameEngine::GetAllActorOfClass()
ArcanoidGameEngine* ArcanoidGameEngine::GetArcanoidGameEngine()
{
	return mArcanoidGameEngine;
}

bool ArcanoidGameEngine::Init()
{
	srand(time(NULL));

	mArcanoidGameEngine = this;

	KillY = -GetWindowHalfHeight();

	mBuffManager = new BuffManager();
	if (!mBuffManager)
	{
		std::cout << "ArcanoidGameEngine::Init() : Failed to create BuffManager" << std::endl;
		return false;
	}
	if (!mBuffManager->Initialize())
	{
		return false;
	}

	/*CREATE PLAYER*/
	PlayerInitPosition = Vector2D(0.f, 0 - GetWindowHeight() / 2.f);
	mPlayer = CreateActor<APlayer>(PlayerInitPosition, Vector2D(0.5f, 1.f), "Player");
	
	/*CREATE BALL*/
	BallInitPosition = Vector2D(0, -(GetWindowHeight() / 2.f) + GetPlayer()->GetActorSize().Y() + 1.f);
	mBall = CreateActor<ABall>(BallInitPosition, Vector2D::UnitVector, "Ball");

	mBall->mOnBallFallOut += MakeDelegate(this, &ArcanoidGameEngine::OnBallFallOut);

	//Add lives
	int x = GetWindowHalfWidth() - 30.f;
	int y = GetWindowHalfHeight() - 30.f;
	auto BallLivesTexture = new OTexture("Assets\\Sprites\\BallLife.png");
	for (int index = 0; index < Lives; ++index)
	{
		BallLives.push_back(CreateActor<ASpriteActor>(Vector2D(x, y), Vector2D::UnitVector, std::string("Ball index " + std::to_string(index))));
		BallLives[index]->GetSpriteComponent()->SetTexture(BallLivesTexture);
		x -= 15.f + BallLives[index]->GetActorSize().X();
	}

	CreateLevel();

	return true;
}

void ArcanoidGameEngine::CreateLevel()
{
	//TODO: change with level settings - read from file
	int mBlocksInRow = 12;
	int rows = 6;

	BlocksAmount = rows * mBlocksInRow;

	float offsetW = WindowWidth / 8.f;
	float offsetH = WindowHeight / 10.f;

	float gapW = 10.f;
	float gapH = 10.f;

	auto* BlockTexture = new OTexture("Assets\\Sprites\\block.png");
	auto* BuffBlockTexture = new OTexture("Assets\\Sprites\\buffBlock.png");
	if (!BlockTexture)
	{
		std::cout << "ERROR: AcranoidGameEngine::LoadLevel: bad block texture." << std::endl;
	}

	float blockWidth = (WindowWidth - offsetW * 2 - gapW * (mBlocksInRow - 2)) / (mBlocksInRow * BlockTexture->GetWidth());
	float blockHeight = (WindowHeight - offsetH - WindowHeight * 0.6f - gapH * (rows - 2)) / (rows * BlockTexture->GetHeight());

	float widthStep = blockWidth * BlockTexture->GetWidth() + gapW;
	float heightStep = blockHeight * BlockTexture->GetHeight() + gapH;

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < mBlocksInRow; ++col)
		{
			float X = -GetWindowHalfWidth() + (offsetW + widthStep * col);
			float Y = GetWindowHalfHeight() - (offsetH + heightStep * row);
			Vector2D BlockPosition = Vector2D(X, Y);

			ABlock* newBlock;
			bool Condition = (row == 5 && (col == 0 || col == 1 || col == 10 || col == 11))
				|| (row % 10 && (col == 5 || col == 6));
			if (Condition)
				newBlock = CreateActor<ABuffBlock>(BlockPosition, Vector2D::UnitVector, "ABlock " + std::to_string(row * mBlocksInRow + col));
			else
				newBlock = CreateActor<ABlock>(BlockPosition, Vector2D::UnitVector, "ABlock " + std::to_string(row * mBlocksInRow + col));
			newBlock->GetSpriteComponent()->SetTexture(Condition ? BuffBlockTexture : BlockTexture);

			newBlock->OnStartBeingPendingToKill += MakeDelegate(this, &ArcanoidGameEngine::CheckWinCondition);
		}
	}

	//Create walls: right, top, left
	ABlock* leftWall = CreateActor<ABlock>(Vector2D(-GetWindowHalfWidth(), 0.f), Vector2D(8.f, WindowHeight), "Left wall");
	leftWall->GetCollisionComponent()->OnComponentCollided.Clear();
	ABlock* rightWall = CreateActor<ABlock>(Vector2D(GetWindowHalfWidth(), 0.f), Vector2D(8.f, WindowHeight), "Right wall");
	rightWall->GetCollisionComponent()->OnComponentCollided.Clear();
	ABlock* topWall = CreateActor<ABlock>(Vector2D(0.f, GetWindowHalfHeight()), Vector2D(WindowWidth, 8.f), "Top wall");
	topWall->GetCollisionComponent()->OnComponentCollided.Clear();
}

void ArcanoidGameEngine::CheckWinCondition(AActor* Actor)
{
	--BlocksAmount;

	if (!BlocksAmount)
	{
		std::cout << "Win!" << std::endl;
		SetGameStatus(EGameStatus::GSE_Exit);
	}
}

void ArcanoidGameEngine::OnBallFallOut(ABall* ball)
{
	if (BallLives.size() > 1)
	{
		BallLives.back()->SetIsPendingToKill(true);
		BallLives.erase(BallLives.end() - 1);

		mPlayer->SetActorPosition(PlayerInitPosition);

		mBall->GetActorTransform()->SetPosition(BallInitPosition);
		mBall->ResetBall();
	}
	else
	{
		SetGameStatus(EGameStatus::GSE_Exit);
	}
}
