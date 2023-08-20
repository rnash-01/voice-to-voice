// Taken and adapted from: https://dev.to/underscorecode/creating-your-react-project-from-scratch-without-create-react-app-the-complete-guide-4kbc
path = require("path");
webpack = require("webpack");
HTMLWebpackPlugin = require("html-webpack-plugin");

module.exports = {
	entry: "./front/index.js",
	output: {
		filename: "bundle.js",
		path: path.resolve("dist"),
		publicPath: "/",
	},
	module: {
		// Help webpack to determine what loader to use for each file extension.
		rules: [
			{
				test: /\.(js|jsx)$/,
				exclude: /node_modules/,
				loader: "babel-loader",
				options: {
					presets: [
						"@babel/preset-react"
					]
				}
							  
			},
			{
				test: /\.html$/,
				use: "html-loader"
			},
			{
				test: /\.css$/,
				use: ["style-loader", "css-loader"]
			}
			// PNG, fonts, etc, could be appended here.
		],
	},
	plugins: [
		new HTMLWebpackPlugin({
			template: "front/index.html"
		})
	],
	devtool: "inline-source-map",
	devServer: {
		static: {
			directory: path.resolve("dist")
		},
		compress: true,
		port: 3000,
		hot: true
	}
};
