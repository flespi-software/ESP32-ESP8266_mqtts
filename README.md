# ESP32/ESP8266 MQTTs
Simple example of secure mqtt connection with root CA/fingerprint for ESP32/ESP8266 boards (send data to mqtt.flespi.io via MQTT over TLS)

## Prerequisites:

- Arduino IDE
- Hardware: [ESP8266](https://en.wikipedia.org/wiki/ESP8266) or [ESP32](https://en.wikipedia.org/wiki/ESP32) board

Install library:
```
Sketch -> Include Library -> Manage Libraries... -> Type PubSub in Search field -> PubSubClient by Nick O'Leary -> Install.
```


## Build Setup

### install additional board to Arduino IDE
[Arduino board project Howto](https://github.com/esp8266/Arduino/blob/master/README.md#installing-with-boards-manager)

Official Arduino IDE info on how to [install additional cores](https://www.arduino.cc/en/Guide/Cores)

### Select board
Arduino IDE: Tools -> Board -> Your board type (ESP32 Dev Module in my case [ESP32 DevkitC v4](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html))

### Get FlespiToken
register on [flespi platform](https://flespi.io), create a Token in a tokens Tab and paste token in [credentials.h file](https://github.com/flespi-software/ESP32-ESP8266_mqtts/blob/main/ESP_Certificate/credentials.h) definitions:

```#define FLESPI_TOKEN    "FlespiToken REPLACE_WITH_YOUR_FLESPI_TOKEN" ```

### Test
compile the project and flash the board

To test it works you can use flespi [online MQTT client](https://flespi.com/tools/mqtt-board): 

Paste yout token and subscribe to topic *"hello/world"*

### Troubleshooting
If you get an error when uploading a sketch:
```
A fatal error occurred: Could not open /dev/ttyACM0, the port doesn't exist
Failed uploading: uploading error: exit status 2
```
Try running the commands:
```
sudo adduser $USER $(stat --format="%G" /dev/ttyACM0 )
sudo chmod a+rw /dev/ttyACM0
```

## License
[MIT](https://github.com/flespi-software/ESP32-ESP8266_mqtts/blob/main/LICENSE) license.
