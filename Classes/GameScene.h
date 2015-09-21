#ifndef __SeventeenSteps__Game__
#define __SeventeenSteps__Game__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer {
public:
    // 初期表示
    static cocos2d::Scene *createScene();
    
    // 初期化
    virtual bool init();
    
    // メソッド
    CREATE_FUNC(GameScene);
    
};


#endif /* defined(__SeventeenSteps__Game__) */
