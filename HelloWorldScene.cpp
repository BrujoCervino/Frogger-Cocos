/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Scroller.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include <\Program Files (x86)\Windows Kits\10\Include\10.0.17134.0\ucrt\corecrt_math.h>

USING_NS_CC;

#define LAYER_PLAYER (1)

HelloWorld::~HelloWorld()
{
	CC_SAFE_DELETE(closeItem);
	CC_SAFE_DELETE(grassSprites);
	CC_SAFE_DELETE(label);
	CC_SAFE_DELETE(menu);
	CC_SAFE_DELETE(player);
	for( int i = 0; i < 3; ++i )
	{
		CC_SAFE_DELETE(scrollers[i]);
	}
	CocosDenshion::SimpleAudioEngine::end();
}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char * const filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // Exit this function if its base version failed
    if ( !Scene::init() )
    {
        return false;
    }
	
	// Tell the scene we want it to update
	scheduleUpdate();

	// Screen position defaults:
    Size const & visibleSize = Director::getInstance()->getVisibleSize(); // Screen dimensions,
    Vec2 const & origin = Director::getInstance()->getVisibleOrigin();	// Origin,
	Vec2 const screenCenterTemp = Vec2
	(
		(visibleSize.width / 2.0f) + origin.x, 
		(visibleSize.height / 2.0f) + origin.y
	);	// Centre. 
	// Allow other functions to refer to the screen centre
	setScreenCentre(screenCenterTemp);

	initialiseCloseItem(origin, visibleSize);

	initialiseMenu(origin);

	initialiseLabel(origin, visibleSize);

	initialisePlayer(origin);
	
	// Create a keyboard event listener, so the player character can react to keyboard input
	EventListenerKeyboard* const eventListener = EventListenerKeyboard::create();
	// Bind the player movement to the keyboard input
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event)->void
	{		
		// Store the position of the player
		Vec2 finalPlayerPos = player->getPosition();

		const float ms = ( Director::getInstance()->getVisibleSize().height / 28.0f );
		player->setMoveSpeed(ms);

		// Horizontal movement input
		if ( EventKeyboard::KeyCode::KEY_A == keyCode || EventKeyboard::KeyCode::KEY_LEFT_ARROW == keyCode )
		{
			finalPlayerPos.x -= player->getMoveSpeed();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Step.wav", false);
		} 
		else if ( EventKeyboard::KeyCode::KEY_D == keyCode || EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keyCode )
		{
			finalPlayerPos.x += player->getMoveSpeed();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Step.wav", false);
		}
		// Vertical movement input
		if ( EventKeyboard::KeyCode::KEY_S == keyCode || EventKeyboard::KeyCode::KEY_DOWN_ARROW == keyCode )
		{
			finalPlayerPos.y -= player->getMoveSpeed();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Step.wav", false);
		} 
		else if ( EventKeyboard::KeyCode::KEY_W == keyCode || EventKeyboard::KeyCode::KEY_UP_ARROW == keyCode )
		{
			finalPlayerPos.y += player->getMoveSpeed();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Step.wav", false);
		}

		// Set the player's position
		if( finalPlayerPos.x < origin.x )
		{
			finalPlayerPos.x = origin.x;
		}
		else if( finalPlayerPos.x > visibleSize.width )
		{
			finalPlayerPos.x = visibleSize.width;
		}
		if( finalPlayerPos.y < origin.y )
		{
			finalPlayerPos.y = origin.y;
		}
		else if ( finalPlayerPos.y > visibleSize.height )
		{
			finalPlayerPos.y = visibleSize.height;
		}

		player->setPosition(finalPlayerPos);
		
	//	// Scale the player, to imply jumping
	//	ScaleBy* const scalingAction = ScaleBy::create(0.125f, 1.25f);
	//	// Give the scaling action a tag so we can reach it later
	//
	//	// Rotate the player, to imply wiggling
	//	RotateBy* const rotatingAction = RotateBy::create(0.125f, 3.0f);
	//	// Give the scaling action a tag so we can reach it later
	//
	//	// Store whether the player needs to scale
	//	static bool bActionsReversed = false;
	//	// Scale and rotate the player, to make movement more fun
	//	if (!bActionsReversed)
	//	{

	//		player->runAction(scalingAction);
	//		player->runAction(rotatingAction);
	//	}
	//	else
	//	{
	//		player->runAction( scalingAction->reverse() );
	//		player->runAction( rotatingAction->reverse() );
	//	}
	//	// Invert the scaling state
	//	bActionsReversed = !(bActionsReversed);
	};

	// Create the grass sprites
	initialiseGrassSprites(origin, visibleSize, 1.0f, Color3B::GREEN);
	initialiseGrassSprites(origin, visibleSize, 5.0f, Color3B::GREEN);
	// Create the grass sprites
	initialiseScrollers(3);

	// Add our keyboard event listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::update(float delta)
{	
	static float gameTime = 5.0f; 
	gameTime += 3.0f;

	static float xPos = 0.0f;
	xPos = fmod(gameTime, Director::getInstance()->getVisibleSize().width);
	
	
	if( nullptr != scrollers )
	{
		
		for (int Index = 0; Index < 3 ; Index++)
		{
			const float yPos = scrollers[Index]->getPosition().y;
			scrollers[Index]->setPosition(xPos, yPos);

			if( scrollers[Index]->getBoundingBox().intersectsRect(player->getBoundingBox()) )
			{
				player->setColor(Color3B::GREEN);
				init();
			}
			else
			{
				player->setColor(Color3B::YELLOW);
			}
		}
		
	}
}

