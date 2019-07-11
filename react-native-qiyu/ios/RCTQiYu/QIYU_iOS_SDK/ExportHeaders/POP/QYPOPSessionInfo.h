//
//  QYSessionInfo.h
//  YSFSDK
//
//  Created by JackyYu on 16/12/2.
//  Copyright (c) 2017 Netease. All rights reserved.
//

#import "QYSessionInfo.h"

/**
 *  平台电商专用；会话列表中的会话详情信息
 */
@interface QYSessionInfo (POP)

/**
 *  会话ID，可以是商铺ID等
 */
@property (nonatomic, copy) NSString *shopId;

/**
 *  会话头像URL
 */
@property (nonatomic, copy) NSString *avatarImageUrlString;

/**
 *  会话名称
 */
@property (nonatomic, copy) NSString *sessionName;

@end
