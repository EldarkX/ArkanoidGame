#pragma once

#include "Modules/ObjectModule/Object/Components/InputComponent.h"

#include "SDL_events.h"

class CPlayerController : public CInputComponent
{
public:
	virtual void	ProccessInput(const SDL_Event* event) override;
};
