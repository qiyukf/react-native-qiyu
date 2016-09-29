import React, { Component } from 'react';
import {
	AppRegistry,
	StyleSheet,
	Text,
	View,
	Image,
	TextInput,
	TouchableHighlight,
	ToastAndroid,
	DeviceEventEmitter,
	Dimensions,
} from 'react-native';

import QiYu from 'react-native-qiyu';

var WINDOW_WIDTH = Dimensions.get('window').width
var session_bg = require('./qiyu/session_bg.png')
var customer_head = require('./qiyu/customer_head.png')
var service_head = require('./qiyu/service_head.png')

var defaultUiParams={
	sessionTipTextColor:'#CC00FF',
	sessionTipTextFontSize: 20,
	customMessageTextColor: '#CC00FF',
	serviceMessageTextColor: '#CC00FF',
	messageTextFontSize: 20,
	tipMessageTextColor: '#CC00FF',
	tipMessageTextFontSize: 20,
	inputTextColor: '#CC00FF',
	inputTextFontSize: 20,
	sessionBackgroundImage: './qiyu/session_bg.png',
	sessionTipBackgroundColor: '#000000',
	customerHeadImage: './qiyu/customer_head.png',
	serviceHeadImage: './qiyu/service_head.png',
	sessionMessageSpacing: 2,
	showHeadImage: true,
	showAudioEntry: false,
	showEmoticonEntry: false,
	autoShowKeyboard: false
}

class AwesomeProject extends Component {
	constructor(props) {
		super(props);
		this.state = {
			inputUiParams: false,
			uiParams: JSON.stringify(defaultUiParams).replace(/,/g, ',\n'),
		}
	}

	componentWillMount() {
		DeviceEventEmitter.addListener('UrlClickEvent', function(e: Event) {
			ToastAndroid.show("点击链接："+e.url, ToastAndroid.SHORT)
		});
		DeviceEventEmitter.addListener('UnreadCountEvent', function(e: Event) {
			ToastAndroid.show("未读消息数："+e.unreadCount, ToastAndroid.SHORT)
		});
	}

	onPress(which){
		switch(which){
			case "registerAppId":
			this.registerAppId()
			break;
			case "openServiceWindow":
			this.openServiceWindow()
			break;
			case "setCustomUIConfig":
			this.setCustomUIConfig()
			break;
			case "setUrlClickWithEventName":
			this.setUrlClickWithEventName()
			break;
			case "setUnreadCountWithEventName":
			this.setUnreadCountWithEventName()
			break;
			case "getUnreadCountCallback":
			this.getUnreadCountCallback()
			break;
			case "setUserInfo":
			this.setUserInfo()
			break;
			case "logout":
			this.logout()
			break;
		}
	}

	registerAppId(){
		QiYu.registerAppId('七鱼管理后台的appKey', '七鱼管理后台的App名称')
	}

	openServiceWindow(){
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
		QiYu.openServiceWindow(params)
	}

	setCustomUIConfig(){
		this.setState({inputUiParams: true})
	}

	setUrlClickWithEventName(){
		QiYu.setUrlClickWithEventName("UrlClickEvent")
	}

	setUnreadCountWithEventName(){
		QiYu.setUnreadCountWithEventName("UnreadCountEvent")
	}

	getUnreadCountCallback(){
		QiYu.getUnreadCountCallback((unreadCount) => {
			ToastAndroid.show("未读消息数："+unreadCount, ToastAndroid.SHORT)
		})
	}

