#ifndef __SeventeenSteps__Game__
#define __SeventeenSteps__Game__

#include "cocos2d.h"
#include <algorithm>
#include <list>
#include <functional>

using namespace std;
// 牌情報
struct Hai {
    int type;   // 34種類の牌を表す
    int number; // 1〜4、赤牌を表すために用意
    
    bool operator < (const Hai& sortObj) const {
        if (type != sortObj.type) {
            return type < sortObj.type;
        } else {
            return number < sortObj.number;
        }
    }
};

// 牌を表示する位置
struct PosIndex {
    int x;
    int y;
};

// 牌のスプライト
class HaiSprite : public cocos2d::Sprite {
protected:
    std::string getFileName(Hai hai); //画像ファイル名取得
    std::string checkAkaHai(Hai hai); //赤牌判定
    
public:
    virtual bool init(); // 初期化処理
    void onEnter() override; // 表示前処理
    CREATE_FUNC(HaiSprite); // create関数作成マクロ
    
    CC_SYNTHESIZE(Hai, _hai, Hai); // 牌情報
    CC_SYNTHESIZE(PosIndex, _posIndex, PosIndex); // 表示位置
};



class GameScene : public cocos2d::Layer {

protected:
    std::vector<Hai> _hais; // 牌情報（vectorは、インデックスで管理しているためアクセスが早い）
    std::list<Hai> _tehai;
    
    void initGame();    // ゲームを初期化する
    void initHais();    // 牌を初期化する
    Hai getHai();       // 牌を取得する
    void dealHais();    // 配牌
    void createHai(PosIndex posIndex); //牌を作成する
    void showTehai();   // 手牌を表示する

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
