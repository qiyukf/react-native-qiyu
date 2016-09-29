//
//  QYSessionViewController.h
//  QYSDK
//
//  Created by towik on 12/21/15.
//  Copyright (c) 2016 Netease. All rights reserved.
//
#import <UIKit/UIKit.h>

@class QYSource;
@class QYCommodityInfo;

/**
 *  客服会话ViewController,必须嵌入到UINavigationcontroller中
 */
@interface QYSessionViewController : UIViewController

/**
 *  会话窗口标题
 */
@property (nonatomic,copy)      NSString    *sessionTitle;

/**
 *  分组Id
 */
@property (nonatomic,assign)    int64_t groupId;

/**
 *  客服Id
 */
@property (nonatomic,assign)    int64_t staffId;

/**
 *  会话窗口来源
 */
@property (nonatomic,strong)    QYSource   *source;

/**
 *  商品信息展示
 */
@property (nonatomic, strong) QYCommodityInfo *commodityInfo;

@end
