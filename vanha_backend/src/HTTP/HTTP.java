package HTTP;
import HTTP.*;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import java.io.IOException;
import java.io.OutputStream;

public class HTTP {
    private static String IPRes(String requesterIP) {
        return "Hello, World!" + "\n" + "Your IP is: " + requesterIP;
    }

    public static class IPReq implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String requesterIP = exchange.getRemoteAddress().getAddress().getHostAddress();

            String response = IPRes(requesterIP);

            System.out.println("Received a request from IP: " + requesterIP);

            exchange.sendResponseHeaders(200, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }
    }
}
