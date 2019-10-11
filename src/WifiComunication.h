/**
 * File that menages the wifi comunication both in input and as a webserver
 * */

#include <Arduino.h>
#include <WiFi101.h>
    
    ///////please enter your sensitive data in the Secret tab/Secrets.h
    char ssid[] = SECRET_SSID;        // your network SSID (name)
    char pass[] = SECRET_PSW;         // your network password (use for WPA, or use as key for WEP)
    int status = WL_IDLE_STATUS;      // the WiFi radio's status

    //in order to work it's required to be outside the class
    WiFiServer server(80);

class WiFiComunication{
    private:
        
        const char* PARAM_INPUT_1 = "fromWeb";
        String readString = "";
        String readedposition = ""; 
        
        /**
         * funciton that takes the string from the get method and extrapolate the characters needed
         * INPUT STRING FORMAT:
         *      "DATA RECIEVED: GET /?fromWeb=45-9-6&Submit=Set+position HTTP/1.1
                 Host: 192.168.0.24"
            so this function remooves everything that's not userfull to the instruction
         * */
        void analyzeString(String fromWeb){
            if(fromWeb.indexOf("DATA RECIEVED: GET")){
                //Serial.println("DEBUG");
                //Serial.println(fromWeb);

                boolean begin = false;
                for (int i = 0; i < fromWeb.length(); i++)
                {
                    //when i found the "&" means that i have finished the acquisition
                    if (fromWeb.charAt(i) == '&')
                    {
                        begin = false;
                        return;
                    }

                    //saving the characters
                    if (begin)
                    {
                        char c = fromWeb.charAt(i);
                        //Serial.println(c);
                        readedposition += c;
                        //analyzeString += tmp;
                    }
                    

                    //looking for the first '=' to start acquiring the stirng
                    if (fromWeb.charAt(i) == '='){
                        begin = true; //means that from the next character i need to save it
                    }
                }
                
                        

            }
        }

        void clientConnected(){
            // compare the previous status to the current status
            if (status != WiFi.status()) {
                // it has changed update the variable
                status = WiFi.status();

                if (status == WL_AP_CONNECTED) {
                byte remoteMac[6];

                // a device has connected to the AP
                Serial.print("Device connected to AP, MAC address: ");
                WiFi.APClientMacAddress(remoteMac);
                printMacAddress(remoteMac);
                } else {
                // a device has disconnected from the AP, and we are back in listening mode
                Serial.println("Device disconnected from AP");
                }
            }
        }

        void printWiFiStatus() {
            // print the SSID of the network you're attached to:
            Serial.print("SSID: ");
            Serial.println(WiFi.SSID());

            // print your WiFi shield's IP address:
            IPAddress ip = WiFi.localIP();
            Serial.print("IP Address: ");
            Serial.println(ip);

            // print the received signal strength:
            long rssi = WiFi.RSSI();
            Serial.print("signal strength (RSSI):");
            Serial.print(rssi);
            Serial.println(" dBm");
            // print where to go in a browser:
            Serial.print("To see this page in action, open a browser to http://");
            Serial.println(ip);

        }

        //set of arduino base function to connect to a network
        void printWiFiData() {
            // print your WiFi shield's IP address:
            IPAddress ip = WiFi.localIP();
            Serial.print("IP Address: ");
            Serial.println(ip);
            Serial.println(ip);

            // print your MAC address:
            byte mac[6];
            WiFi.macAddress(mac);
            Serial.print("MAC address: ");
            printMacAddress(mac);

        }

        void printCurrentNet() {
            // print the SSID of the network you're attached to:
            Serial.print("SSID: ");
            Serial.println(WiFi.SSID());

            // print the MAC address of the router you're attached to:
            byte bssid[6];
            WiFi.BSSID(bssid);
            Serial.print("BSSID: ");
            printMacAddress(bssid);

            // print the received signal strength:
            long rssi = WiFi.RSSI();
            Serial.print("signal strength (RSSI):");
            Serial.println(rssi);

            // print the encryption type:
            byte encryption = WiFi.encryptionType();
            Serial.print("Encryption Type:");
            Serial.println(encryption, HEX);
            Serial.println();
        }

