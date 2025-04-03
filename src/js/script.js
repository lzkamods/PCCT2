function shtdwn() {
    console.log("sending request..");  // Логируем начало запроса
    fetch('/shtdwn')
        .then(response => {
            console.log("answwer recived:", response);
            return response.text();
        })
        .catch(error => console.error('Error:', error));
}

function rstrt(){
    console.log("Requesting Restart..");
    fetch('/rstrt')
        .then(response => {
            console.log("Restart Recived!", response);
            return response.text();
            
        })
        .catch(error => console.error('Error', error));
}

function logout(){
    console.log("Requesting Log Out..");
    fetch('/logout')
        .then(response => {
            console.log("Log Out Recived!", response);
            return response.text();
            
        })
        .catch(error => console.error('Error', error));
}

function discord(){
    console.log("Requesting Discord..");
    fetch('/discord')
        .then(response => {
            console.log("Discord Recived!", response);
            return response.text();
            
        })
        .catch(error => console.error('Error', error));
}

function tgha(){
    console.log("Requesting Telegram..");
    fetch('/telega')
        .then(response => {
            console.log("Telegram Recived!", response);
            return response.text();
            
        })
        .catch(error => console.error('Error', error));
}

function firefox(){
    console.log("Requesting FireFox..");
    fetch('/firefox')
        .then(response => {
            console.log("FireFox Recived!", response);
            return response.text();
            
        })
        .catch(error => console.error('Error', error));
}

function explorer() {
    console.log("Req Explorer");
    fetch('/explorer')
        .then(response => {
            console.log("Explorer Recived", response);
            return response.text();
        })
        .catch(error => console.error('Error', error));
}

function steam() {
    console.log("Req Steam");
    fetch('/steam')
        .then(response => {
            console.log("Steam Recived", response);
            return response.text();
        })
        .catch(error => console.error('Error', error));
}

function vsc() {
    console.log("Req VSC");
    fetch('/vsc')
        .then(response => {
            console.log("VSC Recived", response);
            return response.text();
        })
        .catch(error => console.error('Error', error));
}

function tskmgr() {
    console.log("Req MGR");
    fetch('/tskmgr')
        .then(response => {
            console.log("TSKMGR Recived", response);
            return response.text();
        })
        .catch(error => console.error('Error', error));
}

function volup(){ 
    console.log("volup send");
    fetch('/volup')
        .then(response => {
            console.log("volup Rec", response)
            return response.text;
        })
        .catch(error => console.error('Error', error));
}

function voldn(){ 
    console.log("voldn send");
    fetch('/voldn')
        .then(response => {
            console.log("voldn Rec", response)
            return response.text;
        })
        .catch(error => console.error('Error', error));
}


function drop() {
    let elem = document.getElementById('menu');
    let style = getComputedStyle(elem)
    if(style.display === 'none') {
        document.getElementById('menu').style.display='grid';
    } 
    else if(style.display !== 'none') {
        document.getElementById('menu').style.display='none';
    }
}

function Terminate(){ 
    console.log("Terminate send");
    fetch('/terminate')
        .then(response => {
            console.log("terminate Rec", response)
            return response.text;
        })
        .catch(error => console.error('Error', error));
}