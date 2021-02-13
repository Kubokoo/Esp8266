# Esp8266
Small project on ESP8266

Parts:
* ESP8266
* AM2302 DHT22
* Cables

Datagrams and other:
* ![ESP8266 Pins](https://cdn.forbot.pl/blog/wp-content/uploads/2020/01/ESP8266_pinout_ESP_8266_DEVMODULE_PINOUT.png)
* https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf

Connections:
* ESP D2 pin to second form left pin on DHT
* ESP GND pin to far left pin on DHT
* ESP 3V pin to far right pin on DHT


Arduino IDE config:
* Adding addres http://arduino.esp8266.com/stable/package_esp8266com_index.json as addisional URL for board manager
* Addin board in board manager (esp8266 by ESP8266 Community ver 2.7.4) and selecting NodeMCU 1.0 (ESP-12E Module)
* Adding DHT sensor libary ver 1.4.1 to project
* Selecting COM port
