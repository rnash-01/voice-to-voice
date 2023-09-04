// For now, this is manually built to be useful to Electron
// The hope is that this file can be built automatically from some electron/web-ambivalent code. To be consistent, all functions are PROMISES.

const backiface = {
	hello: () => typeof window !== 'undefined' ? window.backinterface.hello : Promise.resolve("No backinterface defined")
}

export default backiface;
