#ifndef __TEMPLATE_H_
#define __TEMPLATE_H_

#include "2d/CCSprite.h"

USING_NS_CC;

class Template : public Sprite
{

public:

	// Default constructor
	Player();

	// Destructor
	virtual ~Player();

protected:

	virtual bool init() override;

};

#endif // __TEMPLATE_H_

