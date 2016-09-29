//
//  RCTQiYu.m
//  RCTQiYu
//
//  Created by JackYu on 16/8/30.
//  Copyright © 2016年 Netease. All rights reserved.
//

#import "RCTQiYu.h"
#import "QYSDK.h"
#import "RCTConvert.h"
#import "RCTBridge.h"
#import "RCTEventDispatcher.h"


@interface RCTQiYu ()<QYConversationManagerDelegate>

@property (nonatomic, strong) NSString *unreadCountEventName;

@end



@implementation RCTQiYu

@synthesize bridge=_bridge;

RCT_EXPORT_MODULE();


RCT_EXPORT_METHOD(toast:(NSString*)toast) {
    NSLog(@"%@", toast);
}

RCT_EXPORT_METHOD(registerAppId:(NSString *)appKey appName:(NSString *)appName) {
    [[QYSDK sharedSDK] registerAppId:appKey appName:appName];
}

RCT_EXPORT_METHOD(setCustomUIConfig:(NSDictionary*)paramDict) {
    NSString *imageName = nil;
    [[QYSDK sharedSDK] customUIConfig].sessionTipTextColor = [self colorFromString:[paramDict objectForKey:@"sessionTipTextColor"]];
    [[QYSDK sharedSDK] customUIConfig].sessionTipTextFontSize = [RCTConvert CGFloat:[paramDict objectForKey:@"sessionTipTextFontSize"]];
    [[QYSDK sharedSDK] customUIConfig].customMessageTextColor = [self colorFromString:[paramDict objectForKey:@"customMessageTextColor"]];
    [[QYSDK sharedSDK] customUIConfig].customMessageTextFontSize = [RCTConvert CGFloat:[paramDict objectForKey:@"messageTextFontSize"]];
    [[QYSDK sharedSDK] customUIConfig].serviceMessageTextColor = [self colorFromString:[paramDict objectForKey:@"serviceMessageTextColor"]];
    [[QYSDK sharedSDK] customUIConfig].serviceMessageTextFontSize = [RCTConvert CGFloat:[paramDict objectForKey:@"messageTextFontSize"]];
    [[QYSDK sharedSDK] customUIConfig].tipMessageTextColor = [self colorFromString:[paramDict objectForKey:@"tipMessageTextColor"]];
    [[QYSDK sharedSDK] customUIConfig].tipMessageTextFontSize = [RCTConvert CGFloat:[paramDict objectForKey:@"tipMessageTextFontSize"]];
    [[QYSDK sharedSDK] customUIConfig].inputTextColor = [self colorFromString:[paramDict objectForKey:@"inputTextColor"]];
    [[QYSDK sharedSDK] customUIConfig].inputTextFontSize = [RCTConvert CGFloat:[paramDict objectForKey:@"inputTextFontSize"]];
    if ([paramDict objectForKey:@"sessionBackgroundImage"]) {
        imageName = [RCTConvert NSString:[paramDict objectForKey:@"sessionBackgroundImage"]];
        [[QYSDK sharedSDK] customUIConfig].sessionBackground = [[UIImageView alloc] initWithImage:[self getResourceImage:imageName]];
    }
    [[QYSDK sharedSDK] customUIConfig].sessionTipBackgroundColor = [self colorFromString:[paramDict objectForKey:@"sessionTipBackgroundColor"]];
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
    [[QYSDK sharedSDK] customUIConfig].sessionMessageSpacing = [RCTConvert CGFloat:[paramDict objectForKey:@"sessionMessageSpacing"]];
    [[QYSDK sharedSDK] customUIConfig].showHeadImage = [RCTConvert BOOL:[paramDict objectForKey:@"showHeadImage"]];
//    [[QYSDK sharedSDK] customUIConfig].rightBarButtonItemColorBlackOrWhite = [RCTConvert BOOL:[paramDict objectForKey:@"naviBarStyleDark"]];
    [[QYSDK sharedSDK] customUIConfig].showAudioEntry = [RCTConvert BOOL:[paramDict objectForKey:@"showAudioEntry"]];
    [[QYSDK sharedSDK] customUIConfig].showEmoticonEntry = [RCTConvert BOOL:[paramDict objectForKey:@"showEmoticonEntry"]];
    [[QYSDK sharedSDK] customUIConfig].autoShowKeyboard = [RCTConvert BOOL:[paramDict objectForKey:@"autoShowKeyboard"]];
}

RCT_EXPORT_METHOD(setUrlClickWithEventName:(NSString*)EventName) {
    [[QYSDK sharedSDK] customActionConfig].linkClickBlock = ^(NSString *linkAddress){
        [self.bridge.eventDispatcher sendDeviceEventWithName:EventName body:@{@"url": linkAddress}];
    };
}

RCT_EXPORT_METHOD(setUnreadCountWithEventName:(NSString*)EventName) {
    [[[QYSDK sharedSDK] conversationManager] setDelegate:self];
    _unreadCountEventName = EventName;
}

- (void)onUnreadCountChanged:(NSInteger)count {
    NSString *allUnreadCount = [NSString stringWithFormat:@"%ld", (long)count];
    [self.bridge.eventDispatcher sendDeviceEventWithName:_unreadCountEventName body:@{@"unreadCount": allUnreadCount}];
}

