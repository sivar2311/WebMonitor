#pragma once

namespace WebMon {

const char* webPage = R"***(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WebMonitor</title>
</head>

<body>
    <div id="page">
        <div id="header">
            <h1>WebMonitor</h1>
        </div>
        <div id="app">
            <input type="text" id="input" placeholder="Send"></input>
            <button id="send_btn" onclick="send_input()">send</button>
            <button id="clear_btn" onclick="clear_monitor_and_buffer()">clear</button>
            <textarea id="monitor" readonly="true" placeholder="Nothing received yet"></textarea>
            <input type="text" id="filter" placeholder="Filter"></input>
            <button id="toggle_timestamp_btn" onclick="toggle_timestamps()">
                <svg version="1.1" x="0px" y="0px" viewBox="0 0 128 128" id="clock" class="clock">
                    <circle cx="64" cy="64" r="58" />
                    <line x1="64" y1="64" x2="64" y2="25" />
                    <line x1="64" y1="64" x2="94" y2="80" />
                </svg>
            </button>
        </div>
        <div id="footer"><a href="https://github.com/sivar2311/WebMonitor" target="_blank">Visit WebMonitor at <b>GitHub</b></a></div>
    </div>
</body>

<style>
    .clock {
        fill: none;
        stroke: var(--clock);
        stroke-width: 10;
        stroke-linecap: round;
        stroke-linejoin: round;
        width: 2em;
        height: 2em;
    }

    .clock:hover {
        stroke: var(--clock_hover);
    }

    .enabled {
        stroke: var(--clock_hover);
    }

    :root {
        --icon: #ffffff;
        --icon-background: #808080;


        --link_light: #aeb5bb;
        --input_light: #ffffff;
        --text_light: #606060;
        --background_light: #ffffff;
        --app-background_light: #eeeeee;
        --shadow_light: #00000080;
        --btn_light: #ffffff;
        --outline_light: none;

        --send-btn_light: #ffffff;
        --send-btn-hover_light: #ffffff;
        --send-btn-background_light: #23863699;
        --send-btn-background-hover_light: #238636;

        --clear-btn_light: #ffffff;
        --clear-btn-hover_light: #ffffff;
        --clear-btn-background_light: #F8514999;
        --clear-btn-background-hover_light: #F85149;

        --link_dark: #aeb5bb;
        --input_dark: #000000;
        --text_dark: #c9d1d9;
        --background_dark: #010409;
        --app-background_dark: #0d1117;
        --shadow_dark: none;
        --btn_dark: #ffffff;
        --outline_dark: #616161;

        --send-btn_dark: #ffffff;
        --send-btn-hover_dark: #ffffff;
        --send-btn-background_dark: #23863699;
        --send-btn-background-hover_dark: #238636;

        --clear-btn_dark: #ffffff;
        --clear-btn-hover_dark: #ffffff;
        --clear-btn-background_dark: #F8514999;
        --clear-btn-background-hover_dark: #F85149;

        --clock_light: #a0a0a0;
        --clock_hover_light: #616161;

        --clock_dark: gray;
        --clock_hover_dark: white;
    }

    @media (prefers-color-scheme:light) {
        :root {
            --link: var(--link_light);
            --input: var(--input_light);
            --text: var(--text_light);
            --background: var(--background_light);
            --app-background: var(--app-background_light);
            --shadow: var(--shadow_light);
            --btn: var(--btn_light);
            --outline: var(--outline_light);

            --send-btn: var(--send-btn_light);
            --send-btn-hover: var(--send-btn-hover_light);
            --send-btn-background: var(--send-btn-background_light);
            --send-btn-background-hover: var(--send-btn-background-hover_light);

            --clear-btn: var(--clear-btn_light);
            --clear-btn-hover: var(--clear-btn-hover_light);
            --clear-btn-background: var(--clear-btn-background_light);
            --clear-btn-background-hover: var(--clear-btn-background-hover_light);

            --clock: var(--clock_light);
            --clock_hover: var(--clock_hover_light);
        }

    }

    @media (prefers-color-scheme:dark) {
        :root {
            color-scheme: dark;

            --link: var(--link_dark);
            --input: var(--input_dark);
            --text: var(--text_dark);
            --background: var(--background_dark);
            --app-background: var(--app-background_dark);
            --shadow: var(--shadow_dark);
            --btn: var(--btn_dark);
            --outline: var(--outline_dark);

            --send-btn: var(--send-btn_dark);
            --send-btn-hover: var(--send-btn-hover_dark);
            --send-btn-background: var(--send-btn-background_dark);
            --send-btn-background-hover: var(--send-btn-background-hover_dark);

            --clear-btn: var(--clear-btn_dark);
            --clear-btn-hover: var(--clear-btn-hover_dark);
            --clear-btn-background: var(--clear-btn-background_dark);
            --clear-btn-background-hover: var(--clear-btn-background-hover_dark);

            --clock: var(--clock_dark);
            --clock_hover: var(--clock_hover_dark);
        }
    }

    body {
        font-family: Verdana;
        text-align: center;
        margin: 0 auto;
    }

    input:focus,
    textarea:focus,
    button:focus {
        outline: none;
    }

