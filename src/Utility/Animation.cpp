#include "Animation.h"

Animation::Animation(int steps, sf::Vector2u& textureSize, int row, sf::RectangleShape& player) :
	mSteps { steps },
	mTextureSize { textureSize },
	mRow { row },
	mPlayer { player }
{}

void Animation::updatePosition(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;

		unsigned int xOffset { mTextureSize.x * mCurrentStep };
		unsigned int yOffset { mTextureSize.y * mRow };
		mPlayer.setTextureRect(sf::IntRect(xOffset, yOffset, mTextureSize.x, mTextureSize.y));

		++mCurrentStep;
		if (mCurrentStep >= mSteps)
		{
			mCurrentStep = 0;
		}
	}
}