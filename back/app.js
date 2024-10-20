const express = require("express");
const app = express();
const path = require("path");
const port = process.env.PORT || 3000;

app.listen(port, () => {
	console.log(`The app server is running on port: ${port}`);
});

const DIST_DIR = path.join(__dirname, "../front/", "dist"); // Webpack bundle
const HTML_FILE = path.join(DIST_DIR, "index.html"); // HTML index file

// Middleware stack
app.use(express.json());
app.use(express.static(DIST_DIR));

// GETS
app.get("/", (req, res) => {
	res.sendFile(HTML_FILE, function(err) {
		if (err) {
			res.status(500).send(err);
		}
	});
});
