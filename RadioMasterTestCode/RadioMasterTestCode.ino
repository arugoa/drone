#include <SoftwareSerial.h>
#include <AlfredoCRSF.h>

// Use Pin 10 for RX (Connect to Receiver TX)
// Use Pin 11 for TX (Connect to Receiver RX via voltage divider)
SoftwareSerial elrsSerial(10, 11);
AlfredoCRSF crsf;

void setup() {
  // Communication to your PC
  Serial.begin(115200);
  
  // Communication to ELRS Receiver
  // IMPORTANT: Set your Pocket LUA script to 57600 baud!
  elrsSerial.begin(115200);
  
  crsf.begin(elrsSerial);
  Serial.println("System Initialized...");
}

void loop() {
  // Must be called every frame to process incoming data
  crsf.update();

  if (crsf.isLinkUp()) {
    // getChannel(3) is typically Throttle in ELRS/CRSF
    int ch1 = crsf.getChannel(1);
    int ch2 = crsf.getChannel(2);
    int ch3 = crsf.getChannel(3);
    int ch4 = crsf.getChannel(4);
    int ch5 = crsf.getChannel(5);
    int ch6 = crsf.getChannel(6);
    int ch7 = crsf.getChannel(7);
    int ch8 = crsf.getChannel(8);
    int ch9 = crsf.getChannel(9);
    int ch10 = crsf.getChannel(10);
    int ch11 = crsf.getChannel(11);
    int ch12 = crsf.getChannel(12);
    int ch13 = crsf.getChannel(13);
    int ch14 = crsf.getChannel(14);
    int ch15 = crsf.getChannel(15);
    int ch16 = crsf.getChannel(16);

    // Formatted output: \t creates aligned columns
// --- ROW 1 ---
    Serial.print("CH1: ");  Serial.print(ch1);
    Serial.print("\tCH2: "); Serial.print(ch2);
    Serial.print("\tCH3: "); Serial.print(ch3);
    Serial.print("\tCH4: "); Serial.println(ch4); 

    // --- ROW 2 ---
    Serial.print("CH5: ");  Serial.print(ch5);
    Serial.print("\tCH6: "); Serial.print(ch6);
    Serial.print("\tCH7: "); Serial.print(ch7);
    Serial.print("\tCH8: "); Serial.println(ch8);

    // --- ROW 3 ---
    Serial.print("CH9: ");  Serial.print(ch9);
    Serial.print("\tCH10: "); Serial.print(ch10);
    Serial.print("\tCH11: "); Serial.print(ch11);
    Serial.print("\tCH12: "); Serial.println(ch12);

    // --- ROW 4 ---
    Serial.print("CH13: "); Serial.print(ch13);
    Serial.print("\tCH14: "); Serial.print(ch14);
    Serial.print("\tCH15: "); Serial.print(ch15);
    Serial.print("\tCH16: "); Serial.println(ch16);

    // Add a divider so you can see each "frame" of data
    Serial.println("-------------------------------------------------------");
  } else {
    Serial.println("Searching for Link...");
  }

  // Small delay to prevent flooding the serial monitor
  delay(250);
}