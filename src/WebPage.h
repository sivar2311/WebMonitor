#pragma once

const char* webPage = R"***(
<html>
<head>
    <meta charset='utf-8'>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <title>WebSerial</title>

    <style>
        body {
            font-family: 'verdana';
        }

        .wrapper {
            width: 100%;
            max-width: 960px;
            margin: 0 auto;
        }

        .header {
            height: 40px;
        }

        .main {
            height: calc(100% - 88px);
        }

        .footer {
            height: 48px;
            width: 100%;
            max-width: 960px;
            position: fixed;
            bottom:0;
        }

        textarea {
            background-color: lightgray;
            font-family: 'Courier New', monospace;
            color: #222222;
            width: 100%;
            max-width: 960px;
            height: 100%;

        }
    </style>
</head>

<body>
    <form onsubmit="return false">
        <div class="wrapper">
            <div class="header">
                <h1>WebSerial</h1>
            </div>
            <div class="main">
                <textarea readonly id="messages"></textarea>
            </div>
            <div class="footer">
                <div>
                    <input type="checkbox" id="scroll" value="scroll" checked="true"><label for="checkbox">auto
                        scroll</label>
                    <input type="checkbox" id="timestamp" value="timestamp"><label for="timestamp">timestamp</label>
                    <button type="button" onclick="clear_lines()">clear</button>
                </div>
                <div>
                    <input type="text" id="text"><button type="button" onclick="send_line()" autofocus>send</button>
                </div>
            </div>
        </div>
    </form>
</body>
<script>
    let scroll = document.getElementById('scroll');
    let timestamp = document.getElementById('timestamp');
    let messages = document.getElementById('messages');
    let send_text = document.getElementById('text');

    text.addEventListener("keypress", event => {
        if (event.key === "Enter") send_line();
    });

    const port = 80;
    const url = "/webserialws";

    const ws_url = `ws://${window.location.hostname}:${window.location.port}/webserialws`;

    socket = new WebSocket(ws_url);

    socket.onmessage = (event) => {
        var next_line = event.data;

        if (timestamp.checked) {
            const current_time = new Date(Date.now()).toLocaleTimeString();
            next_line = `[${current_time}]: ` + next_line;
        }
        messages.value = messages.value + next_line;

        if (scroll.checked) messages.scrollTop = messages.scrollHeight;
    }

    var clear_lines = function () {
        messages.value = "";
    }

    var send_line = function () {
        socket.send(text.value);
        text.value = "";
    }
</script>
</html>)***";