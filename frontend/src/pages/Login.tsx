import { useEffect, useState, useContext } from "react";
import { server_url, UserInformation } from "../utils/Data";
import styles from "../styles/login.module.css";
import { compare_auth_token, comparePassword, generate_auth_token, hashPassword, LoginRequest } from "../utils/hash";
import { BaseInformationContext } from "../App";

enum LoginOrRegister {
    Login,
    Register,
}

const Login = () => {
    const [showPassword, setShowPassword] = useState<boolean>(false);
    const baseInformation = useContext(BaseInformationContext);
    const [loginOrRegister, setLoginOrRegister] = useState<LoginOrRegister>(
        LoginOrRegister.Login
    );

    const [formData, setFormData] = useState({
        firstName: "",
        lastName: "",
        email: "",
        age: "",
        password: "",
    });

    useEffect(() => {
        setFormData({
            firstName: "",
            lastName: "",
            email: "",
            age: "",
            password: "",
        });
    }, [loginOrRegister]);

    const handleSubmitRegister = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        const { firstName, lastName, email, age, password } = formData;
        const hashedPassword = await hashPassword(password);
    
        try {
            const response = await fetch(`${server_url}/register`, {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify({
                    firstName,
                    lastName,
                    email,
                    age,
                    password: hashedPassword,
                }),
            });
    
            if (!response.ok) {
                throw new Error(`Error: ${response.statusText}`);
            }
    
            const data = await response.json();
            console.log("Registration successful:", data);
        } catch (error) {
            console.error("Error during registration:", error);
        }
    };
    

    const handleSubmitLogin = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        const { email, password } = formData;
        const hashedPassword = await hashPassword(password);
    
        try {
            const loginResponse = await fetch(`${server_url}/login`, {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify({
                    email,
                    password: hashedPassword,
                    token: "",
                }),
            });
            
            if (!loginResponse.ok) {
                if (loginResponse.status === 401) {
                    console.warn("401 Unauthorized error ignored.");
                } else {
                    throw new Error(`Error: ${loginResponse.statusText}`);
                }
            }
            const loginRequest: LoginRequest = await loginResponse.json();
            const isPasswordValid = await comparePassword(password, loginRequest.password);
            const isTokenValid = compare_auth_token(loginRequest);

            if (isPasswordValid && isTokenValid) {
                console.log("Authentication successful. Logging in...");
                
                const userResponse = await fetch(`${server_url}/get`, {
                    method: "POST",
                    headers: {
                        "Content-Type": "application/json",
                        Authorization: generate_auth_token(loginRequest),
                    },
                    body: JSON.stringify(
                        { 
                            email, 
                            token: generate_auth_token(loginRequest)
                        }
                    ),
                });
                if (!userResponse.ok) {
                    throw new Error(`Error: ${userResponse.statusText}`);
                }
                const data = await userResponse.json();
                console.log("User data:", data);
                const userInfo: UserInformation = data;

                baseInformation?.setBaseInformation({
                    userInformation: userInfo,
                    token: loginRequest.token,
                    loggedIn: true,
                    loading: false,
                    news: [{
                        title: "Welcome to the Bank of Helmethill",
                        id: 0,
                        description: "You are now logged in.",
                        url: "https://www.youtube.com/watch?v=dQw4w9WgXcQ",
                    }],
                });
            } else {
                throw new Error("Invalid login credentials");
            }
        } catch (error) {
            handleLoginError(error);
        } finally {
            // Clear the password field
            setFormData((prev) => ({
                ...prev,
                password: "",
            }));
        }
    };
    
    
    const handleLoginError = (error: any) => {
        console.error("An error occurred during login:", error);
        alert(typeof error === "string" ? error : "An unexpected error occurred. Please try again.");
    };
    
    
    

    const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        const { name, value } = e.target;
        setFormData((prev) => ({
            ...prev,
            [name]: value,
        }));
    };

    return (
        <div>
            <h1>Hello and welcome to the Bank of Helmethill</h1>
            <div className={styles.loginOrRegister}>
                <button
                    onClick={() => {
                        setLoginOrRegister(
                            loginOrRegister === LoginOrRegister.Login
                                ? LoginOrRegister.Register
                                : LoginOrRegister.Login
                        );
                    }}
                >
                    {loginOrRegister === LoginOrRegister.Login
                        ? "Not a user? Register"
                        : "Already a user? Login"}
                </button>
            </div>

            {loginOrRegister === LoginOrRegister.Login ? (
                <form onSubmit={handleSubmitLogin}>
                    <label htmlFor="email">Email:</label>
                    <input
                        type="email"
                        id="email"
                        name="email"
                        value={formData.email}
                        onChange={handleInputChange}
                        required
                    />

                    <label htmlFor="password">Password:</label>
                    <input
                        type={showPassword ? "text" : "password"}
                        id="password"
                        name="password"
                        value={formData.password}
                        onChange={handleInputChange}
                        required
                    />
                    <button type="button" onClick={() => setShowPassword(!showPassword)}>
                        {showPassword ? "Hide" : "Show"} Password
                    </button>
                    <button type="submit">Login</button>
                </form>
            ) : (
                <form onSubmit={handleSubmitRegister}>
                    <label htmlFor="email">Email:</label>
                    <input
                        type="email"
                        id="email"
                        name="email"
                        value={formData.email}
                        onChange={handleInputChange}
                        required
                    />
                    <label htmlFor="password">Password:</label>
                    <input
                        type={showPassword ? "text" : "password"}
                        id="password"
                        name="password"
                        value={formData.password}
                        onChange={handleInputChange}
                        required
                    />

                    <label htmlFor="firstName">First Name:</label>
                    <input
                        type="text"
                        id="firstName"
                        name="firstName"
                        value={formData.firstName}
                        onChange={handleInputChange}
                        required
                    />

                    <label htmlFor="lastName">Last Name:</label>
                    <input
                        type="text"
                        id="lastName"
                        name="lastName"
                        value={formData.lastName}
                        onChange={handleInputChange}
                        required
                    />

                    <label htmlFor="age">Age:</label>
                    <input
                        type="number"
                        id="age"
                        name="age"
                        value={formData.age}
                        onChange={handleInputChange}
                        required
                        min={0}
                        max={100}
                    />

                    <button type="button" onClick={() => setShowPassword(!showPassword)}>
                        {showPassword ? "Hide" : "Show"} Password
                    </button>
                    <button type="submit">Register</button>
                </form>
            )}

        </div>
    );
};

export default Login;
