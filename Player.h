#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "2d/CCSprite.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{

public:

	// Default constructor
	Player();

	// Destructor
	virtual ~Player();
	
	// 
	static Player* create(const char * const pszFileName);

	// Returns moveSpeed
	float getMoveSpeed() const;
	// Sets movespeed
	void setMoveSpeed(const float newMoveSpeed);

protected:

	virtual bool init() override;

	// The amount this player will move (floating not vectoral, because the movement is grid-based).
	float moveSpeed;

};

#endif // __PLAYER_H_

