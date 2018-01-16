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
  TextInput,
  View,
  TouchableHighlight,
  NativeModules,
  DeviceEventEmitter,
  findNodeHandle,
  Dimensions,
} from 'react-native';

var QiYu = NativeModules.QiYu;

var WINDOW_WIDTH = Dimensions.get('window').width
var customer_head = require('./qiyu/customer_head.png');
var service_head = require('./qiyu/service_head.png');
var session_bg = require('./qiyu/session_bg.png');

console.log(QiYu);

//appKey是您在网易七鱼官网注册后会获得 需要修改！！！！
//3858be3c20ceb6298575736cf27858a7,5d317772fbec8f376a913f0951f2242d,55bb9a1b346ceb3899eef229e6271d7e
let appKey = '5d317772fbec8f376a913f0951f2242d';
//appName是您在网易七鱼管理后台中增加的APP的名字
let appName = 'unicornbeta';

//设定自定义链接点击回调事件名字
let UrlClickCallback = 'UrlClickCallback';
//设定消息未读数回调事件名字
let UnreadCountCallback = 'UnreadCountCallback';


export default class CustomButton extends React.Component {
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

var defaultUIParams = {
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
};

var defaultSessionParams = {
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
    sessionTitle:'网易七鱼',
    groupId:0,
    staffId:0,
    robotId:0,
    vipLevel:0,
    robotFirst:false,
    faqTemplateId:0,
    showCloseSessionEntry:true,
    showQuitQueue:true
};

class QiYuDemoForReactNative extends Component {
    constructor(props) {
        super(props);
        this.state = {
            showViewType: 0,    //0,显示默认窗口;1.显示自定义样式配置窗口;2.显示聊天参数配置窗口
            uiParams: JSON.stringify(defaultUIParams).replace(/,/g, ',\n'),
            sessionParams: JSON.stringify(defaultSessionParams).replace(/,/g, ',\n'),
        };
    }

    registerApp() {
        QiYu.registerAppId(appKey, appName);
        console.log('registerApp');
    }

    setCustomUIConfig() {
        this.setState({showViewType: 1})
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
        QiYu.getUnreadCountCallback((res) => {
            console.log(res);
        });
        console.log('getUnreadCountCallback');
    }

    cleanCacheCallback() {
        QiYu.cleanCache();
        console.log('cleanCacheCallback');
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
        this.setState({showViewType: 2})
        console.log('openServiceWindow');
    }

    logout() {
        QiYu.logout();
        console.log('logout');
    }

    render() {
        if (this.state.showViewType == 1) {
            return this.renderCustomUI();
        } else if (this.state.showViewType == 2) {
            return this.renderQiYuView();
        } else {
            return (
                <View style={{marginTop:20}} ref={(view)=>{this._rootView = view;}}>
                  <Text style={styles.welcome}>
                      ReactNative 网易七鱼 Demo
                  </Text>
                  <CustomButton text="初始化APP"
                      onPress={this.registerApp}
                  />
                  <CustomButton text="自定义窗口样式"
                      onPress={this.setCustomUIConfig.bind(this)}
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
                      onPress={this.openServiceWindow.bind(this)}
                  />
                  <CustomButton text="清理缓存"
                      onPress={this.cleanCacheCallback}
                  />
                  <CustomButton text="注销当前账号"
                      onPress={this.logout}
                  />
                </View>
            );
        }
    }

    renderCustomUI() {
        return (
            <View style={{flex: 1, padding: 16}}>
            <View style={{flex: 1, borderColor: 'grey', borderWidth: 1}}>
            <TextInput style={{flex: 1, fontSize: 16, color: 'black', textAlignVertical: 'top'}}
            placeholder="请输入你的跟进结果"
            value={this.state.uiParams}
            multiline={true}
            onChangeText={(text) => this.setState({uiParams: text})}/>
            </View>
            <TouchableHighlight style={styles.buttonBg} onPress={() => {
                this.setState({showViewType: 0})
                QiYu.setCustomUIConfig(JSON.parse(this.state.uiParams))
            }}>
            <Text style={styles.text}>确定</Text>
            </TouchableHighlight>
            </View>
        );
    }

    renderQiYuView() {
        return (
            <View style={{flex: 1, padding: 16}}>
            <View style={{flex: 1, borderColor: 'grey', borderWidth: 1}}>
            <TextInput style={{flex: 1, fontSize: 16, color: 'black', textAlignVertical: 'top'}}
            placeholder="请输入你的跟进结果"
            value={this.state.sessionParams}
            multiline={true}
            onChangeText={(text) => this.setState({sessionParams: text})}/>
            </View>
            <TouchableHighlight style={styles.buttonBg} onPress={() => {
                this.setState({showViewType: 0})
                QiYu.openServiceWindow(JSON.parse(this.state.sessionParams))
            }}>
            <Text style={styles.text}>确定</Text>
            </TouchableHighlight>
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
  buttonBg: {
    width: WINDOW_WIDTH - 32,
    height: 40,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#2196F3',
    marginTop: 16,
  },
});

AppRegistry.registerComponent('QiYuDemoForReactNative', () => QiYuDemoForReactNative);