RCT_EXPORT_METHOD(getUnreadCountCallback:(RCTResponseSenderBlock)callback) {
    NSInteger count = [[[QYSDK sharedSDK] conversationManager] allUnreadCount];
    NSString *allUnreadCount = [NSString stringWithFormat:@"%ld", (long)count];
    callback(@[allUnreadCount]);
}

RCT_EXPORT_METHOD(setUserInfo:(NSDictionary*)paramDict) {
    QYUserInfo *userInfo = nil;
    if ([paramDict objectForKey:@"userId"] || [paramDict objectForKey:@"data"]) {
        userInfo = [[QYUserInfo alloc] init];
        userInfo.userId = [RCTConvert NSString:[paramDict objectForKey:@"userId"]];
        userInfo.data = [RCTConvert NSString:[paramDict objectForKey:@"data"]];
    }
    if (userInfo) {
        [[QYSDK sharedSDK] setUserInfo:userInfo];
    }
}

RCT_EXPORT_METHOD(openServiceWindow:(NSDictionary*)paramDict){
    NSDictionary *sourceDict = [RCTConvert NSDictionary:[paramDict objectForKey:@"source"]];
    NSDictionary *commodityInfoDict = [RCTConvert NSDictionary:[paramDict objectForKey:@"commodityInfo"]];
    QYSource *source = nil;
    if ([sourceDict objectForKey:@"sourceTitle"]) {
        source = [[QYSource alloc] init];
        source.title = [RCTConvert NSString:[sourceDict objectForKey:@"sourceTitle"]];
        source.urlString = [RCTConvert NSString:[sourceDict objectForKey:@"sourceUrl"]];
        source.customInfo = [RCTConvert NSString:[sourceDict objectForKey:@"sourceCustomInfo"]];
    }
    QYCommodityInfo *commodityInfo = nil;
    if ([commodityInfoDict objectForKey:@"commodityInfoTitle"]) {
        commodityInfo = [[QYCommodityInfo alloc] init];
        commodityInfo.title = [RCTConvert NSString:[commodityInfoDict objectForKey:@"commodityInfoTitle"]];
        commodityInfo.desc = [RCTConvert NSString:[commodityInfoDict objectForKey:@"commodityInfoDesc"]];
        commodityInfo.pictureUrlString = [RCTConvert NSString:[commodityInfoDict objectForKey:@"pictureUrl"]];
        commodityInfo.urlString = [RCTConvert NSString:[commodityInfoDict objectForKey:@"commodityInfoUrl"]];
        commodityInfo.note = [RCTConvert NSString:[commodityInfoDict objectForKey:@"note"]];
        commodityInfo.show = [RCTConvert BOOL:[commodityInfoDict objectForKey:@"show"]];
    }
    QYSessionViewController *sessionVC = [[QYSDK sharedSDK] sessionViewController];
    sessionVC.sessionTitle = [RCTConvert NSString:[paramDict objectForKey:@"sessionTitle"]];
    sessionVC.groupId = [RCTConvert int64_t:[paramDict objectForKey:@"groupId"]];
    sessionVC.staffId = [RCTConvert int64_t:[paramDict objectForKey:@"staffId"]];
    if (source) {
        sessionVC.source = source;
    }
    if (commodityInfo) {
        sessionVC.commodityInfo = commodityInfo;
    }
    sessionVC.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"返回" style:UIBarButtonItemStyleBordered target:self action:@selector(back:)];
    sessionVC.hidesBottomBarWhenPushed = YES;
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:sessionVC];
    [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:nav animated:YES completion:nil];
}

- (void)back:(id)sender {
    [[UIApplication sharedApplication].keyWindow.rootViewController dismissViewControllerAnimated:YES completion:nil];
}

RCT_EXPORT_METHOD(logout) {
    [[QYSDK sharedSDK] logout:nil];
}


- (UIColor *)colorFromString:(NSString*)colorString
{
    NSMutableString *color = nil;
    NSNumber *argb = nil;
    if ([colorString characterAtIndex:0] == '#') {
        if (colorString.length == 7) {
            color = [NSMutableString stringWithString:@"0xFF"];
            color = [color stringByAppendingString:[colorString substringFromIndex:1]];
            argb = [[NSNumber alloc] initWithUnsignedLong:strtol([color UTF8String], 0, 16)];
            
            return [RCTConvert UIColor:argb];
        }else if (colorString.length == 9) {
            color = [NSMutableString stringWithString:@"0x"];
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
    NSMutableString *bundlePath = [NSBundle mainBundle].bundlePath;
    bundlePath = [[bundlePath stringByAppendingPathComponent:@"assets"] stringByAppendingPathComponent:localImagePath];
    
    UIImage *image = [[UIImage imageWithContentsOfFile:bundlePath] resizableImageWithCapInsets:UIEdgeInsetsMake(15,15,30,30) resizingMode:UIImageResizingModeStretch];
    if (image) {
        return image;
    }
    
    return nil;
}











@end
