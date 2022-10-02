#pragma once

const char* webPage = R"***(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WebSerial</title>
</head>

<body>
    <div id="page">
        <div id="header">
            <h1>WebSerial</h1>
        </div>
        <div id="app">
            <input type="text" id="input"></input>
            <button id="send" onclick="send_input()">send</button>
            <button id="clear" onclick="clear_output()">clear</button>
            <textarea id="output" readonly="true"></textarea>
            <div id="option"><input type="checkbox" id="pause" onclick="pause_output()"><label for="pause">pause</label> </div>
            <div id="option"><input type="checkbox" id="timestamp"><label for="timestamp">timestamp</label></div>
        </div>
        <div id="footer"><a href="https://github.com/sivar2311/WebSerial" target="_blank">Visit WebSerial at <b>GitHub</b></a></div>
        </page>
</body>
<style>
    body {
        color: gray;
        font-family: Verdana;
        text-align: center;
        margin: 0 auto;
    }

    input:focus,
    textarea:focus,
    button:focus {
        outline: none;
    }

    button:hover,
    div#option>*:hover {
        cursor: pointer;
    }

    label {
        margin-left: 0.5em;
    }

    a {
        text-decoration: none;
        color: gray;
    }


    #page {
        display: grid;
        grid-template-columns: 1fr;
        grid-auto-rows: minmax(0px, auto);
        grid-gap: 1em;
        margin: 0 auto;
        position: relative;
        max-width: 960px;
        min-width: 300px;
    }

    #app {
        background-color: #eee;
        border-radius: 1em;
        padding: 1em;
        box-shadow: 0 0 1em;
        gap: 1em;

        display: grid;
        grid-template-columns: repeat(12, 1fr);
        grid-auto-rows: minmax(0px, auto);
    }

    #app>* {
        border-radius: 1em;
        padding: 1em;
        border: none;
    }

    #input {
        grid-column: span 8;
        background-color: #fff;
    }

    input[type=checkbox] {
        margin-right: 10px;
        margin-left: 10px;
        transform: scale(2);

    }

    button {
        grid-column: span 2;
    }

    #send {
        background-color: rgba(144, 238, 144, 0.5);
    }

    #send:hover {
        background-color: rgba(144, 238, 144, 1);
    }

    #clear {
        background-color: rgba(240, 128, 128, 0.5);
    }

    #clear:hover {
        background-color: rgba(240, 128, 128, 1);
    }

    #output {
        grid-column: span 12;
        height: 20em;
        resize: vertical;
    }

    #option {
        grid-column: span 6;
        padding: 0px;
    }

    @media screen and (max-width:720px) {

        #send,
        #clear {
            grid-column: span 6;
        }

        #input {
            grid-column: span 12;
        }

        #header {
            grid-row: 2/3;
        }
    }

    @media screen and (max-width:420px) {
        #option {
            grid-column: span 12;
            justify-self: start;
        }
    }

    @media screen and (max-height: 500px) {
        #output {
            height: 10em;
        }

        #header {
            display: none;
        }

    }
</style>

<script>
    const port = 80;

    const url = "/webserialws";
    const ws_url = `ws://${window.location.hostname}:${window.location.port}/webserialws`;

    let input = document.getElementById('input');
    let output = document.getElementById('output');
    let pause = document.getElementById('pause');
    let timestamp = document.getElementById('timestamp');

    let pause_buffer = "";

    socket = new WebSocket(ws_url);

    input.addEventListener("keypress", event => {
        if (event.key === "Enter") send_input();
    });

    socket.onmessage = (event) => {
        var selection = saveSelection();

        var next_line = event.data;
        if (timestamp.checked) next_line = addTimestamp(next_line);

        if (pause.checked) {
            pause_buffer += next_line;
        } else {
            output.value += next_line;
            output.scrollTop = output.scrollHeight;
        }

        restoreSelection(selection);
    }

    function clear_output() {
        output.value = "";
    }

    function send_input() {
        socket.send(input.value);
        input.value = "";
        input.focus();
    }

    function pause_output() {
        if (!pause.checked && pause_buffer != "") {
            output.value += pause_buffer;
            pause_buffer = "";
            output.scrollTop = output.scrollHeight;
        }
    }

    function addTimestamp(line) {
        const current_time = new Date(Date.now());
        return `${current_time.toLocaleTimeString()}.${String(current_time.getMilliseconds()).padStart(3, '0')} -> ` + line;
    }

    function saveSelection() {
        return { start: output.selectionStart, end: output.selectionEnd };
    }

    function restoreSelection(selection) {
        output.selectionStart = selection.start;
        output.selectionEnd = selection.end;
    }
</script>

</html>
)***";