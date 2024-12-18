interface LoadingProps {
    text : string;
}
const Loading = ({text}: LoadingProps) => {
    return (
        <div>
            <h1>{text}</h1>
        </div>
    )
}

export default Loading;