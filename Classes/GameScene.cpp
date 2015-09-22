#include "HelloWorldScene.h"
#include "GameScene.h"

#include <random>

#define HAI_NUM 4          // 1種類あたりの牌の数
#define HAI_TYPE_NUM 34    // 牌の種類
#define TEHAI_NUM 13       // 手牌の枚数

#define HAI_1_POS_X 50 //1番の牌の位置(x)
#define HAI_1_POS_Y 35 //1番の牌の位置(y)
#define HAI_DISTANCE_X 23 //牌の間の距離(x方向)

USING_NS_CC;

Scene* GameScene::createScene() {
    //シーンを生成する
    auto scene = Scene::create();
    //HelloWorldクラスのレイヤーを生成する
    auto layer = GameScene::create();
    //シーンに対してレイヤーを追加する
    scene->addChild(layer);
    //シーンを返す
    return scene;

return scene;
}

// 初期化
bool GameScene::init() {

    /* お約束 */
    if ( !Layer::init() ) {
        return false;
    }
    /* 背景画像設定 */
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("haikei.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,
                             visibleSize.height/2 + origin.y));
    sprite->setScale(6, 6);
    this->addChild(sprite, 0);

    /* 右サイドのメニュー表示 */
    GameScene::showRightSide();
    
    /* ゲームを初期化する */
    GameScene::initGame();

    return true;
}

/* 右サイドのメニュー設定 */
void GameScene::showRightSide() {
    /* 背景 */
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("rightSide.png");
    sprite->setPosition(Vec2(visibleSize.width*0.92 + origin.x,
                             visibleSize.height*0.25 + origin.y));
    sprite->setScale(0.48, 0.81);
    this->addChild(sprite, 1);
    
    /* Returnボタン */
    auto returnButton = MenuItemImage::create("start1.png", "start2.png", CC_CALLBACK_1(GameScene::pushReturnButton, this));
    auto menu = Menu::create(returnButton, NULL);
    returnButton->setScale(0.2, 0.4);
    menu->setPosition(Vec2(origin.x + visibleSize.width*.92,
                           origin.y + visibleSize.height*.83));
    this->addChild(menu, 1);
    
    /* Returnラベル */
    auto returnLabel = Label::createWithTTF("戻る", "fonts/ooama.ttf", 16);
    returnLabel->setPosition(Vec2(origin.x + visibleSize.width*.92,
                                  origin.y + visibleSize.height*.83));
    this->addChild(returnLabel,2);
    
    /* タイトル設定 */
    auto gameTitle = Label::createWithTTF("十七歩", "fonts/ooama.ttf", 18);
    gameTitle->setPosition(Vec2(origin.x + visibleSize.width*.92,
                                origin.y + visibleSize.height*.93));
    this->addChild(gameTitle, 1);
}


/* ReturnButton押下時の処理 */
void GameScene::pushReturnButton(Ref* pSender) {
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, FirstMenu::createScene(), Color3B::BLACK));
}

/* ゲーム初期化 */
void GameScene::initGame() {
    /* 牌を初期化する */
    GameScene::initHais();
    
    /* 牌を表示する */
    GameScene::showInitHais();
}

/* 牌の初期化 */
void GameScene::initHais() {
    /* 牌のクリア */
    _hais.clear();
    
    /* ランダムに配牌 */
    //34種類 x 4枚分（後々の役の計算を考慮して1からループを回す）
    for (int type = 1; type <= HAI_TYPE_NUM; type++) {
        // 牌の種類も上記に合わせて、1からループを回す
        for (int number = 1; number <= HAI_NUM; number++) {
            //カード情報の作成
            Hai hai;
            hai.number = number;
            hai.type = type;
            
            //カードを追加する
            _hais.push_back(hai);
        }
    }
}

/* 牌の取得 */
Hai GameScene::getHai() {
    std::random_device rd;
    std::mt19937 rand = std::mt19937(rd());
    
    //インデックスをランダムに取得する
    int index = std::uniform_int_distribution<int>(0, (int)_hais.size() - 1)(rand);
    
    //カードの数値を取得する
    auto hai = _hais[index];
    
    //一時カードから削除する
    _hais.erase(_hais.begin() + index);
    
    return hai;
}

/* 牌の表示 */
void GameScene::showInitHais() {
    for (int tag = 1; tag <= 10; tag++) {
        auto hai = getChildByTag(tag);
        if (hai) {
            //カードが残っている場合は、削除する
            hai->removeFromParent();
        }
    }
    
    /* 枚数分生成 */
    for (int x = 0; x < TEHAI_NUM; x++) {
        PosIndex posIndex;
        posIndex.x = x;
            
        //牌の生成
        createHai(posIndex);
    }
}

/* 牌の生成 */
void GameScene::createHai(PosIndex posIndex) {
    //新しいカードを作成する
    auto hai = Sprite::create("haiImage/wz1.png");
    hai->setPosition(HAI_1_POS_X + HAI_DISTANCE_X * posIndex.x,
                      HAI_1_POS_Y);
    addChild(hai, 1);
}








