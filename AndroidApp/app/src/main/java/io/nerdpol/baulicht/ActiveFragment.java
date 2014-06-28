package io.nerdpol.baulicht;

import android.os.Bundle;


public class ActiveFragment extends BaseFragment {

    public ActiveFragment() {
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mListAdapter.setUrl(mSettings.formatUrl("/active"));
    }
}
