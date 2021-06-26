#pragma once

#include "Platform/Platform.hpp"
#include <iostream>

class Animation
{
	int mSteps;
	sf::Vector2u mTextureSize;
	int mYSize;
	int mRow;
	sf::RectangleShape& mPlayer;
	int mCurrentStep { 0 };
	float totalTime { 0 };
	float switchTime { 0.3f };

public:
	Animation(int steps, sf::Vector2u& textureSize, int row, sf::RectangleShape& player);

	void updatePosition(float deltaTime);
};