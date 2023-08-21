const path = require("path");
const webpack = require("webpack");
const HTMLWebpackPlugin = require("html-webpack-plugin");
const common = require("./webpack.common.js");
const { merge } = require("webpack-merge");

module.exports = merge(common, {
	output: {
		filename: "bundle.js",
		path: path.resolve("dist"),
		publicPath: "/"
	},
	plugins: [
		new HTMLWebpackPlugin({
			template: "front/index_web.html",
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
});

