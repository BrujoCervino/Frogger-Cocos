#include "Player.h"

Player::Player()
	: cocos2d::Sprite()
{
	setMoveSpeed(25.0f);
}

Player::~Player()
{
}

Player * Player::create(const char * const pszFileName)
{
	Player* pRet = new ( std::nothrow ) Player();
	if( pRet && pRet->initWithFile(pszFileName) )
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

float Player::getMoveSpeed() const
{
	return moveSpeed;
}

void Player::setMoveSpeed(const float newMoveSpeed)
{
	moveSpeed = newMoveSpeed;
}

bool Player::init()
{
	Sprite::init();
	
	
	setRotation(20.0f);

	return true;
}


