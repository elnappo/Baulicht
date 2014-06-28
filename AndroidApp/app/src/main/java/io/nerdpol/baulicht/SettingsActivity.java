package io.nerdpol.baulicht;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.widget.EditText;


public class SettingsActivity extends ActionBarActivity {

    protected EditText mServerAddress;
    protected Settings mSettings;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        mSettings = new Settings(this);

        mServerAddress = (EditText)findViewById(R.id.serverAddress);
        mServerAddress.setText(mSettings.getServerAddress());
    }

    @Override
    protected void onStop() {
        super.onStop();

        String serverAddress = mServerAddress.getText().toString();
        mSettings.setServerAddress(serverAddress);
    }
}
