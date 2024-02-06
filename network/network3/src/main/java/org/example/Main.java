package org.example;

import org.json.JSONArray;
import org.json.JSONObject;

import java.math.BigDecimal;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.ArrayList;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

public class Main {
    private static BigDecimal lat;
    private static BigDecimal lng;
    private static int id =-1;
    private static HttpClient client;
    private static String coordinatesKey = "4369fd00-924b-4300-8570-4dec869b771d";
    private static String weatherKey = "6d04d5503e07d23e097215c975f9f08c";
    private static String area = "Omsk";
    private static String hitsLimit = "1";

    public static void main(String[] args) {

        client = HttpClient.newHttpClient();

        CompletableFuture<String> future1
                = CompletableFuture.supplyAsync(() -> {
            try {
                //Thread.sleep(100);
                ArrayList<BigDecimal> tmp = getCoordinates("Novosibirsk");
                getWeather(tmp.get(0), tmp.get(1), "Novosibirsk");
                //System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getCoordinates");
            }
            return null;
        });
        CompletableFuture<String> future2
                = CompletableFuture.supplyAsync(() -> {
            try {
                //Thread.sleep(100);
                ArrayList<BigDecimal> tmp = getCoordinates("Moscow");
                getWeather(tmp.get(0), tmp.get(1), "Moscow");
                //System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getCoordinates");
            }
            return null;
        });
        CompletableFuture<String> future3
                = CompletableFuture.supplyAsync(() -> {
            try {
                //Thread.sleep(100);
                ArrayList<BigDecimal> tmp = getCoordinates("Siberia");
                getWeather(tmp.get(0), tmp.get(1), "Siberia");
                //System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getCoordinates");
            }
            return null;
        });

        CompletableFuture<String> future4
                = CompletableFuture.supplyAsync(() -> {
            try {
                //Thread.sleep(100);
                ArrayList<BigDecimal> tmp = getCoordinates("Spb");
                getWeather(tmp.get(0), tmp.get(1), "Spb");
                //System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getCoordinates");
            }
            return null;
        });

        CompletableFuture<Void> combinedFuture
                = CompletableFuture.allOf(future1, future2, future3, future4);

        try {
            combinedFuture.get();
        } catch (InterruptedException | ExecutionException e) {
            throw new RuntimeException(e);
        }


        /*CompletableFuture<Void> futures = CompletableFuture.runAsync(()-> {
            try {
                Thread.sleep(100);
                ArrayList<BigDecimal> tmp = getCoordinates("Novosibirsk");
                getWeather(tmp.get(0), tmp.get(1), "Novosibirsk");
                //System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getCoordinates");
            }
        }).thenRunAsync(() -> {
            try {
                ArrayList<BigDecimal> tmp = getCoordinates("Russia");
                getWeather(tmp.get(0), tmp.get(1), "Russia");
                //System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getCoordinates");
            }
        }).thenRunAsync(() -> {
            try {
                ArrayList<BigDecimal> tmp = getCoordinates("Siberia");
                getWeather(tmp.get(0), tmp.get(1), "Siberia");
                //System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getCoordinates");
            }
        }).thenRunAsync(() -> {
            try {
                ArrayList<BigDecimal> tmp = getCoordinates("Moscow");
                getWeather(tmp.get(0), tmp.get(1), "Moscow");
                //System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getCoordinates");
            }
        }).thenRunAsync(() -> {
            try {
                ArrayList<BigDecimal> tmp = getCoordinates("Spb");
                getWeather(tmp.get(0), tmp.get(1), "Spb");
                //System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getCoordinates");
            }
        });*/

        /*try {
            futures.get();
        } catch (InterruptedException | ExecutionException e) {
            throw new RuntimeException(e);
        }*/

        /*getCoordinates();
        System.out.println();
        getWeather();
        System.out.println();
        getAttractions();
        System.out.println();
        getAttractionsById(id);*/
        /*CompletableFuture<Void> futures = CompletableFuture.runAsync(()-> {
            try {
                getCoordinates();
                System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getCoordinates");
            }
        }).thenRun(() -> {
            try {
                getWeather();
                System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getWeather");
            }
        }).thenRunAsync(() -> {
            try {
                getAttractions();
                System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getAttractions");
            }
        }).thenRun(() -> {
            try {
                getAttractionsById(id);
                System.out.println();
            } catch (ExecutionException | InterruptedException e) {
                System.out.println("error in getAttractionsById");
            }
        });*/

        /*try {
            futures.get();
        } catch (InterruptedException | ExecutionException e) {
            throw new RuntimeException(e);
        }*/


    }

