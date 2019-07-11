//
//  QYCustomMessage.h
//  QYSDK
//
//  Created by Netease on 2018/11/22.
//  Copyright © 2018 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  消息来源类型，默认QYCustomMessageSourceTypeNone
 */
typedef NS_ENUM(NSInteger, QYCustomMessageSourceType) {
    QYCustomMessageSourceTypeNone = 0,  //无，不显示头像
    QYCustomMessageSourceTypeSend,      //发送方，显示访客头像
    QYCustomMessageSourceTypeReceive,   //接收方，显示客服头像
};


/**
 *  QYCustomMessage序列化协议
 */
@protocol QYCustomMessageCoding <NSObject>

@optional
/**
 *  缩略消息，用以显示在会话列表
 */
- (NSString *)thumbText;

/**
 *  消息数据序列化，用于数据库存储
 */
- (NSDictionary *)encodeMessage;

/**
 *  消息数据解码
 */
- (void)decodeMessage:(NSDictionary *)content;

/**
 *  消息来源
 */
- (QYCustomMessageSourceType)messageSourceType;

@end


/**
 *  自定义消息基类
 *  使用方法：针对需自定义的消息，写子类继承QYCustomMessage，扩展所需属性，并实现QYCustomMessageCoding协议
 */
@interface QYCustomMessage : NSObject <QYCustomMessageCoding>

/**
 *  消息唯一ID
 */
@property (nonatomic, copy, readonly) NSString *messageId;

@end
