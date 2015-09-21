#ifndef __SeventeenSteps__FirstMenu__
#define __SeventeenSteps__FirstMenu__

#include "cocos2d.h"

class FirstMenu : public cocos2d::Layer
{
public:
    // 初期表示
    static cocos2d::Scene* createScene();
    
    // 初期化
    virtual bool init();
    
    // メソッド
    CREATE_FUNC(FirstMenu);
};


#endif /* defined(__SeventeenSteps__FirstMenu__) */
