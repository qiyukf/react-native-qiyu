//
//  QYCustomSessionViewController.h
//  QYSDK
//
//  Created by Netease on 2018/11/23.
//  Copyright © 2018 Netease. All rights reserved.
//

#import "QYSessionViewController.h"

@protocol QYCustomMessageDelegate;
@protocol QYCustomContentViewDelegate;
/**
 *  错误码
 */
typedef NS_ENUM(NSInteger, QYCustomMessageErrorCode) {
    QYCustomMessageErrorCodeUnknown         = 0,    //未知错误
    QYCustomMessageErrorCodeInvalidParam    = 1,    //错误参数
    QYCustomMessageErrorCodeInvalidMessage  = 2,    //无效消息体
    QYCustomMessageErrorCodeSQLFailed       = 3,    //SQL语句执行失败
};


/**
 *  消息持久化结果block
 *  @param error 错误信息
 */
typedef void(^QYCustomMessageCompletion)(NSError *error);


/**
 *  QYSessionViewController的分类，扩展自定义消息相关接口
 */
@interface QYSessionViewController (CustomMessage)

/**
 *  注册message-model-contentView的映射关系（必须）
 *  @discussion 若要使用自定义消息，必须调用此方法设置映射关系！
 *  @param messageClass     消息类
 *  @param modelClass       消息对应的数据模型类
 *  @param contentViewClass 消息对应的视图
 */
- (void)registerCustomMessageClass:(Class)messageClass
                        modelClass:(Class)modelClass
                  contentViewClass:(Class)contentViewClass;

/**
 *  设置消息事件委托对象
 *  @param delegate 被委托对象
 */
- (void)addCustomMessageDelegate:(id<QYCustomMessageDelegate>)delegate;

/**
 *  设置消息视图委托对象
 *  @param delegate 被委托对象
 */
- (void)addCustomContentViewDelegate:(id<QYCustomContentViewDelegate>)delegate;

/**
 *  清除消息事件委托对象
 *  @param delegate 被清除的委托对象
 */
- (void)removeCustomMessageDelegate:(id<QYCustomMessageDelegate>)delegate;

/**
 *  清除消息视图委托对象
 *  @param delegate 被清除的委托对象
 */
- (void)removeCustomContentViewDelegate:(id<QYCustomContentViewDelegate>)delegate;

/**
 *  从尾部追加消息
 *  @param message    消息对象
 *  @param save       是否需要持久化消息数据
 *  @param reload     是否需要刷新界面
 *  @param completion 消息持久化结果回调
 */
- (void)addCustomMessage:(QYCustomMessage *)message
            needSaveData:(BOOL)save
          needReloadView:(BOOL)reload
              completion:(QYCustomMessageCompletion)completion;

/**
 *  从头部插入消息
 *  @discussion 插入消息不支持持久化数据
 *  @param message  消息对象
 */
- (void)insertCustomMessage:(QYCustomMessage *)message;

/**
 *  从中间插入消息
 *  @discussion 插入消息不支持持久化数据
 *  @param message  消息对象
 *  @param index    插入位置
 */
- (void)insertCustomMessage:(QYCustomMessage *)message index:(NSInteger)index;

/**
 *  刷新消息
 *  @param message  消息对象
 *  @param save     是否需要持久化消息数据
 *  @param reload   是否需要刷新界面
 *  @param completion 消息持久化结果回调
 */
- (void)updateCustomMessage:(QYCustomMessage *)message
               needSaveData:(BOOL)save
             needReloadView:(BOOL)reload
                 completion:(QYCustomMessageCompletion)completion;

/**
 *  删除消息
 *  @param message  消息对象
 *  @param save     删除记录是否同步至数据库
 *  @param reload   是否需要刷新界面
 */
- (void)deleteCustomMessage:(QYCustomMessage *)message
               needSaveData:(BOOL)save
             needReloadView:(BOOL)reload;

/**
 *  从数据库中取出消息
 *  @param messageId 消息的唯一ID
 *  @return 取出的消息体
 */
- (QYCustomMessage *)fetchCustomMessageFromDatabaseForMessageId:(NSString *)messageId;

/**
 *  从当前table的dataSource中取出消息
 *  @param messageId 消息的唯一ID
 *  @return 取出的消息体
 */
- (QYCustomMessage *)fetchCustomMessageFromDataSourceForMessageId:(NSString *)messageId;

@end

