//
//  QYPushMessage.h
//  QYSDK
//
//  Created by towik on 9/10/16.
//  Copyright (c) 2017 Netease. All rights reserved.
//

/**
 *  推送消息类型
 */
typedef NS_ENUM(NSInteger, QYPushMessageType) {
    QYPushMessageTypeText,
    QYPushMessageTypeRichText,
    QYPushMessageTypeImage,
};

/**
 *  推送消息定义
 */
@interface QYPushMessage : NSObject

/**
 *  消息类型
 */
@property (nonatomic, assign) QYPushMessageType type;

/**
 *  发送方头像图片url
 */
@property (nonatomic, copy) NSString *headImageUrl;

/**
 *  按钮文本
 */
@property (nonatomic, copy) NSString *actionText;

/**
 *  按钮url
 */
@property (nonatomic, copy) NSString *actionUrl;

/**
 *  消息内容 文本
 */
@property (nonatomic, copy) NSString *text;

/**
 *  消息内容 富文本
 */
@property (nonatomic, copy) NSString *richText;

/**
 *  消息内容 图片
 */
@property (nonatomic, copy) NSString *imageUrl;

/**
 *  消息接收时间
 */
@property (nonatomic, assign) NSTimeInterval time;

@end



