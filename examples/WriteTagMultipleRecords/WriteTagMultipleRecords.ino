// Writes multiple records to an NFC formatted tag. Note this erases all existing records.

#include <SPI.h>
#include <MFRC522.h>
#include "NfcAdapter.h"

#define SS_PIN 5

// MFRC522 setup
MFRC522DriverPinSimple ss_pin(SS_PIN); // Configurable, see typical pin layout above.

MFRC522DriverSPI driver{ss_pin}; // Create SPI driver.

MFRC522 mfrc522{driver}; // Create MFRC522 instance.

NfcAdapter nfc = NfcAdapter(&mfrc522);

void setup()
{
    Serial.begin(9600);
    Serial.println("NDEF multiple record writer\nPlace a formatted Mifare Classic or Ultralight NFC tag on the reader.");
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522
    nfc.begin();
}

void loop()
{
    if (nfc.tagPresent())
    {
        Serial.println("Writing multiple records to NFC tag");
        NdefMessage message = NdefMessage();
        message.addTextRecord("Hello, Arduino!");
        message.addUriRecord("https://arduino.cc");
        message.addTextRecord("Goodbye, Arduino!");
        boolean success = nfc.write(message);
        if (success)
        {
            Serial.println("\tSuccess. Try reading this tag with your phone.");
            delay(10000);
        }
        else
        {
            Serial.println("\tWrite failed");
        }
    }
    delay(5000);
}
