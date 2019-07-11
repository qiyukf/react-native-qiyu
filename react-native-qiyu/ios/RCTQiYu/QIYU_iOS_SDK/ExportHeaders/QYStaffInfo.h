//
//  QYStaffInfo.h
//  YSFSDK
//
//  Created by liaosipei on 2018/10/12.
//  Copyright © 2018年 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  人工客服信息
 */
@interface QYStaffInfo : NSObject

/**
 *  客服ID，限制20字符
 */
@property (nonatomic, copy) NSString *staffId;

/**
 *  客服昵称，限制20字符
 */
@property (nonatomic, copy) NSString *nickName;

/**
 *  客服头像URL
 */
@property (nonatomic, copy) NSString *iconURL;

/**
 *  接入提示，限制50字符
 */
@property (nonatomic, copy) NSString *accessTip;

/**
 *  客服信息描述
 */
@property (nonatomic, copy) NSString *infoDesc;

@end

