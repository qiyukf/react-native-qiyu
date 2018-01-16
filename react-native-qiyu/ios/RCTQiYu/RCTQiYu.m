//
//  RCTQiYu.m
//  RCTQiYu
//
//  Created by JackYu on 16/8/30.
//  Copyright © 2016年 Netease. All rights reserved.
//

#import "RCTQiYu.h"
#import "QYSDK.h"


@interface RCTQiYu ()<QYConversationManagerDelegate>

@property (nonatomic, strong) QYSessionViewController *sessionVC;   //七鱼联系界面

@property (nonatomic, strong) NSString *unreadCountEventName;       //未读数事件名

@property (nonatomic, strong) UIColor *naviBarColor;                //导航栏颜色

@property (nonatomic, strong) NSNumber *viewReactTag;               //记录当前视图的reactTag

@property (nonatomic, assign) BOOL showQuitQueue;                   //记录显示排队选择配置

@end



@implementation RCTQiYu

@synthesize bridge=_bridge;

RCT_EXPORT_MODULE();


RCT_EXPORT_METHOD(toast:(NSString*)toast) {
    NSLog(@"%@", toast);
}

RCT_EXPORT_METHOD(registerAppId:(nonnull NSString *)appKey appName:(nonnull NSString *)appName) {
    if (appKey && appName) {
        [[QYSDK sharedSDK] registerAppId:appKey appName:appName];
    }
}