    private static ArrayList<BigDecimal> getCoordinates(String area) throws ExecutionException, InterruptedException {
        ArrayList<BigDecimal> arr = new ArrayList<>();
        HttpRequest request = HttpRequest.newBuilder(
                        URI.create("https://graphhopper.com/api/1/geocode?q="+area+"&limit="+hitsLimit+"&key="+coordinatesKey))
                .GET()
                .build();

        CompletableFuture<HttpResponse<String>> responseFuture = client.sendAsync(request, HttpResponse.BodyHandlers.ofString());

        String response = responseFuture.get().body();
        //System.out.println("response "+response);

        JSONObject obj = new JSONObject(response);
        JSONArray hits = obj.getJSONArray("hits");
        int n = hits.length();
        for (int i = 0; i < n; ++i) {
            JSONObject hit = hits.getJSONObject(i);

            JSONObject point = hit.getJSONObject("point");

            BigDecimal val1 = point.getBigDecimal("lat");
            BigDecimal val2 = point.getBigDecimal("lng");

            arr.add(val1);
            arr.add(val2);

            return arr;
        }
        return null;
    }

    private static void getWeather(BigDecimal lat, BigDecimal lng, String area) throws ExecutionException, InterruptedException {
        //System.out.println("in getWeather");
        HttpRequest request = HttpRequest.newBuilder(
                        URI.create("https://api.openweathermap.org/data/2.5/weather?lat="+lat+"&lon="+lng+"&appid="+weatherKey))
                .GET()
                .build();

        CompletableFuture<HttpResponse<String>> responseFuture = client.sendAsync(request, HttpResponse.BodyHandlers.ofString());

        String response = responseFuture.get().body();
        //System.out.println("response "+response);

        JSONObject obj = new JSONObject(response);
        int code = obj.getInt("cod");

        if(code == 400){
            System.out.println("weather not detect");
            return;
        }

        JSONObject main = obj.getJSONObject("main");
        System.out.println("area "+area+"  temp "+main.getBigDecimal("temp"));
    }

    private static void getAttractions() throws ExecutionException, InterruptedException {
        //System.out.println("in getAttractions");
        HttpRequest request = HttpRequest.newBuilder(
                        URI.create("https://kudago.com/public-api/v1.4/places/?lat="+lat+"&lon="+lng+"&radius=1000000"))
                .GET()
                .build();

        CompletableFuture<HttpResponse<String>> responseFuture = client.sendAsync(request, HttpResponse.BodyHandlers.ofString());

        String response = responseFuture.get().body();
        //System.out.println("response "+response);

        JSONObject obj = new JSONObject(response);
        try{
            String detail = obj.getString("detail");
            if(detail.equals("Введите число.")){
                System.out.println("attraction not found");
                return;
            }
        }catch (RuntimeException ignored){

        }


        JSONArray results = obj.getJSONArray("results");
        int n = results.length();

        for (int i = 0; i < n; ++i) {
            System.out.println();
            JSONObject tmp = results.getJSONObject(i);
            id = tmp.getInt("id");
            System.out.println("id "+tmp.getInt("id"));
            System.out.println("title "+tmp.getString("title"));
            System.out.println();
        }
        //System.out.println("after");
    }

    private static void getAttractionsById(int id) throws ExecutionException, InterruptedException {
        //System.out.println("in getAttractionsById");
        if(id ==-1){
            System.out.println("there are no attraction");
            return;
        }
        HttpRequest request = HttpRequest.newBuilder(
                        URI.create("https://kudago.com/public-api/v1.4/places/"+id+"/"))
                .GET()
                .build();

        CompletableFuture<HttpResponse<String>> responseFuture = client.sendAsync(request, HttpResponse.BodyHandlers.ofString());

        String response = responseFuture.get().body();
        //System.out.println("response "+response);

        JSONObject tmp = new JSONObject(response);

        System.out.println("id "+tmp.getInt("id"));
        System.out.println("title "+tmp.getString("title"));
        System.out.println("address "+tmp.getString("address"));
        System.out.println("timetable "+tmp.getString("timetable"));
        System.out.println("phone "+tmp.getString("phone"));
        System.out.println("body_text "+tmp.getString("body_text"));
        System.out.println("description "+tmp.getString("description"));
        System.out.println("site_url "+tmp.getString("site_url"));
        System.out.println("subway "+tmp.getString("subway"));
    }
}