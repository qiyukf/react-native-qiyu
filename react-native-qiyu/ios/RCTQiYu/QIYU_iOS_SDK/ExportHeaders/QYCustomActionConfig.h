//
//  QYCustomActionConfig.h
//  QYSDK
//
//  Created by towik on 7/28/16.
//  Copyright (c) 2017 Netease. All rights reserved.
//

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
 *  提供了所有自定义行为的接口;每个接口对应一个自定义行为的处理，如果设置了，则使用设置的处理，如果不设置，则采用默认处理
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
 *  是否退出排队回调
 */
typedef void (^QYShowQuitBlock)(QYQuitWaitingBlock block);


/**
 *  自定义行为配置类
 */
@interface QYCustomActionConfig : NSObject

+ (instancetype)sharedInstance;

/**
 *  所有消息中的链接（自定义商品消息、文本消息、机器人答案消息）的回调处理
 */
@property (nonatomic, copy) QYLinkClickBlock linkClickBlock;

/**
 *  bot相关点击
 */
@property (nonatomic, copy) QYBotClickBlock botClick;

@property (nonatomic, copy) QYShowQuitBlock showQuitBlock;

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



