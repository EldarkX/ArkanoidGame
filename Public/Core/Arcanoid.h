#pragma once

#include "Modules/CoreModule/GameEngine.h"

class ABall;
class APlayer;
class ASpriteActor;

class ArcanoidGameEngine : public GameEngine
{
public:
	ArcanoidGameEngine(int window_width, int window_height) : GameEngine(window_width, window_height) {};

	virtual bool					Init() override;

	APlayer*						GetPlayer() const { return mPlayer; };
	ABall*							GetBall() const { return mBall; }

	void							CreateLevel();
	void							CheckWinCondition(AActor* Actor);

	static ArcanoidGameEngine*		GetArcanoidGameEngine();
private:
	void							OnBallFallOut(ABall* ball);
protected:
	std::vector<ASpriteActor *>		BallLives;
	APlayer*						mPlayer = nullptr;
	ABall*							mBall = nullptr;
	static ArcanoidGameEngine*		mArcanoidGameEngine;	

	Vector2D						PlayerInitPosition = Vector2D::UnitVector;
	Vector2D						BallInitPosition = Vector2D::UnitVector;

	int								BlocksAmount = 0;
	int								Lives = 3;
};