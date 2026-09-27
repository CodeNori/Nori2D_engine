#pragma once

class IGame
{
public:
	virtual ~IGame() {}
	virtual void Update(float delta) {};
	virtual void Draw(float delta) {};
	virtual void DrawGUI(float delta) {};
};



