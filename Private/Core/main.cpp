#include "Core/Arcanoid.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h> 
#include <iomanip>

#include <iostream>

int main(int argc, char** argv)
{
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld);

	GameEngine* gameEngine = new ArcanoidGameEngine(1200, 800);

	if (gameEngine->Init())
	{
		gameEngine->Tick();
	}

	delete gameEngine;

	_CrtMemCheckpoint(&sNew); //take a snapshot 
	if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
	{
		std::cout << L"-----------_CrtMemDumpStatistics ---------" << std::endl;
		_CrtMemDumpStatistics(&sDiff);
		std::cout << L"-----------_CrtMemDumpAllObjectsSince ---------" << std::endl;
		_CrtMemDumpAllObjectsSince(&sOld);
		std::cout << L"-----------_CrtDumpMemoryLeaks ---------" << std::endl;
		_CrtDumpMemoryLeaks();
	}

	return 0;
}