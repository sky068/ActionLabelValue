//
//  ActionLabel.hpp
//  ActionLabel
//
//  Created by xujw on 16/3/7.
//
//  当label数值是数字时进行滚动效果，比如从1滚动到100

#ifndef ActionLabel_h
#define ActionLabel_h

#include <stdio.h>
#include "cocos2d.h"
#include "UtilsLabel.h"
USING_NS_CC;

class ActionLabelValueTo:public ActionInterval
{
public:
    ActionLabelValueTo();
    ~ActionLabelValueTo();
    static ActionLabelValueTo* create(float duration,long long startValue,long long endValue,float width=0,kLabelFormat format=kNormal);
    bool initWithDuration(float duration,long long startValue,long long endValue,float width,kLabelFormat format);
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

private:
    long long _startValue;
    long long _endValue;
    long long _delayValue;
    float _maxWidth;
    kLabelFormat _labelFormat;
};


#endif /* ActionLabel_h */
