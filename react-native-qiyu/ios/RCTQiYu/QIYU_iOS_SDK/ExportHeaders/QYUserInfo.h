//
//  QYUserInfo.h
//  QYSDK
//
//  Created by towik on 1/11/16.
//  Copyright (c) 2016 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 *  个人信息
 */
@interface QYUserInfo : NSObject

/**
 *  个人账号Id
 */
@property (nonatomic,copy)      NSString    *userId;

/**
 *  用户详细信息json
 */
@property (nonatomic,copy)      NSString    *data;

@end
