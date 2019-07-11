//
//  QYCustomContentView.h
//  YSFSDK
//
//  Created by liaosipei on 2018/11/27.
//  Copyright © 2018 Netease. All rights reserved.
//

#import <UIKit/UIKit.h>

@class QYCustomModel;
@protocol QYCustomContentViewDelegate;


/**
 *  自定义消息视图基类
 *  使用方法：针对需自定义的消息视图，写子类继承QYCustomContentView，并实现初始化和刷新方法
 */
@interface QYCustomContentView : UIView

/**
 *  数据模型
 */
@property (nonatomic, strong, readonly) QYCustomModel *model;

/**
 *  事件代理，通过addCustomContentViewDelegate:方法设置
 */
@property (nonatomic, weak, readonly) id<QYCustomContentViewDelegate> delegate;

/**
 *  视图初始化方法（必须）
 *  @discussion 一般来说，subViews在此init方法中添加
 *  @return 视图实例
 */
- (instancetype)initCustomContentView;

/**
 *  刷新方法（必须）
 *  @discussion model更新时会自动触发此方法，需重写来更新视图
 *  @param model 数据模型
 */
- (void)refreshData:(QYCustomModel *)model;

@end
