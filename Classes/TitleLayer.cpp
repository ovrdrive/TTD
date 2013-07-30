//
//  TitleLayer.cpp
//  TicTacDuel
//
//  Created by CGarcia
//

#include "TitleLayer.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* TitleLayer::scene()
{

	CCScene *scene = CCScene::create();
	TitleLayer *layer = TitleLayer::create();
	scene->addChild(layer);

	return scene;
}

bool TitleLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* titleSprite = CCSprite::create("game_title.png");
    titleSprite->setPosition( ccp(windowSize.width/2, windowSize.height/1.3) );
    this->addChild(titleSprite, 1);
    
    CCMenuItemImage *newGameButton = CCMenuItemImage::create(
                                                          "new_game.png",
                                                          "new_game_down.png",
                                                          this,
                                                          menu_selector(TitleLayer::newGameButtonAction));
    CCMenuItemImage *exitGameButton = CCMenuItemImage::create(
                                                             "exit_game.png",
                                                             "exit_game_down.png",
                                                             this,
                                                             menu_selector(TitleLayer::exitGameButtonAction));

    CCMenu* titleMenu = CCMenu::create(newGameButton, exitGameButton, NULL);
    titleMenu->alignItemsVerticallyWithPadding(5);
    titleMenu->setPosition(ccp(windowSize.width/2, titleSprite->getPosition().y - titleSprite->getContentSize().height / 1.1));
    this->addChild(titleMenu,1);

    CCSprite* bgSprite = CCSprite::create("background.png");
    bgSprite->setPosition( ccp(windowSize.width/2, windowSize.height/2) );
    this->addChild(bgSprite, 0);
        
	return true;
}

void TitleLayer::newGameButtonAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void TitleLayer::exitGameButtonAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
