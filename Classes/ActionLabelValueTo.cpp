//
//  ActionLabel.cpp
//  ActionLabel
//
//  Created by xujw on 16/3/7.
//
//

#include "ActionLabelValueTo.h"

ActionLabelValueTo::ActionLabelValueTo()
:_startValue(0)
,_endValue(0)
,_delayValue(0)
,_maxWidth(0)
,_labelFormat(kNormal)
{}
ActionLabelValueTo::~ActionLabelValueTo()
{}

ActionLabelValueTo* ActionLabelValueTo::create(float duration, long long startValue, long long endValue,float maxValue,kLabelFormat format)
{
    auto lvt = new(std::nothrow) ActionLabelValueTo();
    if (lvt && lvt->initWithDuration(duration, startValue, endValue,maxValue,format ))
    {
        lvt->autorelease();
        return lvt;
    }
    CC_SAFE_DELETE(lvt);
    return nullptr;
}

bool ActionLabelValueTo::initWithDuration(float duration, long long startValue, long long endValue,float maxWidth,kLabelFormat format)
{
    if (!ActionInterval::initWithDuration(duration))
    {
        return false;
    }
    
    _startValue = startValue;
    _endValue = endValue;
    _labelFormat = format;
    _maxWidth = maxWidth;
    
    return true;
}
void ActionLabelValueTo::startWithTarget(cocos2d::Node *target)
{
    ActionInterval::startWithTarget(target);
    _delayValue = _endValue - _startValue;
}
//time is 0 to 1
void ActionLabelValueTo::update(float time)
{
    if (getTarget())
    {
        Label *label = dynamic_cast<Label*>(getTarget());
        CCASSERT(label, "target must be a Label!");
        long long v = (long long)(_delayValue * (double)time);
        long long curValue = _startValue + v;
        
        //简易单独使用动作可以用下面代码
//        std::string strValue = StringUtils::format("%lld",curValue);
//        label->setString(strValue);
        
        UtilsLabel::setLabelValueWithFormat(label, curValue,_maxWidth,_labelFormat);
    }
}






