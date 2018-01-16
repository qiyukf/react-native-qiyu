package com.awesomeproject;

import android.app.Application;

import com.facebook.react.ReactApplication;
import com.facebook.react.ReactNativeHost;
import com.facebook.react.ReactPackage;
import com.facebook.react.shell.MainReactPackage;
import com.qiyukf.unicorn.reactnative.QiyuSdkPackage;

import java.util.Arrays;
import java.util.List;

public class MainApplication extends Application implements ReactApplication {

    private final ReactNativeHost mReactNativeHost = new ReactNativeHost(this) {
        @Override
        public boolean getUseDeveloperSupport() {
            return BuildConfig.DEBUG;
        }

        @Override
        protected List<ReactPackage> getPackages() {
            return Arrays.asList(
                    new MainReactPackage(),
                    // appKey 和 appName 替换为自己的
                    new QiyuSdkPackage("3858be3c20ceb6298575736cf27858a7", "网易七鱼")
            );
        }
    };

    @Override
    public ReactNativeHost getReactNativeHost() {
        return mReactNativeHost;
    }
}
