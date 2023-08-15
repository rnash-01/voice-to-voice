const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');

const createWindow = () => {
	const win = new BrowserWindow({
		width: 800,
		height: 600,
		webPreferences: {
			preload: path.join(__dirname, 'preload.js')
		}
	});
	win.loadFile('app/index.html');
};

// Handle events - following https://www.electronjs.org/docs/latest/tutorial/tutorial-first-app
app.whenReady().then(() => {
	ipcMain.handle('ping', () => 'pong')
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

