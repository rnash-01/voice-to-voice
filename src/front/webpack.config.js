// Taken and adapted from: https://dev.to/underscorecode/creating-your-react-project-from-scratch-without-create-react-app-the-complete-guide-4kbc

const path = require("path");
const webpack = require("webpack");
const HTMLWebpackPlugin = require("html-webpack-plugin");

module.exports = {
	entry: "./index.js",
	output: {
		filename: "bundle.js",
		path: path.resolve("dist"),
		publicPath: "/",
	},
	module: {
		// Help webpack to determine what loader to use for each file extension.
		rules: [
			{
				test: /\.(js|jsx)$/
				exclude: /node_modules/,
				use: "babel-loader"
			},
			{
				test: /\.html$/,
				use: "html-loader"
			},
			{
				test: /\.css$/
				use: ["style-loader", "css-loader"]
			}
			// PNG, fonts, etc, could be appended here.
		],
	},
	plugins: [
		new HTMLWebpackPlugin({
			template: "index.html"
		}),
	]
}
