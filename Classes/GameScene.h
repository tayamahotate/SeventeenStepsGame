#ifndef __SeventeenSteps__Game__
#define __SeventeenSteps__Game__

#include "cocos2d.h"


//牌
struct Hai {
    int type;   // 34種類の牌を表す
    int number; // 1〜4、赤牌を表すために用意
};

//カードを表示する位置
struct PosIndex {
    int x;
};

class GameScene : public cocos2d::Layer {

protected:
    std::vector<Hai> _hais; //牌情報
    
    void initGame(); //ゲームを初期化する
    void initHais(); //牌を初期化する
    Hai getHai(); //牌を取得する
    void showInitHais(); //ゲーム開始時にカードを13枚表示する
    void createHai(PosIndex posIndex); //牌を作成する

public:
    // 初期表示
    static cocos2d::Scene *createScene();
    
    // 初期化
    virtual bool init();
    
    // 右サイドのメニュー表示
    void showRightSide();

    // StartButton押下時の処理
    void pushReturnButton(cocos2d::Ref* pSender);
    
    // メソッド
    CREATE_FUNC(GameScene);
    
};


#endif /* defined(__SeventeenSteps__Game__) */
