#include "GameScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameScene::createScene() {
    // お約束
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

// 初期化
bool GameScene::init() {

    // お約束
    if ( !Layer::init() ) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // ラベル設定
    auto label = Label::createWithTTF("Game Scene", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    // 背景画像設定
    auto sprite = Sprite::create("haikei.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    setScale(4, 4);
    this->addChild(sprite, 0);
    
    return true;
}