    button:hover {
        cursor: pointer;
    }

    label {
        margin-left: 0.5em;
    }

    a {
        text-decoration: none;
        color: var(--link);
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
        border-radius: 0.5em;
        padding: 1em;
        box-shadow: 0 0 1em var(--shadow);
        gap: 1em;
        display: grid;
        grid-template-columns: repeat(12, 1fr);
        grid-auto-rows: minmax(0px, auto);
        outline: 1px solid var(--outline);
        background-color: var(--app-background);
    }

    #app>* {
        border-radius: 0.5em;
        padding: 1em;
        border: none;
    }

    #input {
        grid-column: span 8;
        background-color: var(--input);
        color: var(--text);
        outline: 1px solid var(--outline);
    }

    #monitor {
        grid-column: span 12;
        height: 20em;
        resize: vertical;
        background-color: var(--input);
        color: var(--text);
        outline: 1px solid var(--outline);
    }

    #filter {
        grid-column: span 11;
        background-color: var(--input);
        color: var(--text);
        outline: 1px solid var(--outline);
    }

    button {
        grid-column: span 2;
        font-family: inherit;
    }

    #toggle_timestamp_btn {
        grid-column: span 1;
        padding: 0px;
        background-color: var(--app-background);
    }

    body {
        color: var(--text);
        background-color: var(--background);
    }

    #send_btn {
        color: var(--send-btn);
        background-color: var(--send-btn-background);
    }

    #send_btn:hover {
        color: var(--send-btn-hover);
        background-color: var(--send-btn-background-hover);
    }

    #clear_btn {
        color: var(--clear-btn);
        background-color: var(--clear-btn-background);
    }

    #clear_btn:hover {
        color: var(--clear-btn-hover);
        background-color: var(--clear-btn-background-hover);
    }

    @media screen and (max-width:720px) {

        #send_btn,
        #clear_btn {
            grid-column: span 6;
        }

        #input {
            grid-column: span 12;
        }

        #header {
            grid-row: 2/3;
        }
    }

    @media screen and (max-height: 500px) {
        #monitor {
            height: 10em;
        }

        #header {
            display: none;
        }
    }
</style>

<script>
    const protocol = (location.protocol === 'https:' ? 'wss' : 'ws');
    const ws_url = `${protocol}://${window.location.hostname}/wmws`;

    let last_monitor_refresh = 0;
    let counter = 0;
    let receive_buffer = [];

    let input = document.getElementById('input');
    let monitor = document.getElementById('monitor');
    let filter = document.getElementById('filter');
    let app = document.querySelector('body');
    socket = new WebSocket(ws_url);

    let show_timestamps = false;

    input.addEventListener("keypress", event => {
        if (event.key === "Enter") send_input();
    });

    filter.addEventListener("input", event => {
        clear_monitor();
        refresh_monitor();
        auto_scroll();
    });

    socket.onmessage = (event) => {
        process_message(event.data);
    }

    socket.onerror = (err) => {
        console.log(err);
    }

    function clear_monitor() {
        last_monitor_refresh = 0;
        monitor.value = "";
    }

    function clear_buffer() {
        receive_buffer = [];
    }

    function clear_monitor_and_buffer() {
        clear_monitor();
        clear_buffer();
    }

    function send_input() {
        socket.send(input.value);
        input.value = "";
        input.focus();
    }

    function saveSelection() {
        return { start: monitor.selectionStart, end: monitor.selectionEnd };
    }

    function restoreSelection(selection) {
        [monitor.selectionStart, monitor.selectionEnd] = [selection.start, selection.end];
    }

    function process_message(message) {
        var selection = saveSelection();
        add_message_to_receive_buffer(message);
        refresh_monitor();
        auto_scroll();
        restoreSelection(selection);
    }

    function auto_scroll() {
        requestAnimationFrame(() => {
            const position = monitor.scrollTop + monitor.offsetHeight;
            const height = monitor.scrollHeight;
            if (position > height - 100) monitor.scrollTop = monitor.scrollHeight;
        });
    }

    function add_message_to_receive_buffer(data) {
        const timestamp = Date.now();

        const messages = data.split('\n');
        messages.forEach(line => {
            if (line == '') return;
            line = line.replace('\r', '') + '\n';
            const message = { content: line, timestamp: timestamp };
            receive_buffer.push(message);
        });
    }

    function refresh_monitor() {
        const filter_value = filter.value;

        let text = "";

        receive_buffer.forEach(element => {
            if (element.timestamp <= last_monitor_refresh) return;

            const d = new Date(element.timestamp);

            var timestamp_string = show_timestamps ? `${d.toLocaleTimeString()}.${String(d.getMilliseconds()).padStart(3, '0')} -> ` : ``;
            var line = `${timestamp_string}${element.content}`;

            if (line.match(filter_value)) text += line;
        });

        monitor.value += text;
        last_monitor_refresh = Date.now();
    }

    function toggle_timestamps() {
        show_timestamps = !show_timestamps;
        clear_monitor();
        refresh_monitor();
        toggle_clock();
    }

    function toggle_clock() {
        let clock = document.getElementById("clock");
        clock.classList.toggle("enabled");
    }
</script>

</html>
)***";

} // namespace