RCT_EXPORT_METHOD(setCustomUIConfig:(nonnull NSDictionary*)paramDict) {
    if ([paramDict objectForKey:@"sessionTipTextColor"]) {
        [[QYSDK sharedSDK] customUIConfig].sessionTipTextColor = [self colorFromString:[paramDict objectForKey:@"sessionTipTextColor"]];
    }
    if ([paramDict objectForKey:@"sessionTipTextFontSize"]) {
        [[QYSDK sharedSDK] customUIConfig].sessionTipTextFontSize = [RCTConvert CGFloat:[paramDict objectForKey:@"sessionTipTextFontSize"]];
    }
    if ([paramDict objectForKey:@"customMessageTextColor"]) {
        [[QYSDK sharedSDK] customUIConfig].customMessageTextColor = [self colorFromString:[paramDict objectForKey:@"customMessageTextColor"]];
    }
    if ([paramDict objectForKey:@"messageTextFontSize"]) {
        [[QYSDK sharedSDK] customUIConfig].customMessageTextFontSize = [RCTConvert CGFloat:[paramDict objectForKey:@"messageTextFontSize"]];
    }
    if ([paramDict objectForKey:@"serviceMessageTextColor"]) {
        [[QYSDK sharedSDK] customUIConfig].serviceMessageTextColor = [self colorFromString:[paramDict objectForKey:@"serviceMessageTextColor"]];
    }
    if ([paramDict objectForKey:@"messageTextFontSize"]) {
        [[QYSDK sharedSDK] customUIConfig].serviceMessageTextFontSize = [RCTConvert CGFloat:[paramDict objectForKey:@"messageTextFontSize"]];
    }
    if ([paramDict objectForKey:@"tipMessageTextColor"]) {
        [[QYSDK sharedSDK] customUIConfig].tipMessageTextColor = [self colorFromString:[paramDict objectForKey:@"tipMessageTextColor"]];
    }
    if ([paramDict objectForKey:@"tipMessageTextFontSize"]) {
        [[QYSDK sharedSDK] customUIConfig].tipMessageTextFontSize = [RCTConvert CGFloat:[paramDict objectForKey:@"tipMessageTextFontSize"]];
    }
    if ([paramDict objectForKey:@"inputTextColor"]) {
        [[QYSDK sharedSDK] customUIConfig].inputTextColor = [self colorFromString:[paramDict objectForKey:@"inputTextColor"]];
    }
    if ([paramDict objectForKey:@"inputTextFontSize"]) {
        [[QYSDK sharedSDK] customUIConfig].inputTextFontSize = [RCTConvert CGFloat:[paramDict objectForKey:@"inputTextFontSize"]];
    }
    NSString *imageName = nil;
    if ([paramDict objectForKey:@"sessionBackgroundImage"]) {
        imageName = [RCTConvert NSString:[paramDict objectForKey:@"sessionBackgroundImage"]];
        dispatch_async(dispatch_get_main_queue(), ^{
            [[QYSDK sharedSDK] customUIConfig].sessionBackground = [[UIImageView alloc] initWithImage:[self getResourceImage:imageName]];
        });
    }
    if ([paramDict objectForKey:@"sessionTipBackgroundColor"]) {
        [[QYSDK sharedSDK] customUIConfig].sessionTipBackgroundColor = [self colorFromString:[paramDict objectForKey:@"sessionTipBackgroundColor"]];
    }
    if ([paramDict objectForKey:@"customerHeadImage"]) {
        imageName = [RCTConvert NSString:[paramDict objectForKey:@"customerHeadImage"]];
        [[QYSDK sharedSDK] customUIConfig].customerHeadImage = [self getResourceImage:imageName];
    }
    if ([paramDict objectForKey:@"serviceHeadImage"]) {
        imageName = [RCTConvert NSString:[paramDict objectForKey:@"serviceHeadImage"]];
        [[QYSDK sharedSDK] customUIConfig].serviceHeadImage = [self getResourceImage:imageName];
    }
    if ([paramDict objectForKey:@"customerMessageBubbleNormalImage"]) {
        imageName = [RCTConvert NSString:[paramDict objectForKey:@"customerMessageBubbleNormalImage"]];
        [[QYSDK sharedSDK] customUIConfig].customerMessageBubbleNormalImage = [self getResourceImage:imageName];
    }
    if ([paramDict objectForKey:@"serviceMessageBubbleNormalImage"]) {
        imageName = [RCTConvert NSString:[paramDict objectForKey:@"serviceMessageBubbleNormalImage"]];
        [[QYSDK sharedSDK] customUIConfig].serviceMessageBubbleNormalImage = [self getResourceImage:imageName];
    }
    if ([paramDict objectForKey:@"customerMessageBubblePressedImage"]) {
        imageName = [RCTConvert NSString:[paramDict objectForKey:@"customerMessageBubblePressedImage"]];
        [[QYSDK sharedSDK] customUIConfig].customerMessageBubblePressedImage = [self getResourceImage:imageName];
    }
    if ([paramDict objectForKey:@"serviceMessageBubblePressedImage"]) {
        imageName = [RCTConvert NSString:[paramDict objectForKey:@"serviceMessageBubblePressedImage"]];
        [[QYSDK sharedSDK] customUIConfig].serviceMessageBubblePressedImage = [self getResourceImage:imageName];
    }
    if ([paramDict objectForKey:@"sessionMessageSpacing"]) {
        [[QYSDK sharedSDK] customUIConfig].sessionMessageSpacing = [RCTConvert CGFloat:[paramDict objectForKey:@"sessionMessageSpacing"]];
    }
    if ([paramDict objectForKey:@"showHeadImage"]) {
        [[QYSDK sharedSDK] customUIConfig].showHeadImage = [RCTConvert BOOL:[paramDict objectForKey:@"showHeadImage"]];
    }
    if ([paramDict objectForKey:@"naviBarColor"]) {
        self.naviBarColor = [self colorFromString:[paramDict objectForKey:@"naviBarColor"]];
    }
    if ([paramDict objectForKey:@"naviBarStyleDark"]) {
        [[QYSDK sharedSDK] customUIConfig].rightBarButtonItemColorBlackOrWhite = [RCTConvert BOOL:[paramDict objectForKey:@"naviBarStyleDark"]];
    }
    if ([paramDict objectForKey:@"showAudioEntry"]) {
        [[QYSDK sharedSDK] customUIConfig].showAudioEntry = [RCTConvert BOOL:[paramDict objectForKey:@"showAudioEntry"]];
    }
    if ([paramDict objectForKey:@"showEmoticonEntry"]) {
        [[QYSDK sharedSDK] customUIConfig].showEmoticonEntry = [RCTConvert BOOL:[paramDict objectForKey:@"showEmoticonEntry"]];
    }
    if ([paramDict objectForKey:@"autoShowKeyboard"]) {
        [[QYSDK sharedSDK] customUIConfig].autoShowKeyboard = [RCTConvert BOOL:[paramDict objectForKey:@"autoShowKeyboard"]];
    }
    if ([paramDict objectForKey:@"bottomMargin"]) {
        [[QYSDK sharedSDK] customUIConfig].bottomMargin = [RCTConvert CGFloat:[paramDict objectForKey:@"bottomMargin"]];
    }
//    if ([paramDict objectForKey:@"showCloseSessionEntry"]) {
//        [[QYSDK sharedSDK] customUIConfig].showCloseSessionEntry = [RCTConvert BOOL:[paramDict objectForKey:@"showCloseSessionEntry"]];
//    }
}

