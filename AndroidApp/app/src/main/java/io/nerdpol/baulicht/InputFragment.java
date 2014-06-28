package io.nerdpol.baulicht;

import android.app.ProgressDialog;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;


public class InputFragment extends Fragment {

    protected EditText textField;
    protected EditText nameField;
    protected Button button;
    protected Settings settings;

    public InputFragment() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_input, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        textField = (EditText)view.findViewById(R.id.text);
        nameField = (EditText)view.findViewById(R.id.name);
        button = (Button)view.findViewById(R.id.button);

        settings = new Settings(getActivity());

        final View contextView = view;

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AsyncTask<String, Void, Void> task = new AsyncTask<String, Void, Void>() {
                    JSONObject response;
                    ProgressDialog progressDialog;

                    @Override
                    protected void onPreExecute() {
                        progressDialog = ProgressDialog.show(getActivity(), "Sende Daten ...", null, true);
                    }

                    @Override
                    protected void onPostExecute(Void aVoid) {
                        // Hide the progress dialog again
                        progressDialog.hide();
                        progressDialog = null;

                        if (response == null) {
                            Toast.makeText(contextView.getContext(), "Fehler beim Senden der Daten", Toast.LENGTH_LONG)
                                    .show();
                        } else {
                            // Empty the text field
                            textField.setText("");

                            // FIXME: We are not allowed to access this activity here
                            MainActivity activity = (MainActivity)getActivity();
                            activity.setCurrentPage(2);
                        }
                    }

                    @Override
                    protected Void doInBackground(String... strings) {
                        final String url = strings[0];

                        try {
                            DefaultHttpClient httpClient = new DefaultHttpClient();

                            HttpPost httpPost = new HttpPost(url);
                            httpPost.setEntity(getEntity());

                            HttpResponse httpResponse = httpClient.execute(httpPost);

                            HttpEntity entity = httpResponse.getEntity();

                            String responseString = EntityUtils.toString(entity);

                            response = new JSONObject(responseString);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        } catch (ClientProtocolException e) {
                            e.printStackTrace();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }

                        return null;
                    }
                };

                task.execute(settings.formatUrl("/queue"));
            }
        });
    }

    protected HttpEntity getEntity() {
        final String name = nameField.getText().toString();
        final String text = textField.getText().toString();

        List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(2);
        nameValuePairs.add(new BasicNameValuePair("text", text));
        nameValuePairs.add(new BasicNameValuePair("name", name));
        try {
            return new UrlEncodedFormEntity(nameValuePairs);
        } catch (UnsupportedEncodingException e) {
            return null;
        }
    }
}
