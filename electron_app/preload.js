// From https://www.electronjs.org/docs/latest/tutorial/tutorial-preload

const { contextBridge, ipcRenderer } = require('electron');

contextBridge.exposeInMainWorld('backinterface', {
	// Interfaces called by front end go here.
	hello: () => ipcRenderer.invoke('hello')
});
