#include <WiFiManager.h>


//This example shows how to require encrypted firmware bin files for the updates to protect the code.
//Follow these steps to encrypt the firmware.
//Find the application.ino.bin file from the last line of the output window in Arduino when compiling and flashing.
//The line will have the command  esptool.exe  followed by 4 separate bin files.   Copy the entire line to notepad and extract the last bin file location
//Get the memory address located on that same esptool.exe line.    The last address is where the file will be placed in the ESP32 and is required for decryption.
//The address is typically 0x10000.   Use this address in you#include <WiFiManager.h>


//This example shows how to require encrypted firmware bin files for the updates to protect the code.
//Follow these steps to encrypt the firmware.
//Find the application.ino.bin file from the last line of the output window in Arduino when compiling and flashing.
//The line will have the command  esptool.exe  followed by 4 separate bin files.   Copy the entire line to notepad and extract the last bin file location
//Get the memory address located on that same esptool.exe line.    The last address is where the file will be placed in the ESP32 and is required for decryption.
//The address is typically 0x10000.   Use this address in your source code.
//download and install ESP-IDF.  Use the default settings.   https://dl.espressif.com/dl/esp-idf/    
//Open the ESP-IDF command window use the cd command to navigate to a directory where you will place the bin file.
//place the bin file there.   Notice the last \ in the file location from the Arduino output line needs to be switched to a /
//Generate a 256bit encryption key with the following command:
//espsecure.py generate_flash_encryption_key internetupdate_key.bin
//read the key with a hex editor or the command:   certutil -dump -v internetupdate_key.bin
//Manually, copy the key to your source code.    This is the key that will allow OTA firmware updates
//encrypt the bin file with the following command:   
//espsecure.py encrypt_flash_data -k internetupdate_key.bin --flash_crypt_conf 0xf -a 0x10000 -o [encrypted project file name].bin [project file name].bin

//finally, to lock down the ESP32 and keep the code secret, blow the follwing fuses.   Warning, the chip can only use OTA for any future updates
//espefuse.py burn_efuse DIS_DOWNLOAD_MODE 1  DIS_DOWNLOAD_ICACHE 1  SOFT_DIS_JTAG 7  DIS_PAD_JTAG 1 -p COM14
//you can also blow the fuses in your firmware.

void setup() {
    // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    delay(2000);   //wait for ESP32 usb to connect after reset for debugging
    Serial.begin(115200);

    Serial.println("Starting Encrypted WiFiManager Demo...");
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result



    //************************ comment out these commands for non encrypted updates *******************************
  
                              //Be sure to change your encryption key to match 
    const uint8_t OTA_KEY[32] = {0x34, 0x15, 0x91, 0xd5, 0x3f, 0xef, 0x29, 0xf3, 0xb3, 0x0c, 0x72, 0xde, 0xff, 0xf7, 0x23, 0x06,
                                 0x7c, 0xa7, 0x1b, 0xc3, 0xb0, 0xac, 0x95, 0x58, 0x68, 0x99, 0xa5, 0x55, 0xbc, 0x5c, 0xf3, 0xde};
    const uint32_t OTA_ADDRESS = 0x10000;  //address for the start of the main code partition.
    
    wm.setOTAEncryption(OTA_KEY,OTA_ADDRESS);   //require encrypted OTA updates

    //*************************************************************************************************************

    wm.setConnectRetries(5);

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("AutoConnectAP"); // password protected ap


    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }

}

void loop() {
    // put your main code here, to run repeatedly:   
}
r source code.
//download and install ESP-IDF.  Use the default settings.   https://dl.espressif.com/dl/esp-idf/    
//Open the ESP-IDF command window use the cd command to navigate to a directory where you will place the bin file.
//place the bin file there.   Notice the last \ in the file location from the Arduino output line needs to be switched to a /
//Generate a 256bit encryption key with the following command:
//espsecure.py generate_flash_encryption_key internetupdate_key.bin
//read the key with a hex editor or the command:   certutil -dump -v internetupdate_key.bin
//Manually, copy the key to your source code.    This is the key that will allow OTA firmware updates
//encrypt the bin file with the following command:   
//espsecure.py encrypt_flash_data -k internetupdate_key.bin --flash_crypt_conf 0xf -a 0x10000 -o [encrypted project file name].bin [project file name].bin

//finally, to lock down the ESP32 and keep the code secret, blow the follwing fuses.   Warning, the chip can only use OTA for any future updates
//espefuse.py burn_efuse DIS_DOWNLOAD_MODE 1  DIS_DOWNLOAD_ICACHE 1  SOFT_DIS_JTAG 7  DIS_PAD_JTAG 1 -p COM14
//you can also blow the fuses in your firmware.

void setup() {
    // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    delay(2000);   //wait for ESP32 usb to connect after reset for debugging
    Serial.begin(115200);

    Serial.println("Starting Encrypted WiFiManager Demo...");
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result



    //************************ comment out these commands for non encrypted updates *******************************
  
                              //Be sure to change your encryption key to match 
    // const uint8_t OTA_KEY[32] = {0x34, 0x15, 0x91, 0xd5, 0x3f, 0xef, 0x29, 0xf3, 0xb3, 0x0c, 0x72, 0xde, 0xff, 0xf7, 0x23, 0x06,
    //                              0x7c, 0xa7, 0x1b, 0xc3, 0xb0, 0xac, 0x95, 0x58, 0x68, 0x99, 0xa5, 0x55, 0xbc, 0x5c, 0xf3, 0xde};

    // wm.setOTAEncryption(OTA_KEY,0x10000);   //make sure to put this line before opening the web portal.  Note the address is in hex

    //*************************************************************************************************************

    wm.setConnectRetries(5);

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("AutoConnectAP"); // password protected ap


    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }

}

void loop() {
    // put your main code here, to run repeatedly:   
}
