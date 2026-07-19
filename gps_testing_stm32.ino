#include <TinyGPS++.h>

HardwareSerial GPS(PB7, PB6);   // RX, TX
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  GPS.begin(9600);

  Serial.println("GNSS Test Started");
  Serial.println("Waiting for GPS Fix...");
}

void loop() {
  while (GPS.available()) {
    gps.encode(GPS.read());
  }

  static unsigned long lastPrint = 0;

  if (millis() - lastPrint > 2000) {
    lastPrint = millis();

    Serial.println("\n========================");

    // Location
    if (gps.location.isValid()) {
      Serial.print("Latitude  : ");
      Serial.println(gps.location.lat(), 6);

      Serial.print("Longitude : ");
      Serial.println(gps.location.lng(), 6);
    } else {
      Serial.println("Location  : No Fix");
    }

    // Altitude
    if (gps.altitude.isValid()) {
      Serial.print("Altitude  : ");
      Serial.print(gps.altitude.meters());
      Serial.println(" m");
    }

    // Speed
    if (gps.speed.isValid()) {
      Serial.print("Speed     : ");
      Serial.print(gps.speed.kmph());
      Serial.println(" km/h");
    }

    // Course / Heading
    if (gps.course.isValid()) {
      Serial.print("Heading   : ");
      Serial.print(gps.course.deg());
      Serial.println(" deg");
    }

    // Satellites
    if (gps.satellites.isValid()) {
      Serial.print("Satellites: ");
      Serial.println(gps.satellites.value());
    }

    // HDOP
    if (gps.hdop.isValid()) {
      Serial.print("HDOP      : ");
      Serial.println(gps.hdop.hdop());
    }

    // Date
    if (gps.date.isValid()) {
      Serial.print("Date      : ");
      Serial.print(gps.date.day());
      Serial.print("/");
      Serial.print(gps.date.month());
      Serial.print("/");
      Serial.println(gps.date.year());
    }

    // Time
    if (gps.time.isValid()) {
      Serial.print("UTC Time  : ");
      Serial.print(gps.time.hour());
      Serial.print(":");
      Serial.print(gps.time.minute());
      Serial.print(":");
      Serial.println(gps.time.second());
    }

    Serial.println("========================");
  }
}