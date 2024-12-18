import { useContext } from "react";
import { BaseInformationContext } from "../App";
import { parse_first_name } from "../utils/parser";
import Loading from "../modules/Loading";

const Home = () => {
    const baseInformation = useContext(BaseInformationContext);
    if(baseInformation?.baseInformation == null){
        return <Loading text="Loading user data..."/>
    }
    
    return (
        <div>
            <h1>Welcome to the home page of the bank of Helmethill{parse_first_name(baseInformation?.baseInformation?.userInformation?.user.name, true)}!</h1>

        </div>
    )
}

export default Home;