#ifndef __SCROLLER_H_
#define __SCROLLER_H_

#include "2d/CCSprite.h"

USING_NS_CC;

// Scroller is the base class for most of Frogger's classes: 
// Cars, logs, crocodiles and turtles must all scroll from left to right or vice versa
class Scroller : public cocos2d::Sprite
{

public:

	// Default constructor
	Scroller();

	// Destructor
	virtual ~Scroller();

	// This function was borrowed and adapted from PhysicsSprite::create
	static Scroller* create(const char * const pszFileName);
	
	float getScrollSpeed() const;

protected:

	virtual bool init() override;

	void setScrollSpeed(const float newSpeed);

	virtual void scroll(float delta);

	virtual void update(float delta) override;

private:

	
	float m_ScrollSpeed;

	float m_maxPosX;

};

#endif // __SCROLLER_H_

