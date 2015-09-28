#include "HelloWorldScene.h"
#include "GameScene.h"

#include <random>


#define HAI_NUM 4           // 1種類あたりの牌の数
#define HAI_TYPE_NUM 34     // 牌の種類

#define AKAHAI_NUM_MAN 1    // 赤5萬の枚数
#define AKAHAI_NUM_PIN 2    // 赤5筒の枚数
#define AKAHAI_NUM_SOU 1    // 赤5索の枚数

#define HAIPAI_NUM_X 12     // 配牌の枚数(x)
#define HAIPAI_NUM_Y 3      // 配牌の枚数(y)
#define HAIPAI_1_POS_X 20   // 配牌の1番の牌の位置(x)
#define HAIPAI_1_POS_Y 90   // 配牌の1番の牌の位置(y)

#define HAI_DISTANCE_X 23   // 牌の間の距離(x方向)
#define HAI_DISTANCE_Y 40   // 牌の間の距離(y方向)

#define TEHAI_NUM_X 13      // 手牌の枚数(x)
#define TEHAI_1_POS_X 50    // 1番の牌の位置(x)
#define TEHAI_1_POS_Y 35    // 1番の牌の位置(y)

USING_NS_CC;

/* 牌クラスの初期化 */
bool HaiSprite::init() {
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

/* 牌の表示前処理 */
void HaiSprite::onEnter() {

    Sprite::onEnter();
    /* 画像の表示 */
    setTexture(HaiSprite::getFileName(_hai));
    
    /* 牌の位置とタグを指定 */
    float posX = HAIPAI_1_POS_X + HAI_DISTANCE_X * _posIndex.x;
    float posY = HAIPAI_1_POS_Y + HAI_DISTANCE_Y * _posIndex.y;
    setPosition(posX, posY);
    // タグは各牌を一意に特定する1以上の値を設定する（setInitHaisのタグと合わせる）
    setTag(_posIndex.x + _posIndex.y * HAIPAI_NUM_X + 1);
}

/* ソート処理 */
/*
bool GameScene::sortHai(const Hai& hai1, const Hai& hai2) {
    if (hai1.type < hai2.type) {
        return true;
    } else if (hai1.type == hai2.type && hai1.number < hai2.number) {
        return true;
    } else {
        return false;
    }
}
*/

/* GameSceneの作成 */
Scene *GameScene::createScene() {

    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

/* GameSceneの初期化 */
bool GameScene::init() {

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
    
    /* 配牌を行う */
    

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

    Director::getInstance()->pushScene(TransitionFade::create(
            1.0f, FirstMenu::createScene(), Color3B::BLACK));
}

/* ゲーム初期化 */
void GameScene::initGame() {

    /* 牌を初期化する */
    GameScene::initHais();
    
    /* 配牌 */
    GameScene::dealHais();

}

/* 牌の初期化 */
void GameScene::initHais() {
    
    /* 牌のクリア */
    _hais.clear();
    
    /* ランダムに配牌 */
    //34種類 x 4枚分（ファイル名の取得や役の計算を考慮して1からループを回す）
    for (int type = 1; type <= HAI_TYPE_NUM; type++) {
        // 牌の種類も上記に合わせて、1からループを回す
        for (int number = 1; number <= HAI_NUM; number++) {
            //牌情報の作成
            Hai hai;
            hai.number = number;
            hai.type = type;
            
            //牌を追加する
            _hais.push_back(hai);
        }
    }
}

/* 牌の設定 */
void GameScene::dealHais() {

    cocos2d::Sprite hai;
    _tehai.clear();

    /* 牌のタグを初期化 */
    for (int tag = 1; tag <= HAI_NUM * HAI_TYPE_NUM; tag++) {
        auto hai = getChildByTag(tag);
        if (hai) {
            // 牌が残っている場合は、削除する
            hai->removeFromParent();
        }
    }
    
    /* 配牌の枚数分、牌の位置を指定する */
    for (int y = 0; y < HAIPAI_NUM_Y; y++) {
        for (int x = 0; x < HAIPAI_NUM_X; x++) {
            PosIndex posIndex;
            posIndex.x = x;
            posIndex.y = y;
    
            //牌の生成
            createHai(posIndex);
        }
    }
    
    /* 牌のソート */
/*    for (int count = 0; count < 34; count++) {
        _tehai.push_back(_hais[count]);
    }
    
    _tehai.sort();
*/
}

/* 牌の生成と指定 */
void GameScene::createHai(PosIndex posIndex) {

    auto hai = HaiSprite::create();
    
    // 牌をランダムに生成
    hai->setHai(getHai());
    // 順々に位置を設定
    hai->setPosIndex(posIndex);
    addChild(hai, 1);
}

/* 牌の取得 */
Hai GameScene::getHai() {
    
    std::random_device rd;
    std::mt19937 rand = std::mt19937(rd());
    
    /* インデックスをランダムに取得する */
    int index = std::uniform_int_distribution<int>(0, (int)_hais.size() - 1)(rand);
    
    /* 牌の数値を取得する */
    auto hai = _hais[index];
    
    /* 牌がかぶらないように、一時牌から削除する */
    _hais.erase(_hais.begin() + index);
    
    return hai;
}

/* 牌の画像表示 */
std::string HaiSprite::getFileName(Hai hai) {

    std::string fileName;       // 牌の色と数から判定されたファイル名
    std::string fileFirstName;  // 牌の色を表す
    std::string fileSecondName; // 牌の数を表す

    /* 牌の色判定 */
    switch (hai.type) {
        case 1: case 2: case 3: case 4: case 5:
        case 6: case 7: case 8: case 9:
            fileFirstName = "wz"; break;
        case 10: case 11: case 12: case 13: case 14:
        case 15: case 16: case 17: case 18:
            fileFirstName = "pz"; break;
        case 19: case 20: case 21: case 22: case 23:
        case 24: case 25: case 26: case 27:
            fileFirstName = "sz"; break;
        default:
            fileFirstName = "kz"; break;
    }
    
    /* 赤牌判定 */
    fileSecondName = checkAkaHai(hai);
    
    /* 牌の数判定 */
    if (fileSecondName == "0") {
        fileSecondName = StringUtils::format("%d", hai.type % 9);
        // 9で割った余りが0の牌（9萵など）はfileSecondNameに9を指定する
        if (fileSecondName == "0") {
            fileSecondName = "9";
        }
    }
    
    fileName = "haiImage/" + fileFirstName + fileSecondName + ".png";

    return fileName;
}

/* 赤牌判定 */
/* 赤牌は"10"以外は、"0"を返却する。 */
std::string HaiSprite::checkAkaHai(Hai hai) {

    std::string fileSecondName = "0"; // 牌の数を表す
    /* 赤5萵判定 */
    if (hai.type == 5 && hai.number <= AKAHAI_NUM_MAN) {
        fileSecondName = "10";
    }
    /* 赤5筒判定 */
    if (hai.type == 14 && hai.number <= AKAHAI_NUM_PIN) {
        fileSecondName = "10";
    }
    /* 赤5索判定 */
    if (hai.type == 23 && hai.number == AKAHAI_NUM_SOU) {
        fileSecondName = "10";
    }
    
    return fileSecondName;
}









