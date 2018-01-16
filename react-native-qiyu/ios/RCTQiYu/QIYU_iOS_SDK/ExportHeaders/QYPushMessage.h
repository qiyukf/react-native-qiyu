//
//  QYPushMessage.h
//  QYSDK
//
//  Created by towik on 9/10/16.
//  Copyright (c) 2017 Netease. All rights reserved.
//

/**
 *  推送消息定义
 */
@interface QYPushMessage : NSObject

/**
 *  消息内容
 */
@property (nonatomic, copy) NSString *text;

/**
 *  消息接收时间
 */
@property (nonatomic, assign) NSTimeInterval time;

@end



