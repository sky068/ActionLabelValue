//
//  UtilsLabel.hpp
//  ActionLabel
//
//  Created by xujw on 16/3/7.
//
//

#ifndef UtilsLabel_h
#define UtilsLabel_h

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

typedef enum labelFormat
{
    kNormal = 0,
    kSeparator = 1  //有逗号分隔，比如100,200,300
}kLabelFormat;

class UtilsLabel
{
public:
    //maxWidth=0表示不对label进行缩放
    static void setLabelValueWithFormat(Label*label,long long value,float maxWidth=0,kLabelFormat format =kNormal);
    
    static void runLabelValueTo(Label*label,long long toValue,float duration,float width=0,kLabelFormat format=kNormal);
    
    static void runLabelValueToValue(Label*label,long long startValue,long long toValue,float duration,float width=0,kLabelFormat format=kNormal);

};

#endif /* UtilsLabel_h */
