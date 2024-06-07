#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
String idKartu = "";


MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  // buka pintu melalui idCard
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {  //cek apakah ada kartu yang di scand atau tidak
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        idKartu.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
        idKartu.concat(String(mfrc522.uid.uidByte[i], HEX));                //untuk menggabungan byte id dari kartu ke dalam variabel string
      }
      Serial.println(idKartu);
      mfrc522.PICC_HaltA(); //menghentikan komunikasi dengan kartu untuk menjalankan aksi di bawah
      mfrc522.PCD_StopCrypto1(); // Hentikan enkripsi pada kartu RFID
      delay(500);
  }
}