RCT_EXPORT_METHOD(setUrlClickWithEventName:(NSString*)EventName) {
    [[QYSDK sharedSDK] customActionConfig].linkClickBlock = ^(NSString *linkAddress){
        [self.bridge.eventDispatcher sendDeviceEventWithName:EventName body:@{@"url": linkAddress}];
    };
}

//RCT_EXPORT_METHOD(setBotClickWithEventName:(NSString*)EventName) {
//    [[QYSDK sharedSDK] customActionConfig].botClick = ^(NSString *target, NSString *params) {
//        [self.bridge.eventDispatcher sendDeviceEventWithName:EventName body:@{@"target": target,
//                                                                              @"params": params}];
//    };
//}

RCT_EXPORT_METHOD(setUnreadCountWithEventName:(NSString*)EventName) {
    [[[QYSDK sharedSDK] conversationManager] setDelegate:self];
    self.unreadCountEventName = EventName;
}

RCT_EXPORT_METHOD(getUnreadCountCallback:(RCTResponseSenderBlock)callback) {
    NSInteger count = [[[QYSDK sharedSDK] conversationManager] allUnreadCount];
    NSString *allUnreadCount = [NSString stringWithFormat:@"%ld", (long)count];
    if (callback) {
        callback(@[allUnreadCount]);
    }
}

//RCT_EXPORT_METHOD(clearUnreadCount) {
//    [[[QYSDK sharedSDK] conversationManager] clearUnreadCount];
//}

RCT_EXPORT_METHOD(setUserInfo:(nonnull NSDictionary*)paramDict) {
    QYUserInfo *userInfo = nil;
    if ([paramDict objectForKey:@"userId"] || [paramDict objectForKey:@"data"]) {
        userInfo = [[QYUserInfo alloc] init];
        if ([paramDict objectForKey:@"userId"]) {
            userInfo.userId = [RCTConvert NSString:[paramDict objectForKey:@"userId"]];
        }
        if ([paramDict objectForKey:@"data"]) {
            userInfo.data = [RCTConvert NSString:[paramDict objectForKey:@"data"]];
        }
    }
    if (userInfo) {
        [[QYSDK sharedSDK] setUserInfo:userInfo];
    }
}

RCT_EXPORT_METHOD(openServiceWindow:(nonnull NSDictionary*)paramDict){
    QYSessionViewController *sessionVC = [[QYSDK sharedSDK] sessionViewController];
    self.sessionVC = sessionVC;
    [self setSessionVC:sessionVC paramDict:paramDict];
    sessionVC.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"返回" style:UIBarButtonItemStylePlain target:self action:@selector(back:)];
    sessionVC.hidesBottomBarWhenPushed = YES;
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:sessionVC];
    if (self.naviBarColor) {
        nav.navigationBar.barTintColor = self.naviBarColor;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:nav animated:YES completion:nil];
    });
}

//RCT_EXPORT_METHOD(openQiYuWindow:(nonnull NSDictionary*)paramDict reactTag:(nonnull NSNumber*)reactTag){
//    QYSessionViewController *sessionVC = [[QYSDK sharedSDK] sessionViewController];
//    [self setSessionVC:sessionVC paramDict:paramDict];
//    sessionVC.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"返回" style:UIBarButtonItemStylePlain target:self action:@selector(backWithReactTag:)];
//    sessionVC.hidesBottomBarWhenPushed = YES;
//    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:sessionVC];
//    if (self.naviBarColor) {
//        nav.navigationBar.barTintColor = self.naviBarColor;
//    }
//    self.viewReactTag = reactTag;
//    RCTUIManager *uiManager = self.bridge.uiManager;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        UIView *view = [uiManager viewForReactTag:reactTag];
//        UIViewController *viewController = (UIViewController*)view.reactViewController;
//        [viewController presentViewController:nav animated:YES completion:nil];
//    });
//}

RCT_EXPORT_METHOD(logout) {
    [[QYSDK sharedSDK] logout:nil];
}

