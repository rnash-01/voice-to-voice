import React from "react";
import ReactDOM from "react-dom";
import {BrowserRouter as Router, Route, Routes } from "react-router-dom";

import App from "./App.js";
//import "./styles.css";

const appRouting = (
	<Router>
		<Routes>
			<Route exact path="/" element={<App/>}></Route>
		</Routes>
	</Router>
);

ReactDOM.render(appRouting, document.getElementById("root"));

if (module.hot)
