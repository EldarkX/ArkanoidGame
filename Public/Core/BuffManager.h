#pragma once

#include "Modules/CoreModule/Subsystem.h"

#include <map>

class OTexture;

enum class EBuffType
{
	None,
	BallBigSize,
	BallSmallSize,
	BallSpeedUp,
	BallSlowDown
};

class BuffManager : public Subsystem
{
public:
	bool		Initialize() override;
	OTexture*	GetBuffTexture(EBuffType BuffType) const;
	void		Terminate() override;
protected:
	std::map<EBuffType, OTexture*> BuffTextures;

};