RCT_EXPORT_METHOD(cleanCache) {
    [[QYSDK sharedSDK] cleanResourceCacheWithBlock:nil];
}

#pragma mark - QYConversationManagerDelegate
- (void)onUnreadCountChanged:(NSInteger)count {
    NSString *allUnreadCount = [NSString stringWithFormat:@"%ld", (long)count];
    [self.bridge.eventDispatcher sendDeviceEventWithName:self.unreadCountEventName body:@{@"unreadCount": allUnreadCount}];
}

#pragma mark - Private Methods
- (void)setSessionVC:(QYSessionViewController*)sessionVC paramDict:(NSDictionary*)paramDict {
    QYSource *source = nil;
    if ([paramDict objectForKey:@"source"]) {
        NSDictionary *sourceDict = [RCTConvert NSDictionary:[paramDict objectForKey:@"source"]];
        if ([sourceDict objectForKey:@"sourceTitle"] || [sourceDict objectForKey:@"sourceUrl"]
            || [sourceDict objectForKey:@"sourceCustomInfo"]) {
            source = [[QYSource alloc] init];
            if ([sourceDict objectForKey:@"sourceTitle"]) {
                source.title = [RCTConvert NSString:[sourceDict objectForKey:@"sourceTitle"]];
            }
            if ([sourceDict objectForKey:@"sourceUrl"]) {
                source.urlString = [RCTConvert NSString:[sourceDict objectForKey:@"sourceUrl"]];
            }
            if ([sourceDict objectForKey:@"sourceCustomInfo"]) {
                source.customInfo = [RCTConvert NSString:[sourceDict objectForKey:@"sourceCustomInfo"]];
            }
        }
    }
    QYCommodityInfo *commodityInfo = nil;
    if ([paramDict objectForKey:@"commodityInfo"]) {
        NSDictionary *commodityInfoDict = [RCTConvert NSDictionary:[paramDict objectForKey:@"commodityInfo"]];
        if ([commodityInfoDict objectForKey:@"commodityInfoTitle"] || [commodityInfoDict objectForKey:@"commodityInfoDesc"]
            || [commodityInfoDict objectForKey:@"pictureUrl"] || [commodityInfoDict objectForKey:@"commodityInfoUrl"]
            || [commodityInfoDict objectForKey:@"note"] || [commodityInfoDict objectForKey:@"show"]) {
            commodityInfo = [[QYCommodityInfo alloc] init];
            if ([commodityInfoDict objectForKey:@"commodityInfoTitle"]) {
                commodityInfo.title = [RCTConvert NSString:[commodityInfoDict objectForKey:@"commodityInfoTitle"]];
            }
            if ([commodityInfoDict objectForKey:@"commodityInfoDesc"]) {
                commodityInfo.desc = [RCTConvert NSString:[commodityInfoDict objectForKey:@"commodityInfoDesc"]];
            }
            if ([commodityInfoDict objectForKey:@"pictureUrl"]) {
                commodityInfo.pictureUrlString = [RCTConvert NSString:[commodityInfoDict objectForKey:@"pictureUrl"]];
            }
            if ([commodityInfoDict objectForKey:@"commodityInfoUrl"]) {
                commodityInfo.urlString = [RCTConvert NSString:[commodityInfoDict objectForKey:@"commodityInfoUrl"]];
            }
            if ([commodityInfoDict objectForKey:@"note"]) {
                commodityInfo.note = [RCTConvert NSString:[commodityInfoDict objectForKey:@"note"]];
            }
            if ([commodityInfoDict objectForKey:@"show"]) {
                commodityInfo.show = [RCTConvert BOOL:[commodityInfoDict objectForKey:@"show"]];
            }
        }
    }
    if (source) {
        sessionVC.source = source;
    }
    if (commodityInfo) {
        sessionVC.commodityInfo = commodityInfo;
    }
    if ([paramDict objectForKey:@"sessionTitle"]) {
        sessionVC.sessionTitle = [RCTConvert NSString:[paramDict objectForKey:@"sessionTitle"]];
    }
    if ([paramDict objectForKey:@"groupId"]) {
        sessionVC.groupId = [RCTConvert int64_t:[paramDict objectForKey:@"groupId"]];
    }
    if ([paramDict objectForKey:@"staffId"]) {
        sessionVC.staffId = [RCTConvert int64_t:[paramDict objectForKey:@"staffId"]];
    }
    if ([paramDict objectForKey:@"robotId"]) {
        sessionVC.robotId = [RCTConvert int64_t:[paramDict objectForKey:@"robotId"]];
    }
    if ([paramDict objectForKey:@"vipLevel"]) {
        sessionVC.vipLevel = [RCTConvert NSInteger:[paramDict objectForKey:@"vipLevel"]];
    }
    if ([paramDict objectForKey:@"robotFirst"]) {
        sessionVC.openRobotInShuntMode = [RCTConvert BOOL:[paramDict objectForKey:@"robotFirst"]];
    }
    if ([paramDict objectForKey:@"faqTemplateId"]) {
        sessionVC.commonQuestionTemplateId = [RCTConvert int64_t:[paramDict objectForKey:@"faqTemplateId"]];
    }
    if ([paramDict objectForKey:@"showCloseSessionEntry"]) {
        [[QYSDK sharedSDK] customUIConfig].showCloseSessionEntry = [RCTConvert BOOL:[paramDict objectForKey:@"showCloseSessionEntry"]];
    }
    if ([paramDict objectForKey:@"showQuitQueue"]) {
        self.showQuitQueue = [RCTConvert BOOL:[paramDict objectForKey:@"showQuitQueue"]];
    }
}

