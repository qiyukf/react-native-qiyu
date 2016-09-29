//
//  QYSource.h
//  QYSDK
//
//  Created by towik on 12/21/15.
//  Copyright (c) 2016 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 *  会话窗口来源
 */
@interface QYSource : NSObject

/**
 *  来源标题
 */
@property (nonatomic,copy)      NSString    *title;

/**
 *  来源url
 */
@property (nonatomic,copy)      NSString    *urlString;

/**
 *  来源自定义信息
 */
@property (nonatomic,copy)      NSString    *customInfo;

@end
