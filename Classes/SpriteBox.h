//
//  Ship.h
//  TicTacDuel
//
//  Created by CGarcia
//

#ifndef __SPRITEBOX_H__
#define __SPRITEBOX_H__

#include "cocos2d.h"
#include "Constants.h"

class SpriteBox : public cocos2d::CCSprite
{
public:
    CCSprite* currentState;
    IconState textState;
    virtual void updateState(IconState state);
	static SpriteBox* boxWithFile(const char *boxState);
    
    CC_SYNTHESIZE(IconState, textState_, textState);
    
	CREATE_FUNC(SpriteBox);
};

#endif // __SPRITEBOX_H__