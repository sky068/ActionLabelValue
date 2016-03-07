//
//  UtilsLabel.cpp
//  ActionLabel
//
//  Created by xujw on 16/3/7.
//
//

#include "UtilsLabel.h"
#include "ActionLabelValueTo.h"

void UtilsLabel::setLabelValueWithFormat(cocos2d::Label *label, long long value, float maxWidth,kLabelFormat format)
{
    std::string strValue = StringUtils::format("%lld",value);
    if (format == kSeparator)
    {
        //需要千位分隔符
        if (strValue.length() > 3)
        {
            int count = strValue.length() / 3;
            if (strValue.length() % 3 == 0)
            {
                count = count - 1;
            }
            for (int i=0; i<count; i++)
            {
                strValue.insert(strValue.length()-((i+1)*3+i), ",");
            }
        }
        label->setString(strValue);
    }
    else
    {
        label->setString(StringUtils::format("%lld",value));
    }
    
    //需要缩放
    if (maxWidth > 0)
    {
        float s = maxWidth/label->getContentSize().width;
        if (s<1.0)
        {
            label->setScale(s);
        }
    }
    else
    {
        label->setScale(1.0f);
    }
}

void UtilsLabel::runLabelValueTo(cocos2d::Label *label, long long toValue, float duration, float width, kLabelFormat format)
{
    label -> stopAllActions();
    long long startValue = 0;
    if (format == kSeparator)
    {
        //当前值可能是有逗号分隔的，将233.233.233转为233233233
        std::string str = label->getString();
        int len = str.length();
        std::string strVlaue = "";
        for (int i=0; i<len; i++)
        {
            if (str.at(i) != ',')
            {
                strVlaue += str.at(i);
            }
        }
        startValue = atoll(strVlaue.c_str());
    }
    else
    {
        startValue = atoll(label->getString().c_str());
    }
    
    if (duration <= 0)
    {
        setLabelValueWithFormat(label, toValue,width,format);
    }
    else
    {
        label->runAction(ActionLabelValueTo::create(duration, startValue, toValue,width,format));
    }
}

void UtilsLabel::runLabelValueToValue(Label*label,long long startValue,long long toValue,float duration,float width,kLabelFormat format)
{
    if (duration <= 0)
    {
        setLabelValueWithFormat(label, toValue,width,format);
    }
    else
    {
        label->runAction(ActionLabelValueTo::create(duration, startValue, toValue,width,format));
    }
}










