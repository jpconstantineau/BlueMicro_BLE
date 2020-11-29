/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

 typedef struct { 
        bool    ledbacklight;  
        bool    ledrgb; 
        bool    VCCSwitchAvailable;  
        bool    VCCSwitchEnabled;  
        bool    ChargerControlAvailable;  
        bool    ChargerControlEnabled; 
        bool    WakeUpBLELED; 
        bool    WakeUpKBLED;  
        uint32_t timerkeyscaninterval;
        uint32_t timerbatteryinterval;   
    } PersistentState;

PersistentState persistentdata;
PersistentState saveddata;

#define FILENAME    "/adafruit.txt"
#define FILENAME_BSP "/bsp.txt"
#define FILENAME_VERSION "/compiled.txt"
#define FILENAME_DATA "/kb_state.dat"
// ARDUINO_BSP_VERSION
#define CONTENTS    "Adafruit Little File System test file contents"

const char compile_date[] = __DATE__ " " __TIME__;

Adafruit_LittleFS_Namespace::File file(InternalFS);
Adafruit_LittleFS_Namespace::File file_bsp(InternalFS);
Adafruit_LittleFS_Namespace::File file_version(InternalFS);
Adafruit_LittleFS_Namespace::File file_data(InternalFS);

void save_data()
{
      Serial.print("Open " FILENAME_DATA " file to write ... ");
        if( file_data.open(FILENAME_DATA, Adafruit_LittleFS_Namespace::FILE_O_WRITE) )
    {
      Serial.println("OK");
Serial.println(file_data.position());
      file_data.truncate(0);
      Serial.println(file_data.position());
      file_data.seek (0);
      Serial.println(file_data.position());
      //file_data.write(reinterpret_cast<char*>( &persistentdata), sizeof( PersistentState));
      auto* raw_data = reinterpret_cast<char*>(std::addressof(persistentdata));
      Serial.println(raw_data);
      file_data.write(raw_data, sizeof(PersistentState));
      file_data.flush();
      Serial.println(file_data.position());
      Serial.println(file_data.size());
      file_data.close();
    }else
    {
      Serial.println("Failed!");
    }
}

void load_data()
{
  file_data.open(FILENAME_DATA, Adafruit_LittleFS_Namespace::FILE_O_READ);
  if ( file_data )    // file existed
  {
    Serial.println(FILENAME_DATA " file exists");

        uint32_t readlen;

    readlen = file_data.read(reinterpret_cast<char *>(&saveddata), sizeof(PersistentState));
    file_data.close();
    Serial.println(reinterpret_cast<char *>(&saveddata));
    Serial.println(saveddata.timerbatteryinterval);
    Serial.println(saveddata.timerkeyscaninterval);
    
    persistentdata.ledbacklight = saveddata.ledbacklight;
    persistentdata.ledrgb = saveddata.ledrgb;
    persistentdata.VCCSwitchAvailable = saveddata.VCCSwitchAvailable;
    persistentdata.VCCSwitchEnabled = saveddata.VCCSwitchEnabled;
    persistentdata.ChargerControlAvailable = saveddata.ChargerControlAvailable;
    persistentdata.ChargerControlEnabled = saveddata.ChargerControlEnabled;
    persistentdata.WakeUpBLELED = saveddata.WakeUpBLELED;
    persistentdata.WakeUpKBLED = saveddata.WakeUpKBLED;
    persistentdata.timerkeyscaninterval = saveddata.timerkeyscaninterval;
    persistentdata.timerbatteryinterval = saveddata.timerbatteryinterval;
  }  else
  {
      persistentdata.ledbacklight = true;
  persistentdata.ledrgb = true;
  persistentdata.VCCSwitchAvailable = true;
  persistentdata.VCCSwitchEnabled = true;
  persistentdata.ChargerControlAvailable = true;
  persistentdata.ChargerControlEnabled = true;
  persistentdata.WakeUpBLELED = true;
  persistentdata.WakeUpKBLED = true;
  persistentdata.timerkeyscaninterval =42;
  persistentdata.timerbatteryinterval = 0;
  }
}

