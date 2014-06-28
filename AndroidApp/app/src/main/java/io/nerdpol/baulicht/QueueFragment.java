package io.nerdpol.baulicht;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import org.json.JSONObject;


public class QueueFragment extends BaseFragment {

    public QueueFragment() {
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mListAdapter.setUrl(mSettings.formatUrl("/queue"));
    }

    @Override
    public int cellForData(JSONObject data) {
        return R.layout.item_queue;
    }

    @Override
    public void configureCell(View view, JSONObject data, int row) {
        // Disable clicking on these items
        view.setClickable(false);
        view.setLongClickable(false);

        TextView titleView = (TextView)view.findViewById(R.id.title);
        if (titleView != null)
            titleView.setText(data.optString("text"));

        TextView nameView = (TextView)view.findViewById(R.id.subtitle);
        if (nameView != null) {
            String name = data.optString("name").toLowerCase();
            if (name.length() == 0)
                name = "unbekannt";

            nameView.setText(String.format("eingetragen von %s", name));
        }
    }
}
