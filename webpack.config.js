const path = require("path");
const webpack = require("webpack");
const HTMLWebpackPlugin = require("html-webpack-plugin");

const electron = require("./webpack.electron.js");
const web = require("./webpack.web.js");

module.exports = [
	web, // Default configuration
	electron // Electron
];


