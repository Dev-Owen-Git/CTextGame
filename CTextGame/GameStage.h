#pragma once
struct GameStage
{
	enum class StageType
	{
		TITLE,
		GAME,
		OVER,
	};

	static bool SetStage(StageType type);

private:

};

