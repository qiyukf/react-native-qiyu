//
//  QYConversationManager.h
//  QYSDK
//
//  Created by towik on 12/21/15.
//  Copyright (c) 2017 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>

@class QYMessageInfo;
@class QYSessionInfo;


/**
 *  会话委托
 */
@protocol QYConversationManagerDelegate <NSObject>

@optional
/**
 *  会话未读数变化
 *
 *  @param count 未读数
 */
- (void)onUnreadCountChanged:(NSInteger)count;

/**
 *  会话列表变化；非平台电商用户，只有一个会话项，平台电商用户，有多个会话项
 */
- (void)onSessionListChanged:(NSArray<QYSessionInfo*> *)sessionList;

/**
 *  收到消息
 */
- (void)onReceiveMessage:(QYMessageInfo *)message;

@end

/**
 *  会话管理类
 */
@interface QYConversationManager : NSObject
    
/**
 *  所有的未读数
 *
 *  @return 未读数
 */
- (NSInteger)allUnreadCount;

/**
 *  清空未读数
 *
 */
- (void)clearUnreadCount;

/**
 *  获取所有会话的列表；非平台电商用户，只有一个会话项，平台电商用户，有多个会话项
 *
 *  @return 包含SessionInfo的数组
 */
- (NSArray<QYSessionInfo*> *)getSessionList;

/**
 *  设置会话委托
 *
 *  @param delegate 会话委托
 */
- (void)setDelegate:(id<QYConversationManagerDelegate>)delegate;

@end

