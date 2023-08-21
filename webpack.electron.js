const path = require("path");
const webpack = require("webpack");
const HTMLWebpackPlugin = require("html-webpack-plugin");
const common = require("./webpack.common.js");
const { merge } = require("webpack-merge");
module.exports = merge(common, {
	output: {
		filename: "bundle.js",
		path: path.resolve("electron_app/app/dist"),
		publicPath: "./"
	},
	plugins: [
		new webpack.DefinePlugin({
			HASH_ROUTERS: true
		}),
		new HTMLWebpackPlugin({
			template: "front/index_electron.html"
		})
	]
});
