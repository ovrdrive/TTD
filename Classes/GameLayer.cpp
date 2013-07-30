//
//  GameLayer.cpp
//  TicTacDuel
//
//  Created by CGarcia
//

#include "TitleLayer.h"
#include "GameLayer.h"
#include "Constants.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameLayer::scene()
{
	CCScene *scene = CCScene::create();
	GameLayer *layer = GameLayer::create();
	scene->addChild(layer);
    
	return scene;
}

bool GameLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    this->setTouchEnabled(true);

    windowSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor* bgLayer = new CCLayerColor;
	bgLayer->initWithColor(ccc4(255, 255, 255, 140));
    this->addChild(bgLayer, 1);
    
    objectLayer = new CCLayer;
    this->addChild(objectLayer,2);
    globalTurn = TurnP1;
    CCMenuItemImage *pauseGameButton = CCMenuItemImage::create(
                                                             "CloseNormal.png",
                                                             "CloseSelected.png",
                                                             this,
                                                             menu_selector(GameLayer::pauseGameButtonAction));
    
    CCMenu* cornerMenu = CCMenu::create(pauseGameButton, NULL);
    cornerMenu->setPosition( ccp(windowSize.width-pauseGameButton->getContentSize().width, pauseGameButton->getContentSize().height) );
    this->addChild(cornerMenu, 4);
    
    CCSprite* boardSprite = CCSprite::create("gameboard.png");
    boardSprite->setPosition( ccp(windowSize.width/2, windowSize.height/2) );
    this->addChild(boardSprite, 3);
    
    this->createGrid();
	return true;
}

void GameLayer::createGrid()
{
    grid = new CCArray();
    for (int i=0; i<3; i++) {
        CCArray* columnArray = CCArray::create();
        for (int j=0; j<3; j++) {
            SpriteBox* stateSprite = SpriteBox::boxWithFile("blank_tile.png");
            objectLayer->addChild(stateSprite,1);
            stateSprite->setPosition(ccp(60+ i*100 + stateSprite->getContentSize().width/2,
                                       140+ j*100 + stateSprite->getContentSize().height/2));
            columnArray->addObject(stateSprite);
            }
        grid->addObject(columnArray);
    }
}

CCPoint GameLayer::touchToPoint(CCTouch* touch)
{
    return CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}

SpriteBox* GameLayer::GetSprite(CCTouch* aLocation)
{
    for(int i = 0; i < objectLayer->getChildren()->count(); i++)
    {
        CCObject* child = objectLayer->getChildren()->objectAtIndex(i);
    
        float left = (static_cast<SpriteBox*> (child))->getPositionX() - (static_cast<SpriteBox*> (child))->getContentSize().width;
        float right = (static_cast<SpriteBox*> (child))->getPositionX();
        float top = (static_cast<SpriteBox*> (child))->getPositionY();
        float bottom = (static_cast<SpriteBox*> (child))->getPositionY() - (static_cast<SpriteBox*> (child))->getContentSize().height;
        if (aLocation->getLocation().x < right && aLocation->getLocation().x > left &&
            aLocation->getLocation().y < top && aLocation->getLocation().y > bottom) {
            
            return (static_cast<SpriteBox*> (child));
        }
    }
    return NULL;
}

void GameLayer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	// reset touch offset
    this->touchOffset = CCPointZero;
    
    SpriteBox* icon;
    
    for( auto it = touches->begin(); it != touches->end(); it++)
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(*it);
        icon = this->GetSprite(touch);
	}
    
    if (icon && icon->textState == IconBlank) {
        if (globalTurn == TurnP1){
            icon->updateState(IconCross);
            this->checkForWinCondition();
            globalTurn = TurnP2;
        } else if (globalTurn == TurnP2){
            icon->updateState(IconCircle);
            this->checkForWinCondition();
            globalTurn = TurnP1;
        }
       
    }
    
    
}

