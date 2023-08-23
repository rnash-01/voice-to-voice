import React, {useState} from "react";
import { hello } from "./interface/back.js"

const App = () => {
	const [helloResult, setHelloResult] = useState("Pending...");
	console.log(`It seems that the function is${window.backinterface.hello ? "" : " not"} defined`);

	window.backinterface.hello().then((res) => {
		setHelloResult(res);
	});
	
	return <div>Hi there, this is a react app. {helloResult}</div>
}

export default App;
