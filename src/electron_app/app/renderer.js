const information = document.getElementById('info');
console.log("Renderer script running...");

information.innerText = `This app is using chrome (v${versions.chrome()})`;
