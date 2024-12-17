package Tables;

public class User {
    private int id;
    private String name;
    private String email;
    private int age;
    private String passwordHash;
    private double balance;

    public User(int id, String name, String email, int age, String passwordHash, double balance) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.age = age;
        this.passwordHash = passwordHash;
        this.balance = balance;
    }

    public int getId() {return id;}
    public void setId(int id) {this.id = id;}

    public String getName() {return name;}
    public void setName(String name) {this.name = name;}

    public String getEmail() {return email;}
    public void setEmail(String email) {this.email = email;}

    public int getAge() {return age;}
    public void setAge(int age) {this.age = age;}

    public String getPasswordHash() {return passwordHash;}
    public void setPasswordHash(String passwordHash) {this.passwordHash = passwordHash;}

    public double getBalance() {return balance;}
    public void setBalance(double balance) {this.balance = balance;}

    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", email='" + email + '\'' +
                ", age=" + age +
                ", passwordHash='" + passwordHash + '\'' +
                ", balance=" + balance +
                '}';
    }
}
