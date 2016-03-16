//
//  CGesture.h
//  ActionLabel
//
//  Created by xujw on 16/3/15.

/*  手势识别 仿iphone  简单长按 点击(双击等) 滑动 拖动等。
 *  使用方法：
 *  auto gesture = CGesture::createTapGesture(target,callback,taps);
 *  this->addChild(gestrue)
 */

#ifndef CGesture_h
#define CGesture_h

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

typedef enum gestureDirection
{
    kDirectUp = 0,
    kDirectDown = 1,
    kDirectLeft = 2,
    kDirectRight = 3
}GestureDirection;

typedef std::function<void(Touch*)> GestureCallback;
typedef std::function<void(Touch*,GestureDirection)> SwipeGestureCallback;

#define SHAKE_LENGTH 100

class CGesture:public Layer
{
private:
    bool _isCanTouch;
    int _tapNum;
public:
    CGesture();
    ~CGesture();
    bool init();
    CREATE_FUNC(CGesture);
public:
    //点击
    static CGesture* createTapGesture(Node*target,GestureCallback callback,int tapsRequired=1);
    //长按
    static CGesture* createLongPressGesture(Node*target,GestureCallback callback,float delay = 1.0f);
    //滑动
    static CGesture* createSwipeGesture(Node*target,SwipeGestureCallback callback);
    //拖动
    static CGesture* createPanGestrue(Node*target,GestureCallback callback);
};

#endif /* CGesture_h */
