#include "Scroller.h"
#include <\Program Files (x86)\Windows Kits\10\Include\10.0.17134.0\ucrt\corecrt_math.h>

Scroller::Scroller()
	: cocos2d::Sprite()
{
}

Scroller::~Scroller()
{
}

Scroller* Scroller::create(const char * const pszFileName)
{
	Scroller* pRet = new ( std::nothrow ) Scroller();
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

bool Scroller::init()
{
	Sprite::init();
	
	m_ScrollSpeed = 20.0f;
	m_maxPosX = 200.0f;
	
	
	return true;
}

float Scroller::getScrollSpeed() const
{
	return m_ScrollSpeed;
}

void Scroller::setScrollSpeed(const float scrollSpeed)
{
	m_ScrollSpeed = scrollSpeed;
}

void Scroller::scroll(float delta)
{
	//static float xPos;
	//xPos = fmod(delta * getScrollSpeed(), Director::getInstance()->getVisibleSize().width);
	//
	//setPositionX();
}

void Scroller::update(float delta)
{
	const float position = fmod(delta * m_ScrollSpeed, m_maxPosX) + 200.0f;
	
	setPositionX(position);

	

}
