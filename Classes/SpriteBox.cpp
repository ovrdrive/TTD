//
//  SpriteBox.cpp
//  TicTacDuel
//
//  Created by CGarcia
//

#include "SpriteBox.h"

USING_NS_CC;

SpriteBox* SpriteBox::boxWithFile(const char *boxState)
{
    SpriteBox *pobSprite = new SpriteBox();
    if (pobSprite && pobSprite->initWithFile(boxState))
    {
        pobSprite->scheduleUpdate();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void SpriteBox::updateState(IconState state)
{
    if (currentState) {
        currentState->removeFromParentAndCleanup(true);
        currentState = NULL;
    }
    
    switch (state) {
        case IconCircle:
            currentState = new CCSprite;
            currentState->initWithFile("o_tile.png");
            this->addChild(currentState,4);
            break;
        case IconCross:
            currentState = new CCSprite;
            currentState->initWithFile("x_tile.png");
            this->addChild(currentState,4);
            break;
        case IconBlank:
            currentState = new CCSprite;
            currentState->initWithFile("blank_tile.png");
            this->addChild(currentState,4);
            break;
        default:
            break;
    }
    this->textState = state;
    CCLOG ("%u \n", state);
    this->setContentSize(currentState->getContentSize());
}
