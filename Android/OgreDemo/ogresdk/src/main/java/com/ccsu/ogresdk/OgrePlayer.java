package com.ccsu.ogresdk;

import android.app.Fragment;
import android.content.Context;
import android.content.res.Configuration;
import android.os.Handler;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.widget.FrameLayout;

/**
 * Created by liuenbao on 12/16/16.
 */

public class OgrePlayer extends FrameLayout {

    private OgreSurfaceView mOgreSurfaceView = null;

    /////////////////////////////////////////////////////////
    //                    Constructors                     //
    /////////////////////////////////////////////////////////
    public OgrePlayer(Context context) {
        super(context);
        Init(context);
    }

    public OgrePlayer(Context context, AttributeSet attrs) {
        super(context, attrs);
        Init(context, attrs);
    }

    private void Init(Context context) {
        mOgreSurfaceView = new OgreSurfaceView(context);
        this.addView(mOgreSurfaceView);
    }

    private void Init(Context context, AttributeSet attrs) {
        mOgreSurfaceView = new OgreSurfaceView(context, attrs);
        this.addView(mOgreSurfaceView);
    }

    public void onDestroy() {
        // Handle onResume();
        mOgreSurfaceView.onDestroy();
    }

    public void onPause() {
        // Handle onPause();
        mOgreSurfaceView.onPause();
    }

    public void onResume() {
        // Handle onResume();
        mOgreSurfaceView.onResume();
    }

    public void onConfigurationChanged(Configuration newConfig) {
        mOgreSurfaceView.onConfigurationChanged(newConfig);
    }

    public void onWindowFocusChanged(boolean hasFocus) {
        mOgreSurfaceView.onWindowFocusChanged(hasFocus);
    }

    public boolean injectEvent(KeyEvent event) {
        return mOgreSurfaceView.injectEvent(event);
    }

    public boolean injectEvent(MotionEvent event) {
        return mOgreSurfaceView.injectEvent(event);
    }

}
