//
//  Constants.h
//  TicTacDuel
//
//  Created by CGarcia on 7/27/13.
//
//

#ifndef TicTacDuel_constants_h
#define TicTacDuel_constants_h
#include "cocos2d.h"
using namespace cocos2d;
typedef enum {
    IconBlank,
    IconCross,
    IconCircle,
}IconState;

typedef enum {
    TurnP1,
    TurnP2,
    TurnNone,
}PlayTurns;

extern int globalTurn;

#endif
