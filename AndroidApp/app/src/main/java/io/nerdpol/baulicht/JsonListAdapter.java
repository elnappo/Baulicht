package io.nerdpol.baulicht;

import android.content.Context;
import android.os.AsyncTask;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;


public class JSONListAdapter extends ArrayAdapter<JSONObject> {

    protected String mUrl;
    protected Delegate mDelegate;
    protected LayoutInflater mInflater;

    public JSONListAdapter(Context context)
    {
        super(context, 0, new ArrayList<JSONObject>());

        mInflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    public void setDelegate(Delegate delegate) {
        mDelegate = delegate;
    }

    Delegate getDelegate() {
        return mDelegate;
    }

    public void setUrl(String url) {
        mUrl = url;
    }

    public String getUrl() {
        return mUrl;
    }

    public void reload() {
        // Clear all data
        clear();

        AsyncTask<String, Void, Void> task = new AsyncTask<String, Void, Void>() {
            JSONObject response;

            @Override
            protected void onPreExecute() {
                mDelegate.onBeginLoading();
            }

            @Override
            protected void onPostExecute(Void aVoid) {
                final Delegate delegate = getDelegate();

                if (response == null)
                    mDelegate.onError();
                else {
                    JSONArray content = delegate.contentFromResponse(response);
                    if (content == null)
                        mDelegate.onError();
                    else
                        fillFromData(content);
                }

                mDelegate.onEndLoading();
            }

            @Override
            protected Void doInBackground(String... params) {
                final String url = params[0];

                response = null;

                try {
                    DefaultHttpClient httpClient = new DefaultHttpClient();
                    HttpGet httpGet = new HttpGet(url);
                    HttpResponse httpResponse = httpClient.execute(httpGet);

                    HttpEntity entity = httpResponse.getEntity();

                    String responseString = EntityUtils.toString(entity);

                    response = new JSONObject(responseString);

                    return null;
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (JSONException e) {
                    e.printStackTrace();
                }

                return null;
            }
        };

        task.execute(getUrl());
    }

    protected void fillFromData(JSONArray content) {
        for(int i=0; i < content.length(); ++i) {
            JSONObject row = content.optJSONObject(i);
            add(row);
        }
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        final Delegate delegate = getDelegate();
        final JSONObject data = getItem(position);

        int id = delegate.cellForData(data);

        View view = mInflater.inflate(id, null);
        delegate.configureCell(view, data, position);
        return view;
    }

    public interface Delegate {
        public void onBeginLoading();
        public void onEndLoading();
        public void onError();

        public int cellForData(JSONObject data);
        public JSONArray contentFromResponse(JSONObject response);
        public void configureCell(View view, JSONObject data, int row);
    }
}
