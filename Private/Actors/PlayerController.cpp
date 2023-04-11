
#include "Actors/PlayerController.h"

#include "Modules/ObjectModule/Object/Actor/Components/LinearMovementComponent.h"
#include "Modules/MathModule/Vector2D.h"

#include "Core/Arcanoid.h"
#include "Actors/Player.h"

void CPlayerController::ProccessInput(const SDL_Event* event)
{
	CInputComponent::ProccessInput(event);

	ArcanoidGameEngine* Game = ArcanoidGameEngine::GetArcanoidGameEngine();

	static bool RightPressed = false;
	static bool LeftPressed = false;

	if (event->key.keysym.sym == SDL_KeyCode::SDLK_SPACE && event->type == SDL_KEYDOWN)
	{
		if (Game->GetGameStatus() == EGameStatus::GSE_Game)
			Game->SetGameStatus(EGameStatus::GSE_Pause);
		else
			Game->SetGameStatus(EGameStatus::GSE_Game);
	}

	APlayer* Player = Game->GetPlayer();

	if (event->key.keysym.sym == SDL_KeyCode::SDLK_RIGHT
		|| event->key.keysym.sym == SDL_KeyCode::SDLK_d)
	{
		if (event->type == SDL_KEYDOWN && !RightPressed)
		{
			Player->GetMovementComponent()->SetVelocity(Vector2D(Player->GetMovementComponent()->GetVelocity().X() + 1, 0));
			RightPressed = true;
		}
		else if (event->type == SDL_KEYUP && RightPressed)
		{
			Player->GetMovementComponent()->SetVelocity(Vector2D(Player->GetMovementComponent()->GetVelocity().X() - 1, 0));
			RightPressed = false;
		}
	}
	else if (event->key.keysym.sym == SDL_KeyCode::SDLK_LEFT
		|| event->key.keysym.sym == SDL_KeyCode::SDLK_a)
	{
		if (event->type == SDL_KEYDOWN && !LeftPressed)
		{
			Player->GetMovementComponent()->SetVelocity(Vector2D(Player->GetMovementComponent()->GetVelocity().X() - 1, 0));
			LeftPressed = true;
		}
		else if (event->type == SDL_KEYUP && LeftPressed)
		{
			Player->GetMovementComponent()->SetVelocity(Vector2D(Player->GetMovementComponent()->GetVelocity().X() + 1, 0));
			LeftPressed = false;
		}
	}
}
