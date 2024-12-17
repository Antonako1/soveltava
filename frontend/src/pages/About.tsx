import { useContext } from "react";
import { BaseInformationContext } from "../App";

const About = () => {
    const { baseInformation } = useContext(BaseInformationContext)!;
    console.log(baseInformation );
    
    return (
        <div>
            <h1>About</h1>
            <p>This is the about page</p>
        </div>
    )
}
export default About;