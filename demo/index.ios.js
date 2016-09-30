/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 * @flow
 */

import React, { Component } from 'react';
import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  TouchableHighlight,
  NativeModules,
  DeviceEventEmitter
} from 'react-native';

import QiYu from 'react-native-qiyu';

var customer_head = require('./qiyu/customer_head.png');
var service_head = require('./qiyu/service_head.png');
var session_bg = require('./qiyu/session_bg.png');

console.log(QiYu);

//appKey是您在网易七鱼官网注册后会获得 需要修改！！！！
//3858be3c20ceb6298575736cf27858a7
let appKey = '3858be3c20ceb6298575736cf27858a7';
//appName是您在网易七鱼管理后台中增加的APP的名字
let appName = 'unicornbeta';

//设定自定义链接点击回调事件名字
let UrlClickCallback = 'UrlClickCallback';
//设定消息未读数回调事件名字
let UnreadCountCallback = 'UnreadCountCallback';


class CustomButton extends React.Component {
  render() {
    return (
      <TouchableHighlight
        style={styles.button}
        underlayColor="#a5a5a5"
        onPress={this.props.onPress}>
        <Text style={styles.customButton}>{this.props.text}</Text>
      </TouchableHighlight>
    );
  }
}

class QiYuDemo extends Component {

    registerApp() {
        QiYu.registerAppId(appKey, appName);
        console.log('registerApp');
    }

    setCustomUIConfig() {
        QiYu.setCustomUIConfig(
            {
                sessionTipTextColor:'#CC00FF',
                sessionTipTextFontSize:13.0,
                customMessageTextColor:'#CC00FF',
                serviceMessageTextColor:'#CC00FF',
                messageTextFontSize:13.0,
                tipMessageTextColor:'#CC00FF',
                tipMessageTextFontSize:13.0,
                inputTextColor:'#CC00FF',
                inputTextFontSize:13.0,
                sessionBackgroundImage:'./qiyu/session_bg.png',
                sessionTipBackgroundColor:'#FFFFFF',
                customerHeadImage:'./qiyu/customer_head.png',
                serviceHeadImage:'./qiyu/service_head.png',
                sessionMessageSpacing:3.0,
                showHeadImage:true,
                naviBarStyleDark:true,
                showAudioEntry:true,
                showEmoticonEntry:true,
                autoShowKeyboard:true
            }
          );
        console.log('setCustomUIConfig');
    }

    setUrlClickCallback() {
        QiYu.setUrlClickWithEventName(UrlClickCallback);
        DeviceEventEmitter.addListener(UrlClickCallback, (info) => {
        console.log(info);
        });
        console.log('setUrlClickCallback');
    }

    setUnreadCountCallback() {
        QiYu.setUnreadCountWithEventName(UnreadCountCallback);
        DeviceEventEmitter.addListener(UnreadCountCallback, (info) => {
        console.log(info);
        });
        console.log('setUnreadCountCallback');
    }

    getUnreadCountCallback() {
        QiYu.getUnreadCountCallback((res)=>{
            console.log(res);
        });
        console.log('getUnreadCountCallback');
    }

    setUserInfo() {
        QiYu.setUserInfo(
            {
               userId:'uid10101010',
               data:'[{\"key\":\"real_name\", \"value\":\"土豪\"},{\"key\":\"mobile_phone\", \"hidden\":true},{\"key\":\"email\", \"value\":\"13800000000@163.com\"},{\"index\":0, \"key\":\"account\", \"label\":\"账号\", \"value\":\"zhangsan\", \"href\":\"http://example.domain/user/zhangsan\"},{\"index\":1, \"key\":\"sex\", \"label\":\"性别\", \"value\":\"先生\"},{\"index\":5, \"key\":\"reg_date\", \"label\":\"注册日期\", \"value\":\"2015-11-16\"},{\"index\":6, \"key\":\"last_login\", \"label\":\"上次登录时间\", \"value\":\"2015-12-22 15:38:54\"}]'
             });
        console.log('setUserInfo');
    }

    openServiceWindow() {
        QiYu.openServiceWindow(
            {
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
                	note:'￥1888',
                	show:true
                },
                
                sessionTitle:'网易七鱼'
            }
          );
        console.log('openServiceWindow');
    }

    logout() {
        QiYu.logout();
        console.log('logout');
    }

  render() {
    return (
      <View style={{marginTop:20}}>
        <Text style={styles.welcome}>
            ReactNative 网易七鱼 Demo
        </Text>
        <CustomButton text="初始化APP"
            onPress={this.registerApp}
        />
        <CustomButton text="自定义窗口样式"
            onPress={this.setCustomUIConfig}
        />
        <CustomButton text="设置自定义消息点击回调"
            onPress={this.setUrlClickCallback}
        />
        <CustomButton text="设置消息未读数改变回调"
            onPress={this.setUnreadCountCallback}
        />
        <CustomButton text="获取消息未读数"
            onPress={this.getUnreadCountCallback}
        />
        <CustomButton text="设置CRM个人信息"
            onPress={this.setUserInfo}
        />
        <CustomButton text="联系客服"
            onPress={this.openServiceWindow}
        />
        <CustomButton text="注销当前账号"
            onPress={this.logout}
        />
        </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  welcome: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
    color: '#ffffff',
    backgroundColor: '#CC00FF',
  },
  instructions: {
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
  customButton:{
    fontSize: 15,
    textAlign : 'center',
    margin: 10,
    color: '#000000',
  },
});

AppRegistry.registerComponent('QiYuDemo', () => QiYuDemo);
