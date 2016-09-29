//
//  QYConversationManager.h
//  QYSDK
//
//  Created by towik on 12/21/15.
//  Copyright (c) 2016 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 *  会话委托
 */
@protocol QYConversationManagerDelegate <NSObject>

/**
 *  会话未读数变化
 *
 *  @param count 未读数
 */
- (void)onUnreadCountChanged:(NSInteger)count;
@end


/**
 *  会话管理类委托
 */
@protocol YSFConversationManager <NSObject>

/**
 *  所有的未读数
 *
 *  @return 未读数
 */
- (NSInteger)allUnreadCount;

/**
 *  设置会话委托
 *
 *  @param delegate 会话委托
 */
- (void)setDelegate:(id<QYConversationManagerDelegate>)delegate;
@end