	setUserInfo(){
		var params = {
			userId:'uid10101010',
			data:'[{\"key\":\"real_name\", \"value\":\"土豪\"},{\"key\":\"mobile_phone\", \"hidden\":true},{\"key\":\"email\", \"value\":\"13800000000@163.com\"},{\"index\":0, \"key\":\"account\", \"label\":\"账号\", \"value\":\"zhangsan\", \"href\":\"http://example.domain/user/zhangsan\"},{\"index\":1, \"key\":\"sex\", \"label\":\"性别\", \"value\":\"先生\"},{\"index\":5, \"key\":\"reg_date\", \"label\":\"注册日期\", \"value\":\"2015-11-16\"},{\"index\":6, \"key\":\"last_login\", \"label\":\"上次登录时间\", \"value\":\"2015-12-22 15:38:54\"}]'
		}
		QiYu.setUserInfo(params)
	}

	logout(){
		QiYu.logout()
	}

	render() {
		if(!this.state.inputUiParams){
			return (
				<View style={styles.container}>
				<Image source={require('./qiyu/logo.png')} />
				<TouchableHighlight style={styles.buttonBg} onPress={() =>
					this.onPress("registerAppId")
				}>
				<Text style={styles.text}>初始化</Text>
				</TouchableHighlight>
				<TouchableHighlight style={styles.buttonBg} onPress={() =>
					this.onPress("openServiceWindow")
				}>
				<Text style={styles.text}>联系客服</Text>
				</TouchableHighlight>
				<TouchableHighlight style={styles.buttonBg} onPress={() =>
					this.onPress("setCustomUIConfig")
				}>
				<Text style={styles.text}>自定义窗口</Text>
				</TouchableHighlight>
				<TouchableHighlight style={styles.buttonBg} onPress={() =>
					this.onPress("setUrlClickWithEventName")
				}>
				<Text style={styles.text}>设置自定义消息点击回调</Text>
				</TouchableHighlight>
				<TouchableHighlight style={styles.buttonBg} onPress={() =>
					this.onPress("setUnreadCountWithEventName")
				}>
				<Text style={styles.text}>设置未读消息数改变回调</Text>
				</TouchableHighlight>
				<TouchableHighlight style={styles.buttonBg} onPress={() =>
					this.onPress("getUnreadCountCallback")
				}>
				<Text style={styles.text}>获取未读消息数</Text>
				</TouchableHighlight>
				<TouchableHighlight style={styles.buttonBg} onPress={() =>
					this.onPress("setUserInfo")
				}>
				<Text style={styles.text}>设置CRM个人信息</Text>
				</TouchableHighlight>
				<TouchableHighlight style={styles.buttonBg} onPress={() =>
					this.onPress("logout")
				}>
				<Text style={styles.text}>注销当前账号</Text>
				</TouchableHighlight>
				</View>
				);
		}else{
			return this.renderInputUiParams()
		}
	}

	renderInputUiParams(){
		return (
			<View style={{flex: 1, padding: 16}}>
			<View style={{flex: 1, borderColor: 'grey', borderWidth: 1}}>
			<TextInput style={{flex: 1, fontSize: 16, color: 'black', textAlignVertical: 'top'}}
			underlineColorAndroid={'#0000'}
			placeholder="请输入你的跟进结果"
			value={this.state.uiParams}
			multiline={true}
			onChangeText={(text) => this.setState({uiParams: text})}/>
			</View>

			<TouchableHighlight style={styles.buttonBg} onPress={() => {
				this.setState({inputUiParams: false})
				QiYu.setCustomUIConfig(JSON.parse(this.state.uiParams))
			}}>
			<Text style={styles.text}>确定</Text>
			</TouchableHighlight>
			</View>
			)
	}
}

const styles = StyleSheet.create({
	container: {
		flex: 1,
		padding: 16,
		justifyContent: 'flex-start',
		alignItems: 'center'
	},
	buttonBg: {
		width: WINDOW_WIDTH - 32,
		height: 40,
		justifyContent: 'center',
		alignItems: 'center',
		backgroundColor: '#2196F3',
		marginTop: 16,
	},
	text: {
		fontSize: 16,
		textAlign: 'center',
		color: '#FFFFFF',
	}
});

AppRegistry.registerComponent('AwesomeProject', () => AwesomeProject);
