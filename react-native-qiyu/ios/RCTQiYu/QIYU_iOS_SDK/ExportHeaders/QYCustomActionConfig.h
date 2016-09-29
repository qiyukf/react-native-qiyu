//
//  QYCustomActionConfig.h
//  QYCustomActionConfig
//
//  Created by towik on 7/28/16.
//  Copyright (c) 2016 Netease. All rights reserved.
//

/**
 *  提供了所有自定义行为的接口;每个接口对应一个自定义行为的处理，如果设置了，则使用设置的处理，如果不设置，则采用默认处理
 */

typedef void (^QYLinkClickBlock)(NSString *linkAddress);

@interface QYCustomActionConfig : NSObject

+ (instancetype)sharedInstance;

@property (nonatomic, copy) QYLinkClickBlock linkClickBlock;

@end