// the setup function runs once when you press reset or power the board
void setup() 
{

         persistentdata.ledbacklight = true;
  persistentdata.ledrgb = true;
  persistentdata.VCCSwitchAvailable = true;
  persistentdata.VCCSwitchEnabled = true;
  persistentdata.ChargerControlAvailable = true;
  persistentdata.ChargerControlEnabled = true;
  persistentdata.WakeUpBLELED = true;
  persistentdata.WakeUpKBLED = true;
  persistentdata.timerkeyscaninterval =42;
  persistentdata.timerbatteryinterval = 0; 
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb

  Serial.println("Internal Read Write File Example");
  Serial.println();

  // Wait for user input to run. Otherwise the code will 
  // always run immediately after flash and create the FILENAME in advance
  Serial.print("Enter to any keys to continue:");
  while ( !Serial.available() )
  {
    delay(1);
  }
  Serial.println();
  Serial.println();

  // Initialize Internal File System
  InternalFS.begin();

  file.open(FILENAME, Adafruit_LittleFS_Namespace::FILE_O_READ);
  file_bsp.open(FILENAME_BSP, Adafruit_LittleFS_Namespace::FILE_O_READ);
  file_version.open(FILENAME_VERSION, Adafruit_LittleFS_Namespace::FILE_O_READ);



  if ( file )    // file existed
  {
    Serial.println(FILENAME " file exists");
    
    uint32_t readlen;
    char buffer[64] = { 0 };
    readlen = file.read(buffer, sizeof(buffer));

    buffer[readlen] = 0;
    Serial.println(buffer);
    file.close();
  }else
  {
    Serial.print("Open " FILENAME " file to write ... ");

    if( file.open(FILENAME, Adafruit_LittleFS_Namespace::FILE_O_WRITE) )
    {
      Serial.println("OK");
      file.write(CONTENTS, strlen(CONTENTS));
      file.close();
    }else
    {
      Serial.println("Failed!");
    }
  }

  if ( file_bsp )     // file existed
  {
    Serial.println(FILENAME_BSP " file exists");
    uint32_t readlen;
    char buffer[64] = { 0 };
    readlen = file_bsp.read(buffer, sizeof(buffer));
    buffer[readlen] = 0;  // adds a null character to finish the string
    Serial.println(buffer);
    file_bsp.close();
  }else
  {
     Serial.print("Open " FILENAME_BSP " file to write ... ");
    if( file_bsp.open(FILENAME_BSP, Adafruit_LittleFS_Namespace::FILE_O_WRITE) )
    {
      Serial.println("OK");
      file_bsp.write(ARDUINO_BSP_VERSION, strlen(ARDUINO_BSP_VERSION));
      file_bsp.close();
    }else
    {
      Serial.println("Failed!");
    }
  }

  if ( file_version ) // file existed
  {
    Serial.println(FILENAME_VERSION " file exists");
    uint32_t readlen;
    char buffer[64] = { 0 };
    readlen = file_version.read(buffer, sizeof(buffer));
    buffer[readlen] = 0;  // adds a null character to finish the string
    Serial.println(buffer);
    file_version.close();
  }else
  {
    Serial.print("Open " FILENAME_VERSION " file to write ... ");
        if( file_version.open(FILENAME_VERSION, Adafruit_LittleFS_Namespace::FILE_O_WRITE) )
    {
      Serial.println("OK");
      file_version.write(compile_date, strlen(compile_date));
      file_version.close();
    }else
    {
      Serial.println("Failed!");
    }
  }


    load_data();
    persistentdata.timerbatteryinterval++;
    save_data();
  

  Serial.println("Done");
}

// the loop function runs over and over again forever
void loop() 
{
    load_data();
    persistentdata.timerbatteryinterval = millis();
    save_data();
    delay(3000);
  
}
