//
//  CGesture.cpp
//  ActionLabel
//
//  Created by xujw on 16/3/15.
//
//

#include "CGesture.h"
#include <time.h>

CGesture::CGesture()
:_isCanTouch(false)
,_tapNum(0)
{}
CGesture::~CGesture()
{}

bool CGesture::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    return true;
}

CGesture* CGesture::createTapGesture(Node*target,GestureCallback callback,int tapsRequired)
{
    CCASSERT(callback && target, "callback or target is null");
    
    auto parent = target->getParent();

    auto gesture = CGesture::create();
    
    auto lis = EventListenerTouchOneByOne::create();
    lis->onTouchBegan = [=](Touch *touch,Event *event)
    {
        auto box = target->getBoundingBox();
        auto pos = touch->getLocation();
        if (parent) {
            pos = parent->convertToNodeSpace(pos);
        }
        if (box.containsPoint(pos))
        {
            gesture->_tapNum ++;
        }
        
        return true;
    };
    lis->onTouchMoved = [=](Touch *touch,Event *event)
    {
        auto startPos = touch->getStartLocation();
        auto curPos = touch->getLocation();
        auto subPos = curPos - startPos;
        if (fabs(subPos.x)>=10 || fabs(subPos.y)>=10)
        {
            gesture->_tapNum = 0;
            gesture->unschedule("GestureTapNumReset");
        }        
    };
    lis->onTouchEnded = [=](Touch *touch,Event *event)
    {
        if (gesture->_tapNum >= tapsRequired)
        {
            auto box = target->getBoundingBox();
            auto pos = touch->getLocation();
            auto parent = target->getParent();
            if (parent) {
                pos = parent->convertToNodeSpace(pos);
            }
            if (box.containsPoint(pos))
            {
                gesture->_tapNum = 0;
                gesture->unschedule("GestureTapNumReset");
                callback(touch);
            }
        }
        gesture->scheduleOnce([=](float dt)
        {
            gesture->_tapNum = 0;
        }, 0.5, "GestureTapNumReset");
    };
    
    gesture->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, target);
    
    return gesture;
}

CGesture* CGesture::createLongPressGesture(Node*target,GestureCallback callback,float delay)
{
    CCASSERT(callback && target, "callback or target is null");
    
    auto parent = target->getParent();

    auto gesture = CGesture::create();
    
    auto lis = EventListenerTouchOneByOne::create();
    lis->onTouchBegan = [=](Touch *touch,Event *event)
    {
        auto box = target->getBoundingBox();
        auto pos = touch->getLocation();
        if (parent) {
            pos = parent->convertToNodeSpace(pos);
        }
        if (box.containsPoint(pos))
        {
            gesture->scheduleOnce([=](float){
                gesture->_isCanTouch = true;
            }, delay, "GestureChangeTouchState");
            return true;
        }
        else
        {
            return false;
        }
    };
    lis->onTouchMoved = [=](Touch *touch,Event *event)
    {
        //长按时滑动算取消
        auto startPos = touch->getStartLocation();
        auto curPos = touch->getLocation();
        auto subPos = curPos - startPos;
        if (fabs(subPos.x)>=10 || fabs(subPos.y)>=10)
        {
            gesture->unschedule("GestureChangeTouchState");
            gesture->_isCanTouch = false;
        }
    };
    lis->onTouchEnded = [=](Touch *touch,Event *event)
    {
        auto box = target->getBoundingBox();
        auto pos = touch->getLocation();
        if (parent) {
            pos = parent->convertToNodeSpace(pos);
        }
        
        if (gesture->_isCanTouch)
        {
            if (box.containsPoint(pos))
            {
                callback(touch);
            }
        }
        else
        {
            gesture->unschedule("GestureChangeTouchState");
        }
        gesture->_isCanTouch = false;
    };
    
    gesture->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, target);
    
    return gesture;
}

CGesture* CGesture::createSwipeGesture(Node*target,SwipeGestureCallback callback)
{
    CCASSERT(callback && target, "callback or target is null");

    auto parent = target->getParent();
    auto gesture = CGesture::create();
    
    auto lis = EventListenerTouchOneByOne::create();
    lis->onTouchBegan = [=](Touch *touch,Event *event)
    {
        auto pos = touch->getLocation();
        auto box = target->getBoundingBox();
        if (parent) {
            pos = parent->convertToNodeSpace(pos);
        }
        if (box.containsPoint(pos))
        {
            gesture->_isCanTouch = true;
        }
        else{
            gesture->_isCanTouch = false;
        }
        return gesture->_isCanTouch;
    };
    lis->onTouchMoved = [=](Touch *touch,Event *event){};
    lis->onTouchEnded = [=](Touch *touch,Event *event)
    {
        auto pos = touch->getLocation();
        auto box = target->getBoundingBox();
        if (parent) {
            pos = parent->convertToNodeSpace(pos);
        }
        //起始点都在target范围内才响应
        if (!gesture->_isCanTouch || !box.containsPoint(pos))
        {
            gesture->_isCanTouch = false;
            return ;
        }
        
        auto startPos = touch->getStartLocation();
        auto curPos = touch->getLocation();
        auto subPos = curPos - startPos;
        
        if (fabs(subPos.x) > fabs(subPos.y))
        {
            //左右移动
            if (subPos.x > SHAKE_LENGTH)
            {
                //向右移动
                callback(touch,kDirectRight);
            }
            else if (subPos.x < -SHAKE_LENGTH)
            {
                //向左移动
                callback(touch,kDirectLeft);
            }
        }
        else
        {
            if (subPos.y > SHAKE_LENGTH)
            {
                //向上移动
                callback(touch,kDirectUp);
            }
            else if (subPos.y < -SHAKE_LENGTH)
            {
                //向下移动
                callback(touch,kDirectDown);
            }
        }
    };
    gesture->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, gesture);
    return gesture;
}

CGesture* CGesture::createPanGestrue(Node*target,GestureCallback callback)
{
    CCASSERT(callback && target, "callback or target is null");

    auto parent = target->getParent();
    
    auto gesture = CGesture::create();
    
    auto lis = EventListenerTouchOneByOne::create();
    lis->onTouchBegan = [=](Touch *touch,Event *event)
    {
        auto box = target->getBoundingBox();
        auto pos = touch->getLocation();
        if (parent) {
            pos = parent->convertToNodeSpace(pos);
        }
        if (box.containsPoint(pos))
        {
            gesture->_isCanTouch = true;
        }
        return true;
    };
    lis->onTouchMoved = [=](Touch *touch,Event *event)
    {
        if (gesture->_isCanTouch)
        {
            callback(touch);
        }
    };
    lis->onTouchEnded = [=](Touch *touch,Event *event)
    {
        gesture->_isCanTouch = false;
    };
    gesture->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, target);
    return gesture;
}





