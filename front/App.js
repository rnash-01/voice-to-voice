import React, {useState} from "react";
import back from "./interface/back.js"

const hello = back.hello
const App = () => {
	console.log(hello);
	const [helloResult, setHelloResult] = useState("Pending...");
	console.log(`It seems that the function is${hello ? "" : " not"} defined`);

	console.log(typeof hello)
	hello().then((res) => {
		setHelloResult(res);
	});
	
	return <div>Hi there, this is a react app. {helloResult}</div>
}

export default App;
