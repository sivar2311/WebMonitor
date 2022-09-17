#pragma once

const char* webPage = R"***(
<html>

<head>
  <meta charset='utf-8'>
  <meta http-equiv='X-UA-Compatible' content='IE=edge'>
  <title>WebSerial</title>
  <meta name='viewport' content='width=device-width, initial-scale=1'>

  <style>
    textarea{
      width:100%;
      background-color: lightgrey;
      font-family: 'Courier New', monospace;
    }
  </style>
</head>

<body>
  <h1>WebSerial</h1>
  <form>
    <div>
      <textarea readonly id="messages" rows="20" cols="80"></textarea>
    </div>
    <div>
      <input type="checkbox" id="scroll" value="scroll" checked="true"><label for="checkbox">auto scroll</label>
      <input type="checkbox" id="timestamp" value="timestamp"><label for="timestamp">timestamp</label>
      <button type="button" onclick="clear_lines()">clear</button>
    </div>
  </form>
</body>
<script>
  let scroll = document.getElementById('scroll');
  let timestamp = document.getElementById('timestamp');
  let messages = document.getElementById('messages');

  const ws_url = "ws://" + window.location.hostname + "/webserialws";
  socket = new WebSocket(ws_url);

  socket.onmessage = (event) => {
    var next_line = event.data;
    const timeElapsed = Date.now();
    const today = new Date(Date.now());
    if (timestamp.checked) {
      const current_time = new Date(Date.now());
      next_line = "[" + current_time.toISOString() + "]: " + next_line;
    }
    messages.value = messages.value + next_line;
    if (scroll.checked) messages.scrollTop = messages.scrollHeight;
  }

  var clear_lines = function () {
    messages.value = "";
  }

</script>

</html>
)***";