- (void)back:(id)sender {
    if (self.showQuitQueue) {
        [[[QYSDK sharedSDK] customActionConfig] showQuitWaiting:^(QuitWaitingType quitType) {
            if (quitType != QuitWaitingTypeCancel) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [[UIApplication sharedApplication].keyWindow.rootViewController dismissViewControllerAnimated:YES completion:nil];
                    self.sessionVC = nil;
                });
            }
        }];
    } else {
        dispatch_async(dispatch_get_main_queue(), ^{
            [[UIApplication sharedApplication].keyWindow.rootViewController dismissViewControllerAnimated:YES completion:nil];
            self.sessionVC = nil;
        });
    }
}

//- (void)backWithReactTag:(id)sender {
//    if (self.showQuitQueue) {
//        __weak typeof(self) weakSelf = self;
//        [[[QYSDK sharedSDK] customActionConfig] showQuitWaiting:^(QuitWaitingType quitType) {
//            if (quitType != QuitWaitingTypeCancel) {
//                [weakSelf dismissViewController];
//            }
//        }];
//    } else {
//        [self dismissViewController];
//    }
//}
//
//- (void)dismissViewController {
//    RCTUIManager *uiManager = self.bridge.uiManager;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        UIView *view = [uiManager viewForReactTag:self.viewReactTag];
//        UIViewController *viewController = (UIViewController*)view.reactViewController;
//        [viewController dismissViewControllerAnimated:YES completion:nil];
//    });
//}

- (UIColor *)colorFromString:(NSString*)colorString
{
    NSString *color = nil;
    NSNumber *argb = nil;
    if ([colorString characterAtIndex:0] == '#') {
        if (colorString.length == 7) {
            color = @"0xFF";
            color = [color stringByAppendingString:[colorString substringFromIndex:1]];
            argb = [[NSNumber alloc] initWithUnsignedLong:strtol([color UTF8String], 0, 16)];
            
            return [RCTConvert UIColor:argb];
        }else if (colorString.length == 9) {
            color = @"0x";
            color = [color stringByAppendingString:[colorString substringFromIndex:1]];
            argb = [[NSNumber alloc] initWithUnsignedLong:strtol([color UTF8String], 0, 16)];
            
            return [RCTConvert UIColor:argb];
        }
    }
    
    return nil;
}

- (UIImage*)getResourceImage:(NSString*)imageFilePath
{
    NSString *localImagePath = [imageFilePath substringFromIndex:1];
    NSString *bundlePath = [NSBundle mainBundle].bundlePath;
    bundlePath = [[bundlePath stringByAppendingPathComponent:@"assets"] stringByAppendingPathComponent:localImagePath];
    
    UIImage *image = [[UIImage imageWithContentsOfFile:bundlePath] resizableImageWithCapInsets:UIEdgeInsetsMake(15,15,30,30) resizingMode:UIImageResizingModeStretch];
    if (image) {
        return image;
    }
    
    return nil;
}









@end
