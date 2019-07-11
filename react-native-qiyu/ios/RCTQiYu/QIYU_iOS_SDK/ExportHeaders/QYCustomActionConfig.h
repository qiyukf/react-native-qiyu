//
//  QYCustomActionConfig.h
//  QYSDK
//
//  Created by towik on 7/28/16.
//  Copyright (c) 2017 Netease. All rights reserved.
//

/**
 *  本类提供了所有自定义行为的接口;每个接口对应一个自定义行为的处理，如果设置了，则使用设置的处理，如果不设置，则采用默认处理
 */

@class QYAction;
@class QYSelectedCommodityInfo;

/**
 *  退出排队结果类型
 */
typedef NS_ENUM(NSInteger, QuitWaitingType) {
    QuitWaitingTypeNone,     //当前不是在排队状态
    QuitWaitingTypeContinue, //继续排队
    QuitWaitingTypeQuit,     //退出排队
    QuitWaitingTypeCancel,   //取消操作
};

/**
 *  action事件回调
 */
typedef void (^QYActionBlock)(QYAction *action);

/**
 *  链接点击事件回调
 */
typedef void (^QYLinkClickBlock)(NSString *linkAddress);

/**
 *  bot点击事件回调
 */
typedef void (^QYBotClickBlock)(NSString *target, NSString *params);

/**
 *  退出排队回调
 */
typedef void (^QYQuitWaitingBlock)(QuitWaitingType quitType);

/**
 *  显示bot自定义信息回调
 */
typedef void (^QYShowBotCustomInfoBlock)(NSArray *array);

/**
 *  bot商品卡片按钮点击事件回调
 */
typedef void (^QYSelectedCommodityActionBlock)(QYSelectedCommodityInfo *commodityInfo);

/**
 *  扩展视图点击回调
 *
 *  @param extInfo 附带信息
 */
typedef void (^QYExtraViewClickBlock)(NSString *extInfo);

/**
 *  系统消息点击回调
 *
 *  @param message 消息对象
 */
typedef void (^QYSystemNotificationClickBlock)(id message);

/**
 *  所有消息内事件点击回调
 *
 *  @param eventName 事件名称
 *  @param eventData 数据
 *  @param messageId 消息ID
 */
typedef void (^QYEventBlock)(NSString *eventName, NSString *eventData, NSString *messageId);


/**
 *  自定义行为配置类：QYCustomActionConfig，单例模式
 */
@interface QYCustomActionConfig : NSObject

+ (instancetype)sharedInstance;

/**
 *  action事件
 */
@property (nonatomic, copy) QYActionBlock actionBlock;

/**
 *  所有消息中的链接（自定义商品消息、文本消息、机器人答案消息）的回调处理
 */
@property (nonatomic, copy) QYLinkClickBlock linkClickBlock;

/**
 *  bot相关点击
 */
@property (nonatomic, copy) QYBotClickBlock botClick;

/**
 *  推送消息相关点击
 */
@property (nonatomic, copy) QYLinkClickBlock pushMessageClick;

/**
 *  显示bot自定义信息
 */
@property (nonatomic, copy) QYShowBotCustomInfoBlock showBotCustomInfoBlock;

/**
 *  bot商品卡片按钮点击事件
 */
@property (nonatomic, copy) QYSelectedCommodityActionBlock commodityActionBlock;

/**
 *  扩展视图点击
 */
@property (nonatomic, copy) QYExtraViewClickBlock extraClickBlock;

/**
 *  系统消息点击
 */
@property (nonatomic, copy) QYSystemNotificationClickBlock notificationClickBlock;

/**
 *  消息内点击
 */
@property (nonatomic, copy) QYEventBlock eventClickBlock;

/**
 *  设置录制或者播放语音完成以后是否自动deactivate AVAudioSession
 *
 *  @param deactivate 是否deactivate，默认为YES
 */
- (void)setDeactivateAudioSessionAfterComplete:(BOOL)deactivate;

/**
 *  显示退出排队提示
 *
 *  @param quitWaitingBlock 选择结果回调
 */
- (void)showQuitWaiting:(QYQuitWaitingBlock)quitWaitingBlock;

@end



