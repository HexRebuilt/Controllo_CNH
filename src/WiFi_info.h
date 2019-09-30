#include <Arduino.h>
//#define WIFI_NET
#ifdef WIFI_NET
    #define WiFi_SSID "KyneproxSRL-2.4"
    #define WiFi_PSW "KyneproxPD3X"
#else
    #define WiFi_SSID "KYNEPROX-VR-AP"
    #define WiFi_PSW "KynePD3X" 
#endif