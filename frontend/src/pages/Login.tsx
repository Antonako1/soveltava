import { useState } from "react";
import styles from "../styles/login.module.css"

enum LoginOrRegister {
    Login,
    Register
}

const Login = () => {
    const [showPassword, setShowPassword] = useState<boolean>(false);
    const [loginOrRegister, setLoginOrRegister] = useState<LoginOrRegister>(LoginOrRegister.Login);
    const handleSubmit = (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        const form = e.currentTarget;
        const formData = new FormData(form);
        const data = Object.fromEntries(formData.entries());
        console.log(data);
    }
    
    return (
        <div>
            <h1>
                Hello and welcome to the Bank of Helmethill
            </h1>
            <div className={styles.loginOrRegister}>
                <span>{loginOrRegister === LoginOrRegister.Login ? "Login" : "Register"}
                </span>
                <button
                    onClick={() => {
                        if (loginOrRegister === LoginOrRegister.Login) {
                            setLoginOrRegister(LoginOrRegister.Register);
                        } else {
                            setLoginOrRegister(LoginOrRegister.Login);
                        }
                    }}
                >Login or Register?</button> 

            </div>
            
            {
                loginOrRegister === LoginOrRegister.Login ? (
                    <form
                        onSubmit={(e) => handleSubmit(e)}
                    >
                        <label htmlFor="email">Email:</label>
                        <input type="email" id="email" name="email" required />

                        <label htmlFor="password">Password:</label>
                        <input type={showPassword ? "text" : "password"} id="password" name="password" required />
                        <button type="button" onClick={() => setShowPassword(!showPassword)}>
                            {showPassword ? "Hide" : "Show"} Password
                        </button>
                        <button type="submit">Login</button>
                    </form>
                ) : (
                    <form 
                        onSubmit={(e) => handleSubmit(e)} 
                    >
                        
                        <label htmlFor="firstName">First Name:</label>
                        <input type="text" id="firstName" name="firstName" required />

                        <label htmlFor="lastName">Last Name:</label>
                        <input type="text" id="lastName" name="lastName" required />

                        <label htmlFor="email">Email:</label>
                        <input type="email" id="email" name="email" required />

                        <label htmlFor="age">Age:</label>
                        <input type="number" id="age" name="age" required min={0} max={100}/>

                        <label htmlFor="password">Password:</label>
                        <input type={showPassword ? "text" : "password"} id="password" name="password" required />
                        <button type="button" onClick={() => setShowPassword(!showPassword)}>
                            {showPassword ? "Hide" : "Show"} Password
                        </button>
                        <button type="submit">Register</button>
                    </form>
                )
            }
        </div>
    );
}

export default Login;