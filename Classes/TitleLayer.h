//
//  TitleLayer.h
//  TicTacDuel
//
//  Created by CGarcia 
//  


#ifndef __TITLELAYER_H__
#define __TITLELAYER_H__

#include "cocos2d.h"

class TitleLayer : public cocos2d::CCLayer
{
public:

	virtual bool init();  
	static cocos2d::CCScene* scene();
    void newGameButtonAction(CCObject* pSender);
    void exitGameButtonAction(CCObject* pSender);
    
    CREATE_FUNC(TitleLayer);

};

#endif // __TITLELAYER_H__
