
#include "Actors/PlayerController.h"

#include "Modules/ObjectModule/Object/Actor/Components/LinearMovementComponent.h"
#include "Modules/MathModule/Vector2D.h"

#include "Core/Arcanoid.h"
#include "Actors/Player.h"

void CPlayerController::ProccessInput(const SDL_Event* event)
{
	CInputComponent::ProccessInput(event);

	ArcanoidGameEngine* Game = dynamic_cast<ArcanoidGameEngine *>(GameEngine::GetGameEngine());

	static bool RightPressed = false;
	static bool LeftPressed = false;

	if (event->key.keysym.sym == SDL_KeyCode::SDLK_SPACE && event->type == SDL_KEYDOWN)
	{
		if (Game->GetGameStatus() == EGameStatus::GSE_Game)
			Game->SetGameStatus(EGameStatus::GSE_Pause);
		else
			Game->SetGameStatus(EGameStatus::GSE_Game);
	}

	Player* player = Game->GetPlayer();

	if (event->key.keysym.sym == SDL_KeyCode::SDLK_RIGHT
		|| event->key.keysym.sym == SDL_KeyCode::SDLK_d)
	{
		if (event->type == SDL_KEYDOWN && !RightPressed)
		{
			player->GetMovementComponent()->SetVelocity(Vector2D(player->GetMovementComponent()->GetVelocity().X() + 1, 0));
			RightPressed = true;
		}
		else if (event->type == SDL_KEYUP && RightPressed)
		{
			player->GetMovementComponent()->SetVelocity(Vector2D(player->GetMovementComponent()->GetVelocity().X() - 1, 0));
			RightPressed = false;
		}
	}
	else if (event->key.keysym.sym == SDL_KeyCode::SDLK_LEFT
		|| event->key.keysym.sym == SDL_KeyCode::SDLK_a)
	{
		if (event->type == SDL_KEYDOWN && !LeftPressed)
		{
			player->GetMovementComponent()->SetVelocity(Vector2D(player->GetMovementComponent()->GetVelocity().X() - 1, 0));
			LeftPressed = true;
		}
		else if (event->type == SDL_KEYUP && LeftPressed)
		{
			player->GetMovementComponent()->SetVelocity(Vector2D(player->GetMovementComponent()->GetVelocity().X() + 1, 0));
			LeftPressed = false;
		}
	}
}
