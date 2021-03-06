#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class FirstMenu : public cocos2d::Layer {
public:
    // 初期表示
    static cocos2d::Scene* createScene();
    
    // 初期化
    virtual bool init();
    
    // StartButton押下時の処理
    void pushStartButton(cocos2d::Ref* pSender);
    
    // メソッド
    CREATE_FUNC(FirstMenu);
};

#endif // __HELLOWORLD_SCENE_H__
