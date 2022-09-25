#pragma once

const char* webPage = R"***(
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WebSerial</title>
</head>

<body>
    <div id="content">
        <div id="header">
            <h1>WebSerial</h1>
        </div>
        <div id="opt">
            <input type="checkbox" id="scroll" value="scroll" checked="true"><label for="scroll">auto scroll</label>
            <input type="checkbox" id="pause" value="pause"><label for="pause">pause</label>
            <input type="checkbox" id="timestamp" value="timestamp"><label for="timestamp">timestamp</label>
        </div>
        <input type="text" id="st" placeholder="type something and press send button"></input>
        <button id="sb" onclick="send_line()">send</button>
        <button id="cb" onclick="clear_lines()">clear</button>
        <textarea readonly="true" id="o" placeholder="nothing received yet"></textarea>
    </div>
</body>

<script>
    let scroll = document.getElementById('scroll');
    let timestamp = document.getElementById('timestamp');
    let pause = document.getElementById('pause');
    let output = document.getElementById('o');
    let send_text = document.getElementById('st');
    
    send_text.addEventListener("keypress", event => {
        if (event.key === "Enter") send_line();
    });
    
    const port = 80;
    const url = "/webserialws";
    
    const ws_url = `ws://${window.location.hostname}:${window.location.port}/webserialws`;
    
    socket = new WebSocket(ws_url);
    let pause_buffer = "";

    socket.onmessage = (event) => {
        var next_line = event.data;

        if (timestamp.checked) {
            const current_time = new Date(Date.now()).toLocaleTimeString();
            next_line = `[${current_time}] ` + next_line;
        }

        if (pause.checked) {
            pause_buffer += next_line;
        } else {
            if (pause_buffer == "") {
                output.value += next_line;
            } else {
                output.value += pause_buffer + next_line;
                pause_buffer = "";
            }
        }
        
        if (scroll.checked && !pause.checked) output.scrollTop = output.scrollHeight;
    }

    var clear_lines = function () {
        output.value = "";
    }

    var send_line = function () {
        socket.send(send_text.value);
        send_text.value = "";
    }
</script>
<style>
    body {
        color: gray;
        font-family: Verdana;
        text-align: center;
    }

    #content {
        display: grid;
        grid-template-columns: repeat(2, 1fr);
        grid-auto-rows: minmax(50px, auto);
        grid-gap: 10px;
        max-width: 960px;
        margin: 0 auto;
        position: relative;

        grid-template-areas:
            "st st"
            "sb cb"
            "o o"
            "o o"
            "o o"
            "o o"
            "o o"
            "opt opt"
            "h h";
    }


    @media screen and (min-width: 760px) {

        #content {
            display: grid;
            grid-template-columns: repeat(8, 1fr);
            grid-auto-rows: minmax(50px, auto);
            grid-gap: 10px;
            max-width: 960px;
            margin: 0 auto;
            position: relative;

            grid-template-areas:
                "h h h h h h h h"
                "opt opt opt opt opt opt opt opt"
                "st st st st st st sb cb"
                "o o o o o o o o"
                "o o o o o o o o"
                "o o o o o o o o"
                "o o o o o o o o"
                "o o o o o o o o"
                "o o o o o o o o";
        }
    }

    #content>* {
        padding: 0px;
        border-radius: 1em;
        outline: none;
        border: 0px;
    }

    #header {
        grid-area: h;
        text-align: center;
    }

    #opt {
        grid-area: opt;
        text-align: center;
    }

    button {
        cursor: pointer;
    }

    input[type=checkbox] {
        margin-right: 10px;
        margin-left: 10px;
        transform: scale(1.5);
    }

    input[type=checkbox]+label {
        cursor: pointer;
    }

    #pause:checked {
        content: '=';
    }

    #st {
        grid-area: st;
        background: #eee;
        padding: 10px;
    }

    #st:hover,
    #st:focus {
        background: #ddd;
    }

    #sb {
        grid-area: sb;
        background-color: rgba(144, 238, 144, 0.5);
    }

    #sb:hover {
        background-color: rgba(144, 238, 144, 1);
    }

    #cb {
        grid-area: cb;
        background-color: rgba(240, 128, 128, 0.5);
    }

    #cb:hover {
        background-color: rgba(240, 128, 128, 1);
    }

    #o {
        grid-area: o;
        padding: 10px;
        background: #eee;
        resize: vertical;
    }
</style>

</html>
)***";