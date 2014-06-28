package io.nerdpol.baulicht;

import android.content.Context;
import android.content.SharedPreferences;


public class Settings {

    protected SharedPreferences prefs;

    public Settings(Context context) {
        prefs = context.getSharedPreferences("settings", Context.MODE_PRIVATE);
    }

    public String getServerAddress() {
        return prefs.getString("serverAddress", "http://baulicht.nerdpol.io/api");
    }

    public void setServerAddress(String serverAddress) {
        SharedPreferences.Editor editor = prefs.edit();
        editor.putString("serverAddress", serverAddress);
        editor.apply();
    }

    public String formatUrl(String path) {
        return getServerAddress() + path;
    }
}
