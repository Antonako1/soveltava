import { useEffect, useState } from "react";
import axios from "axios";
import { server_url } from "../utils/Data";
import styles from "../styles/login.module.css";
import { compare_auth_token, comparePassword, generate_auth_token, hashPassword } from "../utils/hash";

enum LoginOrRegister {
  Login,
  Register,
}

const Login = () => {
  const [showPassword, setShowPassword] = useState<boolean>(false);
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
    await axios
      .post(`${server_url}/register`, {
        firstName,
        lastName,
        email,
        age,
        password: hashedPassword,
      })
      .then((response) => {
        console.log(response);
      })
      .catch((error) => {
        console.error(error);
      });
  };

  const handleSubmitLogin = async (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    const { email, password } = formData;
    const hashedPassword = await hashPassword(password);
    await axios
      .post(`${server_url}/login`, {
        email,
        password: hashedPassword,
        token: ""
      })
      .then(async (response) => {

        const res:boolean = await comparePassword(password, response.data.password)
        console.log(res, response.data)
        
        if(res) {

          await axios
          .post(`${server_url}/login`, {
            email,
            password: hashedPassword,
            token: generate_auth_token(response.data)
          }).
          then((response:any) => {
            console.log(response)
            const is_authentic:boolean = compare_auth_token(response.data.token);
            if(is_authentic) {
              console.log("User is authenticated")
            }
            else {
              console.log("User is not authenticated")
            }
          }).catch((error:any) => {
            console.error(error);
          });

        }
      })
      .catch((error) => {
        console.error(error);
      });
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