        void printMacAddress(byte mac[]) {
            for (int i = 5; i >= 0; i--) {
                if (mac[i] < 16) {
                Serial.print("0");
                }
                Serial.print(mac[i], HEX);
                if (i > 0) {
                Serial.print(":");
                }
            }
            Serial.println();
        }
        
    public:

        /**
         * function that creates the html page with the reading information 
         * 
         * TODO adding the set line
         * */
        void writeHTML (String messageOut){
            clientConnected();
            WiFiClient client = server.available();
            if (client) {
                // an http request ends with a blank line
                boolean currentLineIsBlank = true;
                while (client.connected()) {
                    if (client.available()) {
                        char c = client.read();
                        
                        if (readString.length() < 100) {
                            //store characters to string
                            readString += c;
                        }

                        // if you've gotten to the end of the line (received a newline
                        // character) and the line is blank, the http request has ended,
                        // so you can send a reply
                        if (c == '\n' && currentLineIsBlank) {
                        // send a standard http response header
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        //lines added later
                        //client.println("Connection: close");  // the connection will be closed after completion of the response
                        //client.println("Refresh: 10");  // refresh the page automatically every 5 sec
                        client.println("<!DOCTYPE HTML>");
                        client.println();

                        //printing the webpage
                        client.println("<HTML>");
                        client.println("<HEAD>");
                        client.println("<TITLE>Arduino GET test page</TITLE>");
                        client.println("</HEAD>");
                        client.println("<BODY>");

                        client.println("<H1>CNH Control Panel</H1>");

                        client.println("The position format must be Zheight-Inclination-Rotation");
                        client.println("\tIn form:[mm]-[Degrees]-[Degrees]");

                        client.println("<FORM ACTION='/' method=get >"); //uses IP/port of web page

                        client.println("New position to set: <INPUT TYPE=TEXT NAME='fromWeb' VALUE='' ><BR>"); //cutted SIZE='25' MAXLENGTH='50'

                        client.println("<INPUT TYPE=SUBMIT NAME='Submit' VALUE='Set position'>");

                        client.println("</FORM>");

                        analyzeString(readString);


                        //http//.../?NOMEPARAMETRO=VALORE&ALTROPARAM=VALORE2
                        //ù
                        // GET /?NOMEPARAMETRO=VALORE&ALTROPARAM=VALORE2 HTTP/1.1

                        // output the value of each analog input pin
                        client.println(messageOut);

                        client.println("<BR>");

                        client.println("</BODY>");
                        client.println("</HTML>");

                        break;
                    }
                    if (c == '\n') {
                    // you're starting a new line
                    currentLineIsBlank = true;
                    }
                    else if (c != '\r') {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                    }
                }
                }
                // give the web browser time to receive the data
                delay(10);
                // close the connection:
                client.stop();
            }
        }    
        

        void startup(){
            WiFi.setPins(8,7,4,2); //in order to use the wifi module
            
            // check for the presence of the shield:
            if (WiFi.status() == WL_NO_SHIELD) {
                Serial.println("WiFi shield not present");
                // don't continue:
                while (true);
            }
            // attempt to connect to WiFi network:
            Serial.print("Attempting to connect to WPA SSID: ");
            Serial.println(ssid);
            // Connect to WPA/WPA2 network:
            status = WiFi.begin(ssid, pass);
            // wait 10 seconds for connection:
            delay(10000);

            if ( status != WL_CONNECTED) {
                Serial.println("Couldn't get a wifi connection");
                
                                
                // print the network name (SSID);
                Serial.print("Creating access point named: ");
                Serial.println(SSID_AP);
                // Create open network. Change this line if you want to create an WEP network:
                status = WiFi.beginAP(SSID_AP);
                if (status != WL_AP_LISTENING) {
                    Serial.println("Creating access point failed");
                    // don't continue
                    while (true);
                }
                  // you're connected now, so print out the status
                printWiFiStatus();
                delay(5000);
                server.begin();
            }
            else {
                // you're connected now, so print out the data:
                Serial.print("You're connected to the network");
                printCurrentNet();
                printWiFiData();
                server.begin();
            }
        }
            
        String getDataIn(){
            //Serial.println(readedposition);
            String tmp = readedposition;
            
            //clearing string for next read
            readedposition="";
            readString="";
            return tmp;
        }
};