Vec2 HelloWorld::getScreenCentre() const
{
	return screenCentre;
}

void HelloWorld::setScreenCentre(Vec2 const & newSize)
{
	screenCentre = newSize;
}

void HelloWorld::initialiseScrollers(const int numScrollers)
{
	// If scrollers are null,
	if( nullptr == scrollers[0] )
	{
		for( int index = 0; index < numScrollers; ++index )
		{
			// If the index is non-zero,
			//if( 0 != index )
			//{
			//	// Allocate new memory within scrollers.
			//	++scrollers;
			//}
			// If our scroller was successfully created,

			if( scrollers[index] = Scroller::create("Car_W.png") )
			{
				addChild(scrollers[index], 2);
				const float fOffsetIndex = static_cast<float>( index * 50.0f );
				Vec2 const vOffset = Vec2(fOffsetIndex, fOffsetIndex);
				scrollers[index]->setPosition(getScreenCentre() + vOffset);
				if( index == 0 )
				{
					scrollers[index]->setColor(Color3B::BLUE);
				}
				else if( index == 1 )
				{
					scrollers[index]->setColor(Color3B::GREEN);
				}
				else if( index == 2 )
				{
					scrollers[index]->setColor(Color3B::ORANGE);
					scrollers[index]->setPositionY(getScreenCentre().y + 150.0f);
				}
			}
		}
	}
}

void HelloWorld::initialiseCloseItem(Vec2 const &origin, Size const &visibleSize)
{
	// If the closeItem doesn't exist,
	if( nullptr == closeItem )
	{
		// Create the closeItem.
		closeItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
		
		// If the closeItem is not properly created or the texture is improper,
		const bool closeItemIsInValid =
			(
				nullptr == closeItem ||
				0 >= closeItem->getContentSize().width ||
				0 >= closeItem->getContentSize().height
			);
		if( closeItemIsInValid )
		{
			// Log an error
			problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
		}
	}

	// Move the close item to the bottom right of the screen
	Vec2 const closeItemPos = 
		Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2);
	closeItem->setPosition(closeItemPos);
}

void HelloWorld::initialiseGrassSprites(Vec2 const & origin, Size const & visibleSize, const float grassPos, const Color3B & grassColour)
{
	// The number of grass sprites we'll have, and a floating version of it.
	const int numGrassSprites = 14;
	const float fNumGrassSprites = static_cast<float>( numGrassSprites );

	// Iteratively create and set our grass sprites
	for( int index = 0; index < numGrassSprites; ++index )
	{
		// Store a floating version of our index
		const float fIndex = static_cast<float>( index );
		// If the index is non-zero,
		if( 0 != index )
		{
			// Allocate new memory within grassSprites.
			++grassSprites;
		}
		// Create each sprite, adding it as a child to our scene.
		grassSprites = Sprite::create("Path.png");
		addChild(grassSprites, 0);
		// Reduce the size of each
		//grassSprites->setScale(5.0f);
		grassSprites->setPosition(
			origin.x + ( visibleSize.width / fNumGrassSprites * fIndex ) + ((visibleSize.width/(numGrassSprites))/2.0f),
			origin.y + ((visibleSize.height/fNumGrassSprites)*grassPos));
	}
}

void HelloWorld::initialiseMenu(Vec2 const & origin)
{
	// If the menu does not exist,
	if( nullptr == menu )
	{
		// Create a menu.
		menu = Menu::create(closeItem, NULL);
		// Add the menu as a child of the scene.
		addChild(menu, LAYER_PLAYER);
	}
	// Place the menu at the screen's lower right.
	menu->setPosition(origin);
}

void HelloWorld::initialiseLabel(Vec2 const & origin, Size const & visibleSize)
{
	if( nullptr == label )
	{
		// Create a label reading "Hello World"
		label = Label::createWithTTF("Frogger", "fonts/Marker Felt.ttf", 24);
		if( nullptr == label )
		{
			problemLoading("'fonts/Marker Felt.ttf'");
		}
		else
		{
			// position the label on the center of the screen
			label->setPosition(Vec2(origin.x + visibleSize.width / 2,
				origin.y + visibleSize.height - label->getContentSize().height));

			// add the label as a child to this layer
			addChild(label, 1);
		}
	}
}

void HelloWorld::initialisePlayer(Vec2 const & origin)
{
	// If the player is null,
	if( nullptr == player )
	{
		// Create a sprite for the player
		player = Player::create("Frog_1.png");
		if( nullptr == player )
		{
			problemLoading("'Frog_1.png'");
		}
		else
		{
			// add the sprite as a child to this layer
			addChild(player, 1);
		}
	}
	// position the sprite on the center of the screen
	player->setPosition(
		Vec2(getScreenCentre().x,
			origin.y));
}

