//
//  QYCustomEvent.h
//  YSFSDK
//
//  Created by liaosipei on 2018/11/28.
//  Copyright © 2018 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  可自行扩展事件名称，在onCatchEvent:回调中通过eventName判断事件
 */
extern NSString * const QYCustomEventTapAvatar;
extern NSString * const QYCustomEventLongPressCell;


@class QYCustomMessage;

/**
 *  消息事件
 */
@interface QYCustomEvent : NSObject

/**
 *  事件名称
 */
@property (nonatomic, copy) NSString *eventName;

/**
 *  消息
 */
@property (nonatomic, strong) QYCustomMessage *message;

/**
 *  扩展数据，可传递任意想传递的数据
 */
@property (nonatomic, strong) id data;

@end
