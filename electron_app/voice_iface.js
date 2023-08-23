const voice = process.env.DEV_MODE
	  ? require('../cpp/build/Debug/voice')
	  : require('../cpp/build/Release/voice')


const hello = () => {
	return voice.hello();
};

module.exports = {
	hello: hello
};

