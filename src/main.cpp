/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Libraries for SD card
#include "FS.h"
#include "SD.h"
#include <SPI.h>

// SHT31 library
#include <Wire.h>
#include <Adafruit_SHT31.h>

// Libraries for RTC
#include <Wire.h>
#include <RTClib.h>

// Define deep sleep options
uint64_t uS_TO_S_FACTOR = 1000000;  // Conversion factor for micro seconds to seconds
// Sleep for 10 minutes = 600 seconds
uint64_t TIME_TO_SLEEP = 15;

// Define CS pin for the SD card module
#define SD_CS 5

// Save reading number on RTC memory
RTC_DATA_ATTR int readingID = 0;

String dataMessage;

// Initialize SHT31 sensor
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// Initialize RTC
RTC_DS3231 rtc;

// Variables to save date and time
String dayStamp;
String timeStamp;

// Temperature and Humidity Sensor variables
float temperature;
float humidity;

// Function to get temperature and humidity
void getReadings(){
  temperature = sht31.readTemperature(); // Temperature in Celsius
  humidity = sht31.readHumidity();       // Humidity in percentage

  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);
}

// Function to get date and time from RTC
void getTimeStamp() {
  DateTime now = rtc.now();

  // Format date and time
  timeStamp = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  dayStamp = String(now.day()) + "-" + String(now.month()) + "-" + String(now.year());

  Serial.println(dayStamp);
  Serial.println(timeStamp);
}
// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}
// Write the sensor readings on the SD card
void logSDCard() {
  dataMessage = String(readingID) + "," + String(dayStamp) + "," + String(timeStamp) + "," + 
                String(temperature) + "," + String(humidity) + "\r\n";
  Serial.print("Save data: ");
  Serial.println(dataMessage);
  appendFile(SD, "/data.txt", dataMessage.c_str());
}

// Write to the SD card (DON'T MODIFY THIS FUNCTION)
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void setup() {
  // Start serial communication for debugging purposes
  Serial.begin(115200);

  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    // The following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Initialize SD card
  if (!SD.begin(SD_CS)) {
    Serial.println("ERROR - SD card initialization failed!");
    return;    // init failed
  }

  // If the data.txt file doesn't exist
  // Create a file on the SD card and write the data labels
  File file = SD.open("/data.txt");
  if (!file) {
    Serial.println("File doesn't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/data.txt", "Reading ID, Date, Hour, Temperature, Humidity \r\n");
  } else {
    Serial.println("File already exists");  
  }
  file.close();

  // Enable Timer wake_up
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  // Initialize SHT31 sensor
  if (!sht31.begin(0x44)) {   // Set to 0x45 if your sensor has that address
    Serial.println("Couldn't find SHT31 sensor!");
    while (1);
  }

  getReadings();
  getTimeStamp();
  logSDCard();
  
  // Increment readingID on every new reading
  readingID++;
  
  // Start deep sleep
  Serial.println("DONE! Going to sleep now.");
  esp_deep_sleep_start(); 
}

void loop() {
  // The ESP32 will be in deep sleep
  // it never reaches the loop()
}


