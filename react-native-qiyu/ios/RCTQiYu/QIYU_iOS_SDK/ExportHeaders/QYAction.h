//
//  QYAction.h
//  QYSDK
//
//  Created by Netease on 2018/10/25.
//  Copyright © 2018年 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  动作类型
 */
typedef NS_ENUM(NSInteger, QYActionType) {
    QYActionTypeNone = 0,
    QYActionTypeRequestStaffBefore,     //请求客服前
    QYActionTypeRequestStaffAfter,      //请求客服后
};

/**
 *  通用回调，一般用于告诉SDK是否继续进行后续操作
 *  例如：设置了请求客服前回调后，通过调用此QYCallback来继续或是中断请求客服
 */
typedef void (^QYCallback)(BOOL continueIfNeeded);


// QYActionTypeRequestStaffBefore 定义
/**
 *  请求客服场景
 */
typedef NS_ENUM(NSInteger, QYRequestStaffBeforeScene) {
    QYRequestStaffBeforeSceneNone,               //无需关心的请求客服场景
    QYRequestStaffBeforeSceneInit,               //进入会话页面，初次请求客服
    QYRequestStaffBeforeSceneRobotUnable,        //机器人模式下告知无法解答，点击消息中人工客服按钮请求
    QYRequestStaffBeforeSceneNavHumanButton,     //机器人模式下，点击右上角人工按钮
    QYRequestStaffBeforeSceneActiveRequest,      //主动请求人工客服
    QYRequestStaffBeforeSceneChangeStaff,        //切换人工客服
};

/**
 *  请求客服前回调
 *
 *  @param scene 请求客服场景
 *  @param onlyHuman 是否只请求人工客服
 *  @param callback 处理完成后的回调，若需继续请求客服，则调用callback(YES)；若需停止请求，调用callback(NO)
 */
typedef void (^QYRequestStaffBeforeBlock)(QYRequestStaffBeforeScene scene, BOOL onlyHuman, QYCallback callback);

// QYActionTypeRequestStaffAfter 定义
/**
 *  请求客服后回调
 *
 *  @param info 会话相关信息
 *  @param error 错误信息
 */
typedef void (^QYRequestStaffAfterBlock)(NSDictionary *info, NSError *error);


/**
 *  QYAction定义了部分动作，通过type区分不同情形，并调用各自对应的回调
 *  若需要获取这部分动作，请在QYCustomActionConfig单例中设置QYAction属性
 */
@interface QYAction : NSObject

/**
 *  动作类型
 */
@property (nonatomic, assign) QYActionType type;

/**
 *  请求客服前调用
 */
@property (nonatomic, copy) QYRequestStaffBeforeBlock requestStaffBeforeBlock;

/**
 *  请求客服后调用
 */
@property (nonatomic, copy) QYRequestStaffAfterBlock requestStaffAfterBlock;

@end

