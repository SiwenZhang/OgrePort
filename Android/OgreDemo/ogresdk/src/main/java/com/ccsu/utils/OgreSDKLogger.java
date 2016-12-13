package com.ccsu.utils;

import android.util.Log;

/**
 * Created by liuenbao on 12/13/16.
 */

public class OgreSDKLogger {

    private boolean mLogEnabled = true;
    private String mTag = "";

    public OgreSDKLogger(String tag) {
        mTag = tag;
    }

    public void debug(String debug) {
        if (!mLogEnabled) {
            return ;
        }
        Log.d(mTag, debug);
    }

    public void info(String info) {
        if (!mLogEnabled) {
            return ;
        }
        Log.i(mTag, info);
    }

    public void warn(String warn) {
        if (!mLogEnabled) {
            return ;
        }
        Log.w(mTag, warn);
    }

    public void error(String error) {
        if (!mLogEnabled) {
            return ;
        }
        Log.e(mTag, error);
    }

}
