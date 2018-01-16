//
//  QYPOPMessageInfo.h
//  YSFSDK
//
//  Created by towik on 16/12/29.
//  Copyright (c) 2017 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  消息类型
 */
typedef NS_ENUM(NSInteger, QYMessageType) {
    QYMessageTypeText,      //文本
    QYMessageTypeImage,     //图片
    QYMessageTypeAudio,     //语音
    QYMessageTypeCustom     //自定义
};

/**
 *  消息
 */
@interface QYMessageInfo : NSObject

/**
 *  消息文本
 */
@property (nonatomic, copy) NSString *text;

/**
 *  消息类型
 */
@property (nonatomic, assign) QYMessageType type;

/**
 *  消息时间
 */
@property (nonatomic, assign) NSTimeInterval timeStamp;


@end
