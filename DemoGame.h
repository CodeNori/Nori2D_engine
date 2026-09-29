#pragma once
#include "IGame.h"
#include "PngImage.h"
#include "XSprite.h"




class DemoGame : public IGame
{
public:
	DemoGame();
	void Update(float delta);
	void Draw(float delta);
	void DrawGUI(float delta);

	XSprite sp_tree;
	XSprite sp_char;
	XSprite sp_explosion;
	int mRenderedSpriteCount = 0;

	float rot = 0.f;
	float one_second = 0.f;
	int   char_color = 0;
};

