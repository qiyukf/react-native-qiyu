//
//  QYSDK.h
//  QYSDK
//
//  version 4.9.0
//
//  Created by towik on 12/21/15.
//  Copyright (c) 2017 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QYHeaders.h"

/**
 *  完成回调
 */
typedef void(^QYCompletionBlock)(BOOL success);

/**
 *  完成结果回调
 */
typedef void(^QYCompletionWithResultBlock)(BOOL isSuccess);

/**
 *  推送消息回调
 */
typedef void(^QYPushMessageBlock)(QYPushMessage *pushMessage);

/**
 *  清理文件缓存回调
 */
typedef void(^QYCleanResourceCacheCompleteBlock)(NSError *error);


/**
 *  QYSDK：单例模式，所有SDK接口都从此类获得
 */
@interface QYSDK : NSObject

/**
 *  返回 SDK 单例
 *
 *  @return SDK 单例
 */
+ (instancetype)sharedSDK;

/**
 *  注册SDK
 *
 *  @param appKey  对应管理后台分配的appkey
 *  @param appName  对应管理后台添加一个App时填写的App名称 (就是SDK1.0.0版本的cerName,参数名变动)
 */
- (void)registerAppId:(NSString *)appKey appName:(NSString *)appName;

/**
 *  返回客服聊天ViewController，必须嵌入至UINavigationController中
 *  须保证全局只有一个sessionViewController实例，退出后能够正确释放实例
 *
 *  @return 会话ViewController
 */
- (QYSessionViewController *)sessionViewController;

/**
 *  返回自定义UI类,通过此类可以设置sessionViewController内的界面效果
 *
 *  @return 自定义UI类
 */
- (QYCustomUIConfig *)customUIConfig;

/**
 *  返回自定义事件处理类,通过此类可以设置sessionViewController内的事件处理
 *
 *  @return 自定义事件处理类
 */
- (QYCustomActionConfig *)customActionConfig;

/**
 *  返回会话管理类
 *
 *  @return 会话管理类
 */
- (QYConversationManager *)conversationManager;

/**
 *  更新推送token
 *
 *  @param token 推送token
 */
- (void)updateApnsToken:(NSData *)token;

/**
 *  注销当前账号。用户帐号注销时需要调用此函数；切换账号包含注销和登录过程，在注销阶段也要调用此函数
 *
 *  @param completion 完成回调
 */
- (void)logout:(QYCompletionBlock)completion;

/**
 *  设置个人信息。用户帐号登录成功之后，调用此函数
 *
 *  @param userInfo 个人信息
 */
- (void)setUserInfo:(QYUserInfo *)userInfo;

/**
 *  设置authToken
 */
- (void)setAuthToken:(NSString *)authToken;

/**
 *  设置个人信息，带authToken校验。用户帐号登录成功之后，调用此函数
 *
 *  @param userInfo 个人信息
 *  @param block authToken校验结果的回调
 */
- (void)setUserInfo:(QYUserInfo *)userInfo authTokenVerificationResultBlock:(QYCompletionWithResultBlock)block;

/**
 *  获取推送消息
 *
 *  @param messageId 消息id
 */
- (void)getPushMessage:(NSString *)messageId;

/**
 *  注册推送消息通知回调
 *
 *  @param block 收到消息的回调
 */
- (void)registerPushMessageNotification:(QYPushMessageBlock)block;

/**
 *  返回AppKey
 *
 *  @return appKey
 */
- (NSString *)appKey;

/**
 *  清理接收文件缓存
 *  @param completeBlock 清理缓存完成block
 */
- (void)cleanResourceCacheWithBlock:(QYCleanResourceCacheCompleteBlock)completeBlock;

/**
 *  访问轨迹
 *  @param title 标题
 *  @param enterOrOut 进入还是退出
 */
- (void)trackHistory:(NSString *)title enterOrOut:(BOOL)enterOrOut key:(NSString *)key;

/**
 *  行为轨迹
 *  @param title 标题
 *  @param description 具体信息，以key-value表示信息对，例如key为“商品价格”，value为“999”
 */
- (void)trackHistory:(NSString *)title description:(NSDictionary *)description key:(NSString *)key;

/**
 *  获取七鱼日志文件路径
 *
 *  @return 日志文件路径
 */
- (NSString *)qiyuLogPath;


#pragma mark - Deprecated
///**
// *  已废弃
// *  追踪用户浏览信息;暂时客服端还没有入口可以查看这部分信息
// *  @param urlString  浏览url
// *  @param attributes 附加信息
// */
//- (void)trackHistory:(NSString *)urlString withAttributes:(NSDictionary *)attributes;

///**
// *  已废弃，使用setUserInfo替代
// *  设置userInfo.userId即可，userInfo.data忽略
// *  添加个人信息
// *
// *  @param infos 个人信息；目前有两个key，“foreignid”表示用户id，“name”表示用户名
// */
//- (void)addUserInfo:(NSDictionary *)infos;

@end
