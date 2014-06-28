package io.nerdpol.baulicht;

import android.os.Bundle;
import android.support.v4.app.ListFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONObject;

import uk.co.senab.actionbarpulltorefresh.library.ActionBarPullToRefresh;
import uk.co.senab.actionbarpulltorefresh.library.Options;
import uk.co.senab.actionbarpulltorefresh.library.PullToRefreshLayout;
import uk.co.senab.actionbarpulltorefresh.library.listeners.OnRefreshListener;


public class BaseFragment extends ListFragment implements JSONListAdapter.Delegate, OnRefreshListener {

    protected Settings mSettings;
    protected JSONListAdapter mListAdapter;
    protected PullToRefreshLayout mPullToRefreshLayout;
    protected ProgressBar mProgressBar;
    protected boolean isLoading = false;

    public BaseFragment() {
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mSettings = new Settings(getActivity());

        mListAdapter = new JSONListAdapter(getActivity());
        mListAdapter.setDelegate(this);
        setListAdapter(mListAdapter);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_base, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view,savedInstanceState);

        // This is the View which is created by ListFragment
        ViewGroup viewGroup = (ViewGroup) view;

        // We need to create a PullToRefreshLayout manually
        mPullToRefreshLayout = new PullToRefreshLayout(viewGroup.getContext());

        // We can now setup the PullToRefreshLayout
        ActionBarPullToRefresh.from(getActivity())

                // We need to insert the PullToRefreshLayout into the Fragment's ViewGroup
                .insertLayoutInto(viewGroup)

                        // We need to mark the ListView and it's Empty View as pullable
                        // This is because they are not dirent children of the ViewGroup
                .theseChildrenArePullable(getListView(), getListView().getEmptyView())

                        // We can now complete the setup as desired
                .listener(this)
                .options(Options.create()
                        //.scrollDistance(.75f)
                        .build())
                .setup(mPullToRefreshLayout);

        // Find the progress bar
        mProgressBar = (ProgressBar)view.findViewById(R.id.progressBar);
        updateProgressBar();

        if (mListAdapter.isEmpty() && !isLoading)
            mListAdapter.reload();
    }

    protected void updateProgressBar() {
        if (mProgressBar != null)
            mProgressBar.setVisibility(isLoading ? View.VISIBLE : View.GONE);
    }

    @Override
    public void onBeginLoading() {
        isLoading = true;
        updateProgressBar();
    }

    @Override
    public void onEndLoading() {
        isLoading = false;
        updateProgressBar();
    }

    @Override
    public void onError() {
        Toast.makeText(getActivity(), R.string.error_loading_data, Toast.LENGTH_SHORT)
                .show();
    }

    @Override
    public int cellForData(JSONObject data) {
        return android.R.layout.simple_list_item_1;
    }

    @Override
    public JSONArray contentFromResponse(JSONObject response) {
        return response.optJSONArray("results");
    }

    @Override
    public void configureCell(View view, JSONObject data, int row) {
        TextView titleView = (TextView)view;
        if (titleView != null)
            titleView.setText(data.optString("text"));
    }

    @Override
    public void onRefreshStarted(View view) {
        mPullToRefreshLayout.setRefreshComplete();
        mListAdapter.reload();
    }
}
