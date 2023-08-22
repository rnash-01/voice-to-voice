import React from "react";
import ReactDOM from "react-dom/client";
import { HashRouter, BrowserRouter, Route, Routes } from "react-router-dom";
import App from "./App.js";
//import "./styles.css";

// Depending on whether or not the environment is Electron or just Web,
// a different router is needed. For Electron, this is the HashRouter (for files)
// For web, a standard BrowserRouter works.
const root = ReactDOM.createRoot(document.getElementById("root"));
let Router;
typeof(HASH_ROUTERS) !== 'undefined'
	? Router = HashRouter
	: Router = BrowserRouter
root.render(
	<React.StrictMode>
		<Router>
 			<Routes>
 				<Route exact path="/" element={<App/>}></Route>
 			</Routes>
		</Router>
		
																			   
 	</React.StrictMode>
);

console.log(root.render ? "It's a function, yes" : "No");
console.log("HIII");

