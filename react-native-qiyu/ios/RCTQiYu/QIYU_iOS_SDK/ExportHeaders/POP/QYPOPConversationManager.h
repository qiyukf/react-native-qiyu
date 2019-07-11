//
//  QYConversationManager.h
//  QYSDK
//
//  Created by towik on 12/21/15.
//  Copyright (c) 2017 Netease. All rights reserved.
//

#import "QYConversationManager.h"

/**
 *  会话委托
 */
@protocol QYPOPConversationManagerDelegate <NSObject>

/**
 *  会话列表变化
 */
- (void)onSessionListChanged;

/**
 *  收到消息
 *
 *  @param message 消息信息
 */
- (void)onReceiveMessage:(QYMessageInfo *)message;

@end

/**
 *  平台电商专用;会话管理类委托
 */
@interface QYConversationManager (POP)

/**
 *  清空未读数
 *
 *  @param shopId 商铺ID
 */
- (void)clearUnreadCount:(NSString *)shopId;

/**
 *  删除会话列表中的会话
 *
 *  @param shopId 商铺ID
 *  @param isDelete 是否删除消息记录，YES删除，NO不删除
 */
- (void)deleteRecentSessionByShopId:(NSString *)shopId deleteMessages:(BOOL)isDelete;

@end
