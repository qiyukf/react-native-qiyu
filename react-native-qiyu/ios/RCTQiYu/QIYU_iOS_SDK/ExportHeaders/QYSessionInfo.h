//
//  QYSessionInfo.h
//  YSFSDK
//
//  Created by JackyYu on 16/12/2.
//  Copyright (c) 2017 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QYMessageInfo.h"

/**
 *  会话状态类型
 */
typedef NS_ENUM(NSInteger, QYSessionStatus) {
    QYSessionStatusNone,        //无
    QYSessionStatusWaiting,     //排队中
    QYSessionStatusInSession    //会话中
};

/**
 *  会话列表中的会话详情信息
 */
@interface QYSessionInfo : NSObject

/**
 *  会话最后一条消息文本
 */
@property (nonatomic, copy) NSString *lastMessageText;

/**
 *  消息类型
 */
@property (nonatomic, assign) QYMessageType lastMessageType;

/**
 *  会话未读数
 */
@property (nonatomic, assign) NSInteger unreadCount;

/**
 *  会话状态
 */
@property (nonatomic, assign) QYSessionStatus status;

/**
 *  会话最后一条消息的时间
 */
@property (nonatomic, assign) NSTimeInterval lastMessageTimeStamp;

/**
 *  是否存在垃圾词汇
 */
@property (nonatomic, assign) BOOL hasTrashWords;

@end
