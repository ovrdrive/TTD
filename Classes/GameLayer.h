//
//  GameLayer.h
//  TicTacDuel
//
//  Created by CGarcia
//

#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "SpriteBox.h"

class GameLayer : public cocos2d::CCLayer
{
public:

    virtual bool init();  

    static CCScene* scene();
    
    CCLayer* objectLayer;
    CCSize windowSize;
    CCArray* grid;
    CCPoint touchOffset;
    
    void createGrid();
    void pauseGameButtonAction(CCObject* pSender);
    void resumeGameButtonAction(CCObject* pSender);
    void restartGameButtonAction(CCObject* pSender);
    void exitGameButtonAction(CCObject* pSender);
    void winLayer();
    void checkForWinCondition();
    CCPoint touchToPoint(CCTouch* touch);
    SpriteBox* GetSprite(CCTouch* touch);
    void ccTouchesBegan(CCSet* touches, CCEvent* event);
    
    CREATE_FUNC(GameLayer);
};

#endif // __GAMELAYER_H__
