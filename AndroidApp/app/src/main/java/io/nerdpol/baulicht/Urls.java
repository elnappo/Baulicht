package io.nerdpol.baulicht;

public class Urls {
    public static String HOST = "10.0.0.49:8000";

    public static String INSERT_URL = String.format("http://%s/api/queue/", HOST);
    public static String QUEUE_URL = String.format("http://%s/api/queue/", HOST);
    public static String ACTIVE_URL = String.format("http://%s/api/active/", HOST);
}
