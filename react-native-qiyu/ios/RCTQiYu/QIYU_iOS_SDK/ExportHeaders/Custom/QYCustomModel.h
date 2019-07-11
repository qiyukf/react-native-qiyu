//
//  QYCustomModel.h
//  QYSDK
//
//  Created by Netease on 2018/11/22.
//  Copyright © 2018 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>

@class QYCustomMessage;

/**
 *  model布局协议
 */
@protocol QYCustomModelLayoutDataSource <NSObject>

@required
/**
 * model对应的cell复用标识（必须）
 */
- (NSString *)cellReuseIdentifier;

@optional
/**
 * 视图大小
 * @discussion
 *  1. 若显示气泡，则contentView位于气泡内部，气泡有默认最大宽度bubbleMaxWidth
 *  2. 若不显示气泡，仅显示头像，则contentView位于头像另一侧
 *  3. 若不显示头像及气泡，则contentView为整个cell，宽度固定为table宽度
 *  @param bubbleMaxWidth 气泡最大宽度
 */
- (CGSize)contentSizeForBubbleMaxWidth:(CGFloat)bubbleMaxWidth;

/**
 *  是否显示头像，默认显示
 */
- (BOOL)needShowAvatar;

/**
 *  是否显示气泡，默认显示
 */
- (BOOL)needShowBubble;

/**
 *  内容视图距离气泡的内间距，默认UIEdgeInsetsZero
 */
- (UIEdgeInsets)contentViewInsets;

/**
 *  气泡距离整个cell的内间距，默认UIEdgeInsetsZero
 */
- (UIEdgeInsets)bubbleViewInsets;

/**
 *  头像与气泡间距，默认5pt
 */
- (CGFloat)avatarBubbleSpace;

@end


/**
 *  自定义消息数据源基类（即用于消息列表刷新的数据源）
 *  使用方法：针对需自定义的消息数据源，写子类继承QYCustomModel，并实现QYCustomModelLayoutDataSource协议
 */
@interface QYCustomModel : NSObject <QYCustomModelLayoutDataSource>

/**
 *  消息数据
 */
@property (nonatomic, strong, readonly) QYCustomMessage *message;

@end
