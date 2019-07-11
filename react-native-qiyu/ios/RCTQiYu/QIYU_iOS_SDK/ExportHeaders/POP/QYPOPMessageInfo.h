//
//  QYPOPMessageInfo.h
//  QYSDK
//
//  Created by towik on 12/21/15.
//  Copyright (c) 2017 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  消息信息
 */
@interface QYMessageInfo (POP)

/**
 *  会话ID，可以是商铺ID等
 */
@property (nonatomic, copy) NSString *shopId;

/**
 *  会话头像URL
 */
@property (nonatomic, copy) NSString *avatarImageUrlString;

/**
 *  发送者
 */
@property (nonatomic, copy) NSString *sender;

@end

