#pragma once

#include "Modules/CoreModule/GameEngine.h"

#include <string>

class Ball;
class Player;
class ASpriteActor;

class ArcanoidGameEngine : public GameEngine
{
public:
	ArcanoidGameEngine(int window_width, int window_height) : GameEngine(window_width, window_height) {};

	virtual bool					Init() override;

	Player							*GetPlayer() const { return mPlayer; };
	Ball							*GetBall() const { return mBall; }
	void							LoadLevel(std::string path);
	void							CheckWinCondition(AActor* Actor);


	static ArcanoidGameEngine		*GetArcanoidGameEngine();
private:
	void							OnBallFallOut(Ball* ball);
protected:
	std::vector<ASpriteActor *>		BallLives;
	Player							*mPlayer = nullptr;
	Ball							*mBall = nullptr;
	static ArcanoidGameEngine*		mArcanoidGameEngine;	

	int								blocksAmount = 0;
	int								Lives = 3;
};