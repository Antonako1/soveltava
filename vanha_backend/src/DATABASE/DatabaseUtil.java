package DATABASE;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

import Tables.User;

public class DatabaseUtil {
    private static final String URL = "mysql://localhost:3306/node_mysql_crud";
    private static final String USER = "root";
    private static final String PASSWORD = "";

    public Connection getConnection() throws SQLException {
        return DriverManager.getConnection(URL, USER, PASSWORD);
    }

    public static List<User> readAllUsers() throws SQLException {
        List<User> users = new ArrayList<>();
        String query = "SELECT * FROM users";
        try (Connection connection = getConnection();
                Statement statement = connection.createStatement();
                ResultSet resultSet = statement.executeQuery(query)) {
            // while (resultSet.next()) {
            //     users.add(new User(
            //         resultSet.getInt("id"),
            //         resultSet.getString("name"),
            //         resultSet.getString("email"),
            //         resultSet.getInt("age")
            //     ));
            // }
        }
        return users;
    }

    public static void updateUser(User user) throws SQLException {
        String query = "UPDATE users SET name = ?, email = ?, age = ? WHERE id = ?";
        try (Connection connection = getConnection();
                PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, user.getName());
            statement.setString(2, user.getEmail());
            statement.setInt(3, user.getAge());
            statement.setInt(4, user.getId());
            statement.executeUpdate();
        }
    }

    public static void deleteUser(int userId) throws SQLException {
        String query = "DELETE FROM users WHERE id = ?";
        try (Connection connection = getConnection();
                PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setInt(1, userId);
            statement.executeUpdate();
        }
    }

    public static void createUser(User user) throws SQLException {
        String query = "INSERT INTO users (name, email, age) VALUES (?, ?, ?)";
        try (Connection connection = getConnection();
                PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, user.getName());
            statement.setString(2, user.getEmail());
            statement.setInt(3, user.getAge());
            statement.executeUpdate();
        }
    }
}
