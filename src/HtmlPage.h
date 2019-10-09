/**
 * files that include the skeleton of the webpage shown on the server
 * */

#include <Arduino.h>

// HTML web page to handle 1 input field
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>CNH Control panel</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    input1: <input type="text" name="New position:">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";