#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "UtilsLabel.h"
USING_NS_CC;
#include "CGesture.h"

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    auto label = Label::createWithSystemFont("10,000", "arial-boldmt", 50);
    label->setPosition(500,300);
    this->addChild(label);
    
//    UtilsLabel::runLabelValueTo(label, 99999999, 5,0);
    
    UtilsLabel::runLabelValueToValue(label, 100, 99999, 5);

    auto bg = Sprite::create("icon_camera.jpg");
    bg->setPosition(200,200);
    this->addChild(bg);
    
    auto tap = CGesture::createTapGesture(bg,[=](Touch*touch){
    
        CCLOG("tap...");
    },1);
    this->addChild(tap);

    auto longPress = CGesture::createLongPressGesture(bg,[=](Touch*touch)
    {
        CCLOG("long pressed call...");
    });
    this->addChild(longPress);

    auto swipe = CGesture::createSwipeGesture(bg,[=](Touch *touch,GestureDirection dir)
    {
        switch (dir) {
            case kDirectUp:
                CCLOG("swipe up...");
                break;
            case kDirectDown:
                CCLOG("swipe down...");
                break;
            case kDirectLeft:
                CCLOG("swipe left...");
                break;
            case kDirectRight:
                CCLOG("swipe right");
                break;
            default:
                break;
        }
    });
    this->addChild(swipe);
    
    auto pan = CGesture::createPanGestrue(bg,[=](Touch *touch)
    {
        bg->setPosition(bg->getPosition()+touch->getDelta());
    });
    this->addChild(pan);
    
    return true;
}
