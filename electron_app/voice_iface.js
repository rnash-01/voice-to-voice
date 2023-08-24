const voice = process.env.DEV_MODE
	  ? require('../cpp/build/Debug/voice')
	  : require('./audio_back/voice.node')


const hello = () => {
	return voice.hello();
};

module.exports = {
	hello: hello
};

