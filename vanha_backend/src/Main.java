import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.SQLException;

import HTTP.HTTP;
import DATABASE.DatabaseUtil;

public class Main {
    public static void main(String[] args) {
        try (Connection con = DatabaseUtil.getConnection()) {
            if (con.isClosed()) {
                System.out.println("Failed to connect to the database");
                return;
            }
        } catch (SQLException e) {
            System.out.println("Database connection error: " + e.getMessage());
            return;
        }

        try {
            HttpServer server = HttpServer.create(new InetSocketAddress(9090), 0);
            server.createContext("/api", new HTTP.IPReq());

            System.out.println("Server is running on http://localhost:9090/");
            server.start();
        } catch (IOException e) {
            System.out.println("Error starting server: " + e.getMessage());
        }
    }
}
