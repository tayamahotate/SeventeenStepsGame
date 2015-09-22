#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* FirstMenu::createScene() {
    //シーンを生成する
    auto scene = Scene::create();
    //HelloWorldクラスのレイヤーを生成する
    auto layer = FirstMenu::create();
    //シーンに対してレイヤーを追加する
    scene->addChild(layer);
    //シーンを返す
    return scene;
}

// 初期化
bool FirstMenu::init() {
    /* お約束 */
    if ( !Layer::init() ) {
        return false;
    }

    /* 背景画像設定 */
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("haikei.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // (TODO)画面最大幅に背景画像を表示する方法がわからないので、とりあえず元のサイズの7倍に拡大
    sprite->setScale(6, 6);
    this->addChild(sprite, 0);
    
    /* Startボタン */
    auto startButton = MenuItemImage::create("start1.png", "start2.png", CC_CALLBACK_1(FirstMenu::pushStartButton, this));
    auto menu = Menu::create(startButton, NULL);
    startButton->setScale(0.6, 0.6);
    this->addChild(menu, 1);

    /* Startラベル */
    auto startLabel = Label::createWithTTF("始める", "fonts/ooama.ttf", 24);
    startLabel->setPosition(Vec2(visibleSize.width*.5, visibleSize.height*.5));
    this->addChild(startLabel,2);

    /* タイトル */
    auto title = Label::createWithTTF("十七歩", "fonts/ooama.ttf", 40);
    title->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - title->getContentSize().height));
    this->addChild(title, 1);

    return true;
}

/* StartButton押下時の処理 */
void FirstMenu::pushStartButton(Ref* pSender) {
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, GameScene::createScene(), Color3B::BLACK));
}



