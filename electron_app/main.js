const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');

const createWindow = () => {
	const win = new BrowserWindow({
		width: 800,
		height: 600,
		webPreferences: {
			preload: path.join(__dirname, 'preload.js'),
			nodeIntegration: true
		}
	});
	console.log(__dirname);
	win.loadURL(
		process.env.DEV_MODE
			? 'http://localhost:3000'
			: `file://${__dirname}/app/dist/index.html`
	);
//	win.loadURL('http://localhost:3000');
};

// Handle events - following https://www.electronjs.org/docs/latest/tutorial/tutorial-first-app
app.whenReady().then(() => {
	createWindow();

	// Close app if all windows are closed
	app.on('window-all-closed', () => {
		if (process.platform !== 'darwin') app.quit();
	});
});



// Open new window if app is activated (MacOS)
app.on('activate', () => {
	if (BrowserWindow.getAllWindows().length === 0) createWindow();
});

