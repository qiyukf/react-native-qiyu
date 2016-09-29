# 网易七鱼 React-Native 模块集成指南
## QiYu
### 简介
网易七鱼 iOS SDK 是客服系统访客端的解决方案，既包含了客服聊天逻辑管理，也提供了聊天界面，开发者可方便的将客服功能集成到自己的 APP 中。
本模块支持 iOS 7 以上，Android 2.3 以上版本，同时支持手机、Pad。在iOS 9.2 以上版本中支持 IPv6，能正常通过苹果审核。
详情请前往：http://www.qiyukf.com

### 安装与配置
#### 安装
通过npm安装模块
```
npm install --save react-native-qiyu
```
即把react-native-qiyu导入到工程中的node_modules文件夹中

#### 配置
##### iOS
通过rnpm link
如果你还没有安装[rnpm](https://github.com/rnpm/rnpm)，执行以下命令来安装rnpm
```
npm install -g rnpm
```
安装完rnpm后执行以下命令
```
rnpm link react-native-qiyu
```
link成功命令行会提示
```
rnpm info Linking react-native-wx ios dependency
```
或者你还可以手动配置
```
打开XCode's工程中, 右键点击Libraries文件夹 ➜ Add Files to <...> b.去node_modules ➜ react-native-qiyu ➜ ios ➜ 选择 RCTQiYu.xcodeproj c.在工程Build Phases ➜ Link Binary With Libraries中添加libRCTQiYu.a

工程配置
在工程target的Build Phases->Link Binary with Libraries中加入UIKit.framework、CoreText.framework、MobileCoreService.framework、SystemConfiguration.framework、AVFoundation.framwork、CoreTelephony.framework、CoreMedia.framework、AudioToolbox.framework、libz.tbd、libstdc++.6.0.9.tbd、libsqlite3.0.tbd等依赖库
```
iOS9传输安全问题
```
在iOS9中，默认需要为每次网络传输建立SSL，解决方法是在应用plist文件中设置<key>NSAppTransportSecurity</key><dict><key>NSAllowsArbitraryLoads</key></true></dict>
```
如果在原生代码中需要引入七鱼SDK
```
在工程target的Build Setting->Library Search Paths中添加$(SRCROOT)/../node_modules/react-native-qiyu/ios/RCTQiYu、在Header Search Paths中添加$(SRCROOT)/../node_modules/react-native-qiyu/ios/RCTQiYu
```
消息推送
```
需要在工程的APPDelegate文件中的(void)application:(UIApplication *)app
                didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken方法中把 APNS Token 传给 SDK
```
示例代码：
```
- (void)application:(UIApplication *)app
                didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    ......

    [[QYSDK sharedSDK] updateApnsToken:deviceToken];

    ......
}
```
具体使用请参考QiYuDemo例子工程

##### Android
手动配置
编辑android/settings.gradle
```
// ...

include ':react-native-qiyu'
project(':react-native-qiyu').projectDir = new File(rootProject.projectDir, '../node_modules/react-native-qiyu/android')
```
编辑android/app/build.gradle
```
// ...

dependencies {
    // ...
    compile project(':react-native-qiyu')
}
```
在MainApplication.java中注册模块（基于React-Native 0.32+）
编辑android/app/src/main/java/[...]/MainApplication.java
```
// ...

import com.qiyukf.unicorn.reactnative.QiyuSdkPackage;    // <--- 导包

public class MainApplication extends Application implements ReactApplication {
    // ...

    private final ReactNativeHost mReactNativeHost = new ReactNativeHost(this) {
        // ...

        @Override
        protected List<ReactPackage> getPackages() {
            return Arrays.<ReactPackage>asList(
                new MainReactPackage(),
                new QiyuSdkPackage("七鱼管理后台的appKey", "七鱼管理后台的App名称")    // <--- 添加package
            );
        }

        // ...
    };

    // ...
}
```
如果你使用的React-Native版本中不包含MainApplication.java，则可能需要在MainActivity.java中注册模块，方法同上。

### Method
- registerAppId
- openServiceWindow
- setCustomUIConfig
- setUrlClickWithEventName
- setUnreadCountWithEventName
- getUnreadCountCallback
- setUserInfo
- logout

### 方法接口描述
#### * registerAppId
注册七鱼SDK
```
registerAppId(appKey, appName)
```

##### params
| 参数名 | 类型 | 默认值 | 描述 |
| :----- | :----- | :----- | :----- |
| appKey | 字符串类型 | 无 | 七鱼管理后台的appKey |
| appName | 字符串类型 | 无 | 七鱼管理后台的App名称 |

##### 示例代码
```
import QiYu from 'react-native-qiyu';
QiYu.registerAppId('七鱼管理后台的appKey', '七鱼管理后台的App名称');
```

##### 注意事项
建议在应用启动时初始化，初始化之前无法使用此模块的其他方法。七鱼模块只需要初始化一次。代码如下
```
componentWillMount() {
    QiYu.registerAppId('七鱼管理后台的appKey', '七鱼管理后台的App名称');
}
```

#### * openServiceWindow
启动客服聊天窗口
```
openServiceWindow(params)
```

##### params
| 参数名 | 类型 | 默认值 | 描述 |
| :----- | :----- | :----- | :----- |
| source | JSON对象 | 无 | 会话窗口来源 |
| sourceTitle | 字符串类型 | 无 | 会话窗口来源标题 |
| sourceUrl | 字符串类型 | 无 | 会话窗口来源URL |
| sourceCustomInfo | 字符串类型 | 无 | 会话窗口来源自定义消息 |
| commodityInfo | JSON对象 | 无 | 商品详情信息 |
| commodityInfoTitle | 字符串类型 | 无 | 商品详情信息展示商品标题，字符数要求小于100 |
| commodityInfoDesc | 字符串类型 | 无 | 商品详情信息展示商品描述，字符数要求小于300 |
| pictureUrl | 字符串类型 | 无 | 商品详情信息展示商品图片URL，字符数要求小于1000 |
| commodityInfoUrl | 字符串类型 | 无 | 商品详情信息展示跳转URL，字符数要求小于1000 |
| note | 字符串类型 | 无 | 商品详情信息展示备注信息，可以显示价格、订单号等，字符数要求小于100 |
| show | 布尔类型 | false | 商品详情信息展示发送时是否要在用户端显示，默认不显示 |
| sessionTitle | 字符串类型 | 无 | 客服会话窗口标题 |
| staffId | long类型 | 无 | 指定客服id，如果同时指定 staffId 和 groupId，以 staffId 为准，忽略 groupId |
| groupId | long类型 | 无 | 指定客服分组id，如果同时指定 staffId 和 groupId，以 staffId 为准，忽略 groupId |

##### 示例代码
```
import QiYu from 'react-native-qiyu';
var params = {
    source:{
        sourceTitle:'网易七鱼ReactNative',
        sourceUrl:'http://www.qiyukf.com',
        sourceCustomInfo:'我是来自自定义的信息'
    },
    commodityInfo:{
        commodityInfoTitle:'ReactNative商品',
        commodityInfoDesc:'这是来自网易七鱼ReactNative的商品描述',
        pictureUrl:'http://qiyukf.com/res/img/companyLogo/blmn.png',
        commodityInfoUrl:'http://www.qiyukf.com',
        note:'￥1000',
        show:true
    },
    sessionTitle:'网易七鱼',
    groupId:0,
    staffId:0
}
QiYu.openServiceWindow(params);
```

#### * setCustomUIConfig
自定义客服聊天窗口UI
```
setCustomUIConfig(params)
```

##### params
| 参数名 | 类型 | 默认值 | 描述 |
| :----- | :----- | :----- | :----- |
| sessionTipTextColor | 字符串类型，如'#CC00FF' | 无 | 会话窗口上方提示条中的文本字体颜色 |
| sessionTipTextFontSize | int类型，如15 | 无 | 会话窗口上方提示条中的文本字体大小 |
| customMessageTextColor | 字符串类型，如'#CC00FF' | 无 | 访客文本消息字体颜色 |
| serviceMessageTextColor | 字符串类型，如'#CC00FF' | 无 | 客服文本消息字体颜色 |
| messageTextFontSize | int类型，如15 | 无 | 消息文本消息字体大小 |
| tipMessageTextColor | 字符串类型，如'#CC00FF' | 无 | 提示文本消息字体颜色 |
| tipMessageTextFontSize | int类型，如15 | 无 | 提示文本消息字体大小 |
| inputTextColor | 字符串类型，如'#CC00FF' | 无 | 输入框文本字体颜色 |
| inputTextFontSize | int类型，如15 | 无 | 输入框文本字体大小 |
| sessionBackgroundImage | [\*]字符串类型，传入图片的绝对路径，如'./qiyu/session_bg.png' | 无 | 客服聊天窗口背景图片 |
| sessionTipBackgroundColor | 字符串类型，如'#CC00FF' | 无 | 会话窗口上方提示条的背景颜色 |
| customerHeadImage | [\*]字符串类型，传入图片的绝对路径 | 无 | 访客头像 |
| serviceHeadImage | [\*]字符串类型，传入图片的绝对路径 | 无 | 客服头像 |
| sessionMessageSpacing | float类型，如3.5 | 无 | 消息竖直方向间距 |
| showHeadImage | 布尔类型 | true | 是否显示头像 |
| showAudioEntry | 布尔类型 | true | 是否显示发送语音入口，设置为false，可以修改为隐藏 |
| showEmoticonEntry | 布尔类型 | true | 是否显示发送表情入口，设置为false，可以修改为隐藏 |
| autoShowKeyboard | 布尔类型 | true | 进入聊天界面，是文本输入模式的话，会弹出键盘，设置为false，可以修改为不弹出 |
* **注意**
为了防止 react-native 在打包时将用于七鱼的图片文件过滤掉，我们需要将用于七鱼的图片文件添加引用，如
```
var session_bg = require('./qiyu/session_bg.png')
```
建议将七鱼使用的图片单独放在一个文件夹下，如qiyu。

##### 示例代码
```
import QiYu from 'react-native-qiyu';
var params = {
    sessionTipTextColor:'#CC00FF',
    sessionTipTextFontSize:20,
    customMessageTextColor:'#CC00FF',
    serviceMessageTextColor:'#CC00FF',
    messageTextFontSize:20,
    tipMessageTextColor:'#CC00FF',
    tipMessageTextFontSize:20,
    inputTextColor:'#CC00FF',
    inputTextFontSize:20,
    sessionBackgroundImage:'session_bg',
    sessionTipBackgroundColor:'#000000',
    customerHeadImage:'customer_head',
    serviceHeadImage:'service_head',
    sessionMessageSpacing:2,
    showHeadImage:true,
    showAudioEntry:false,
    showEmoticonEntry:false,
    autoShowKeyboard:false
}
QiYu.setCustomUIConfig(params);
```

#### * setUrlClickWithEventName
用于设置聊天窗口中的事件处理
```
setUrlClickWithEventName(eventName)
```

##### params
| 参数名 | 类型 | 默认值 | 描述 |
| :----- | :----- | :----- | :----- |
| eventName | 字符串类型 | 无 | 指定一个事件名称，指定DeviceEventEmitter.addListener后会进行事件监听 |
| e | Event对象 | 无 | 事件回调返回数据，返回'url'字段，为链接地址字符串 |

##### 示例代码
```
import QiYu from 'react-native-qiyu';
QiYu.setUrlClickWithEventName(eventName);
DeviceEventEmitter.addListener(eventName, function(e: Event) {
    console.log(e.url);
});
```

#### * setUnreadCountWithEventName
用于设置会话管理，使得未读数改变的时候会回调
```
setUnreadCountWithEventName(eventName)
```

##### params
| 参数名 | 类型 | 默认值 | 描述 |
| :----- | :----- | :----- | :----- |
| eventName | 字符串类型 | 无 | 指定一个事件名称，指定DeviceEventEmitter.addListener后会进行事件监听 |
| e | Event对象 | 无 | 事件回调返回数据，返回'unreadCount'字段，为未读数字符串 |

##### 示例代码
```
import QiYu from 'react-native-qiyu';
QiYu.setUnreadCountWithEventName(UnreadCountCallback);
DeviceEventEmitter.addListener(UnreadCountCallback, function(e: Event) {
    console.log(e.unreadCount);
});
```

#### * getUnreadCountCallback
得到会话未读数，主动获取
```
getUnreadCountCallback(callback(unreadCount))
```

##### params
| 参数名 | 类型 | 默认值 | 描述 |
| :----- | :----- | :----- | :----- |
| unreadCount | 字符串类型 | 无 | 返回未读消息数 |

##### 示例代码
```
import QiYu from 'react-native-qiyu';
QiYu.getUnreadCountCallback((unreadCount)=>{
    console.log(unreadCount);
});
```

#### * setUserInfo
用于设置CRM个人信息
```
setUserInfo(params)
```

##### params
| 参数名 | 类型 | 默认值 | 描述 |
| :----- | :----- | :----- | :----- |
| userId | 字符串类型 | 无 | 个人账号Id |
| data | 字符串类型 | 无 | 用户详细信息json |

##### 示例代码
```
import QiYu from 'react-native-qiyu';
var params = {
    userId:'uid10101010',
    data:'[{\"key\":\"real_name\", \"value\":\"土豪\"},{\"key\":\"mobile_phone\", \"hidden\":true},{\"key\":\"email\", \"value\":\"13800000000@163.com\"},{\"index\":0, \"key\":\"account\", \"label\":\"账号\", \"value\":\"zhangsan\", \"href\":\"http://example.domain/user/zhangsan\"},{\"index\":1, \"key\":\"sex\", \"label\":\"性别\", \"value\":\"先生\"},{\"index\":5, \"key\":\"reg_date\", \"label\":\"注册日期\", \"value\":\"2015-11-16\"},{\"index\":6, \"key\":\"last_login\", \"label\":\"上次登录时间\", \"value\":\"2015-12-22 15:38:54\"}]'
}
QiYu.setUserInfo(params);
```

#### * logout
注销当前账号
```
logout()
```

##### 示例代码
```
import QiYu from 'react-native-qiyu';
QiYu.logout();
```