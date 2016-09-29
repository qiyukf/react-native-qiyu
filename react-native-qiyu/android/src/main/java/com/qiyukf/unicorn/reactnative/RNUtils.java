package com.qiyukf.unicorn.reactnative;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Color;
import android.text.TextUtils;

import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.ReadableType;

/**
 * Created by hzwangchenyan on 2016/9/12.
 */
public class RNUtils {

    public static String optString(ReadableMap params, String key) {
        String value = "";
        if (params != null && params.hasKey(key) && params.getType(key) == ReadableType.String) {
            value = params.getString(key);
        }
        return value;
    }

    public static boolean optBoolean(ReadableMap params, String key, boolean defValue) {
        boolean value = defValue;
        if (params != null && params.hasKey(key) && params.getType(key) == ReadableType.Boolean) {
            value = params.getBoolean(key);
        }
        return value;
    }

    public static int optInt(ReadableMap params, String key) {
        int value = 0;
        if (params != null && params.hasKey(key) && params.getType(key) == ReadableType.Number) {
            value = params.getInt(key);
        }
        return value;
    }

    public static double optDouble(ReadableMap params, String key) {
        double value = 0;
        if (params != null && params.hasKey(key) && params.getType(key) == ReadableType.Number) {
            value = params.getDouble(key);
        }
        return value;
    }

    public static ReadableMap optReadableMap(ReadableMap params, String key) {
        ReadableMap value = null;
        if (params != null && params.hasKey(key) && params.getType(key) == ReadableType.Map) {
            value = params.getMap(key);
        }
        return value;
    }

    public static int parseColor(String colorString) {
        int color = 0;
        try {
            color = Color.parseColor(colorString);
        } catch (Exception e) {
            // e.printStackTrace();
        }
        return color;
    }

    public static String getImageUri(Context context, String resName) {
        if (TextUtils.isEmpty(resName)) {
            return null;
        }
        if (resName.startsWith("./")) {
            resName = resName.replace("./", "");
        }
        if (resName.contains(".")) {
            resName = resName.substring(0, resName.indexOf("."));
        }
        resName = resName.replace("/", "_");
        Resources res = context.getResources();
        String pkgName = context.getPackageName();
        int resId = res.getIdentifier(resName, "drawable", pkgName);
        if (resId > 0) {
            return "res:///" + resId;
        }
        return null;
    }
}
