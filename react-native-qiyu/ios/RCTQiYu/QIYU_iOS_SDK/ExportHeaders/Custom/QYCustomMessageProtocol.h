//
//  QYCustomMessageProtocol.h
//  QYSDK
//
//  Created by Netease on 2018/11/23.
//  Copyright © 2018 Netease. All rights reserved.
//

@class QYCustomMessage;
@class QYCustomEvent;

/**
 *  自定义消息部分事件 委托协议
 */
@protocol QYCustomMessageDelegate <NSObject>

@optional
/**
 *  追加消息的回调，此时消息已持久化（若需），还未刷新界面
 */
- (void)onAddMessageBeforeReload:(QYCustomMessage *)message;

/**
 *  插入消息的回调，此时消息已持久化（若需），还未刷新界面
 */
- (void)onInsertMessageBeforeReload:(QYCustomMessage *)message;

/**
 *  更新消息的回调，此时消息已持久化（若需），还未刷新界面
 */
- (void)onUpdateMessageBeforeReload:(QYCustomMessage *)message;

/**
 *  删除消息的回调，此时消息已持久化（若需），还未刷新界面
 */
- (void)onDeleteMessageBeforeReload:(QYCustomMessage *)message;

@end


/**
 *  自定义视图点击事件 委托协议
 */
@protocol QYCustomContentViewDelegate <NSObject>

@optional
/**
 *  自定义事件，通过QYCustomContentView的delegate去调用onCatchEvent:事件
 *  若事件涉及到更新消息及视图则尽量使用onCatchEvent:抛出，若未涉及消息及视图更新，可直接响应事件，无需使用该方法抛出
 */
- (void)onCatchEvent:(QYCustomEvent *)event;

/**
 *  头像点击事件
 */
- (void)onTapAvatar:(QYCustomEvent *)event;

/**
 *  消息体长按事件
 */
- (void)onLongPressCell:(QYCustomEvent *)event;

@end
