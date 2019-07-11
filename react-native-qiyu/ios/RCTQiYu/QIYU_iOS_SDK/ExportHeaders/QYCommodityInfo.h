//
//  QYCommodityInfo.h
//  QYSDK
//
//  Created by JackyYu on 16/5/26.
//  Copyright (c) 2017 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  QYCommodityTag：自定义商品信息卡片按钮信息
 */
@interface QYCommodityTag : NSObject

@property (nonatomic, copy) NSString *label;
@property (nonatomic, copy) NSString *url;
@property (nonatomic, copy) NSString *focusIframe;
@property (nonatomic, copy) NSString *data;

@end


/**
 *  商品信息类：QYCommodityInfo
 */
@interface QYCommodityInfo : NSObject

/**
 *  商品标题，字符数要求小于100
 */
@property (nonatomic, copy) NSString *title;

/**
 *  商品描述，字符数要求小于300
 */
@property (nonatomic, copy) NSString *desc;

/**
 *  商品图片url，字符数要求小于1000
 */
@property (nonatomic, copy) NSString *pictureUrlString;

/**
 *  跳转url，字符数要求小于1000
 */
@property (nonatomic, copy) NSString *urlString;

/**
 *  备注信息，可以显示价格，订单号等，字符数要求小于100
 */
@property (nonatomic, copy) NSString *note;

/**
 *  发送时是否要在用户端隐藏，YES为显示，NO为隐藏，默认为NO
 */
@property (nonatomic, assign) BOOL show;

/**
 *  自定义商品信息按钮数组，最多显示三个按钮;
 */
@property (nonatomic, copy) NSArray<QYCommodityTag *> *tagsArray;

/**
 *  自定义商品信息按钮数组，最多显示三个按钮;NSString *类型，跟上面的数组类型二选一
 */
@property (nonatomic, copy) NSString *tagsString;

/**
 *  是否自定义，YES代表是，NO代表否，默认NO。
 *  自定义的话，只有pictureUrlString、urlString有效，只显示一张图片 (v4.4.0)
 */
@property (nonatomic, assign) BOOL isCustom;

/**
 *  是否由访客手动发送，YES代表是，NO代表否，默认NO (v4.4.0)
 */
@property (nonatomic, assign) BOOL sendByUser;

/**
 *  发送按钮文案 (v4.4.0)
 */
@property (nonatomic, copy) NSString *actionText;

/**
 *  发送按钮文案颜色 (v4.4.0)
 */
@property (nonatomic, strong) UIColor *actionTextColor;

/**
 *  一般用户不需要填这个字段，这个字段仅供特定用户使用
 */
@property (nonatomic, copy) NSString *ext;

@end


/**
 *  自定义商品信息类：QYSelectedCommodityInfo，用于机器人模式下发送商品/订单等场景
 */
@interface QYSelectedCommodityInfo : NSObject

@property (nonatomic, copy) NSString *target;
@property (nonatomic, copy) NSString *params;
@property (nonatomic, copy) NSString *p_status;
@property (nonatomic, copy) NSString *p_img;
@property (nonatomic, copy) NSString *p_name;
@property (nonatomic, copy) NSString *p_price;
@property (nonatomic, copy) NSString *p_count;
@property (nonatomic, copy) NSString *p_stock;
@property (nonatomic, copy) NSString *p_action;
@property (nonatomic, copy) NSString *p_url;
@property (nonatomic, copy) NSString *p_userData;

@end
