package com.ccsu.ogresdk;

import android.app.Activity;
import android.content.Context;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.inputmethod.InputMethodManager;

import com.ccsu.utils.OgreSDKLogger;

/**
 * Created by liuenbao on 12/11/16.
 */

public class OgrePlayerActivity extends Activity {

    private static final OgreSDKLogger logger = new OgreSDKLogger(OgrePlayerActivity.class.getSimpleName());

    protected OgrePlayer mOgrePlayer = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mOgrePlayer = new OgrePlayer(this);
        setContentView(mOgrePlayer);
    }

    @Override
    public void onDestroy() {
        mOgrePlayer.onDestroy();
        super.onDestroy();
    }

    @Override
    public void onPause() {
        mOgrePlayer.onPause();
        super.onPause();
    }

    @Override
    public void onResume() {
        super.onResume();
        mOgrePlayer.onResume();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        mOgrePlayer.onConfigurationChanged(newConfig);
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);

        mOgrePlayer.onWindowFocusChanged(hasFocus);
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        return event.getAction() == KeyEvent.ACTION_MULTIPLE ? mOgrePlayer.injectEvent(event) : super.dispatchKeyEvent(event);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        return mOgrePlayer.injectEvent(event);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        return mOgrePlayer.injectEvent(event);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return mOgrePlayer.injectEvent(event);
    }

    @Override
    public boolean onGenericMotionEvent(MotionEvent event) {
        return mOgrePlayer.injectEvent(event);
    }

}
