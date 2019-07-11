//
//  QYSessionViewController.h
//  QYSDK
//
//  Created by towik on 12/21/15.
//  Copyright (c) 2017 Netease. All rights reserved.
//

#import "QYSessionViewController.h"

/**
 *  平台电商专用
 */
@interface QYSessionViewController (POP)

/**
 *  平台电商店铺Id，不是平台电商不用管
 */
@property (nonatomic, copy) NSString *shopId;

/**
 *  会话窗口回调
 */
@property (nonatomic, weak) id<QYSessionViewDelegate> delegate;

@end