void GameLayer::checkForWinCondition()
{
    
    CCArray* column0 = (dynamic_cast<CCArray*>(grid->objectAtIndex(0)));
    CCArray* column1 = (dynamic_cast<CCArray*>(grid->objectAtIndex(1)));
    CCArray* column2 = (dynamic_cast<CCArray*>(grid->objectAtIndex(2)));

    SpriteBox* child0 = (dynamic_cast<SpriteBox*>(column0->objectAtIndex(2)));//1
    SpriteBox* child1 = (dynamic_cast<SpriteBox*>(column1->objectAtIndex(2)));//2
    SpriteBox* child2 = (dynamic_cast<SpriteBox*>(column2->objectAtIndex(2)));//3
    
    SpriteBox* child3 = (dynamic_cast<SpriteBox*>(column0->objectAtIndex(1)));//11
    SpriteBox* child4 = (dynamic_cast<SpriteBox*>(column1->objectAtIndex(1)));//22
    SpriteBox* child5 = (dynamic_cast<SpriteBox*>(column2->objectAtIndex(1)));//33
    
    SpriteBox* child6 = (dynamic_cast<SpriteBox*>(column0->objectAtIndex(0)));//111
    SpriteBox* child7 = (dynamic_cast<SpriteBox*>(column1->objectAtIndex(0)));//222
    SpriteBox* child8 = (dynamic_cast<SpriteBox*>(column2->objectAtIndex(0)));//333
    
    int tempTurn = globalTurn;
    int tempIcon;
    if(tempTurn == TurnP1)
    {
        tempIcon = IconCross;
    }
    else if(tempTurn == TurnP2)
    {
        tempIcon = IconCircle;
    }
    
        //2 corner checking
        if(child0->textState == tempIcon && child1->textState == tempIcon && child2->textState == tempIcon)
        {
            globalTurn = tempTurn;
            this->winLayer();
        }
        else if(child0->textState == tempIcon && child3->textState == tempIcon && child6->textState == tempIcon)
        {
            globalTurn = tempTurn;
            this->winLayer();
        }
        else if(child8->textState == tempIcon && child7->textState == tempIcon && child6->textState == tempIcon)
        {
            globalTurn = tempTurn;
            this->winLayer();
        }
        else if(child8->textState == tempIcon && child5->textState ==tempIcon && child2->textState == tempIcon)
        {
            globalTurn = tempTurn;
            this->winLayer();
        }
        //center checking
        else if(child0->textState == tempIcon && child4->textState == tempIcon && child8->textState == tempIcon)
        {
            globalTurn = tempTurn;
            this->winLayer();
        }
        else if(child6->textState == tempIcon && child4->textState == tempIcon && child2->textState == tempIcon)
        {
            globalTurn = tempTurn;
            this->winLayer();
        }
        else if(child1->textState == tempIcon && child4->textState == tempIcon && child7->textState == tempIcon)
        {
            globalTurn = tempTurn;
            this->winLayer();
        }
        else if(child3->textState == tempIcon && child4->textState == tempIcon && child5->textState == tempIcon)
        {
            globalTurn = tempTurn;
            this->winLayer();
        }
        else
        {
            int blankCtr=0;
            for(int i = 0; i < objectLayer->getChildren()->count(); i++)
            {
                SpriteBox* pluckChild = (dynamic_cast<SpriteBox*>(objectLayer->getChildren()->objectAtIndex(i)));
                    
                if(pluckChild->textState==IconBlank)
                {
                    blankCtr++;
                }
            }
            if(blankCtr==0)
            {
                globalTurn = TurnNone;
                this->winLayer();
            }
        }
}

void GameLayer::winLayer()
{
    CCLabelBMFont * label;
    if(globalTurn == TurnP1)
    {
        label = CCLabelBMFont::create("P1 Wins!", "Arial.fnt");
    }
    else if(globalTurn == TurnP2)
    {
        label = CCLabelBMFont::create("P2 Wins!", "Arial.fnt");
    }
    else if(globalTurn == TurnNone)
    {
        label = CCLabelBMFont::create("It's a Draw!", "Arial.fnt");
    }
    
    cocos2d::CCLayerColor* colorLayer = new CCLayerColor;
	colorLayer->initWithColor(ccc4(0, 0, 0, 100));
    colorLayer->setOpacity(40);
    colorLayer->setTouchEnabled(false);
    this->setTouchEnabled(false);
    this->addChild(colorLayer, 5, 11);
    
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    label->setScale(1);
    label->setPosition(ccp(windowSize.width/2 , windowSize.height*0.6));
    this->addChild(label, 6,12);
    
    CCMenuItemImage *newGameButton = CCMenuItemImage::create(
                                                             "new_game.png",
                                                             "new_game_down.png",
                                                             this,
                                                             menu_selector(GameLayer::restartGameButtonAction));
    CCMenuItemImage *exitGameButton = CCMenuItemImage::create(
                                                              "exit_game.png",
                                                              "exit_game_down.png",
                                                              this,
                                                              menu_selector(GameLayer::exitGameButtonAction));
    
    CCMenu* titleMenu = CCMenu::create(newGameButton, exitGameButton, NULL);
    
    titleMenu->alignItemsVerticallyWithPadding(5);
    titleMenu->setPosition(ccp(windowSize.width/2, windowSize.height/2.5));
    this->addChild(titleMenu,6,13);
    
}

void GameLayer::pauseGameButtonAction(CCObject* pSender)
{
    cocos2d::CCLayerColor* colorLayer = new CCLayerColor;
	colorLayer->initWithColor(ccc4(0, 0, 0, 100));
    colorLayer->setOpacity(40);
    colorLayer->setTouchEnabled(false);
    this->setTouchEnabled(false);
    this->addChild(colorLayer, 5, 9);
    
    CCMenuItemImage *resumeGameButton = CCMenuItemImage::create(
                                                                "resume.png",
                                                                "resume_down.png",
                                                                this,
                                                                menu_selector(GameLayer::resumeGameButtonAction));
    CCMenuItemImage *restartGameButton = CCMenuItemImage::create(
                                                                 "restart.png",
                                                                 "restart_down.png",
                                                                 this,
                                                                 menu_selector(GameLayer::restartGameButtonAction));
    CCMenuItemImage *exitGameButton = CCMenuItemImage::create(
                                                              "exit_game.png",
                                                              "exit_game_down.png",
                                                              this,
                                                              menu_selector(GameLayer::exitGameButtonAction));
    
    CCMenu* pauseMenu = CCMenu::create(resumeGameButton, restartGameButton, exitGameButton, NULL);
    
    pauseMenu->alignItemsVerticallyWithPadding(5);
    pauseMenu->setPosition(ccp(windowSize.width/2, windowSize.height/2));
    this->addChild(pauseMenu, 6, 10);
}

void GameLayer::resumeGameButtonAction(CCObject* pSender)
{
    this->setTouchEnabled(true);
    this->removeChildByTag(9);
    this->removeChildByTag(10);
    this->removeChildByTag(11);
    this->removeChildByTag(12);
}

void GameLayer::restartGameButtonAction(CCObject* pSender)
{
    this->removeChildByTag(9);
    this->removeChildByTag(10);
    this->removeChildByTag(11);
    this->removeChildByTag(12);
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void GameLayer::exitGameButtonAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(TitleLayer::scene());
}
