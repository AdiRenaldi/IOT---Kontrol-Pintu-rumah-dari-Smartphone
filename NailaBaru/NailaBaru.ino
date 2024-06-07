#include <SPI.h>        //libraries berfungsi untuk menerjemahkan pin dalam rdfid
#include <MFRC522.h>    //libraries berfungsi untuk mengolah bit dari KTP yang di tangkap rfid

#define RST_PIN 9       //untuk inisialisasi pin arduino 9 pada rfid pin rst
#define SS_PIN 10       //untuk inisialisasi pin arduino 9 pada rfid pin ss

const int buzzer = 4;   //pin arduino 4 ke kabel negatif buzzer
const int relay = 2;    //pin arduino 2 ke kabel pin relay output
const int hijau = 5;    //pin arduino 5 ke kabel negatif led
const int merah = 6;    //pin arduino 6 ke kabel negatif led

String idKartu = "";    //variabel untuk menampung id

String naila = "042129e2455a80";      //menyimpan id KTP naila dalam variabel naila
String amina = "058bc699dd9200";      //menyimpan id KTP aminah dalam variabel aminah
String aninda = "0446880a354e80";     //menyimpan id KTP anindah dalam variabel anindah
String kartuRusak = "04473eeadf4b80";  //menyimpan id KTP ktpRusak dalam variabel ktpRusak


MFRC522 mfrc522(SS_PIN, RST_PIN);`    //menjalankan fungsi dalam libraries dengan parameter pin yang didefinisikan untuk arduino

void setup() {                //jalankan semua fungsi didalam arduino mengen mengsetnya sekali saat alat di jalankan
  Serial.begin(9600);       //mencetak data pada serial monitor
  SPI.begin();              //menjalankan libraries untuk komunikasi antar pin rfid dan arduino
  mfrc522.PCD_Init();         //jalankan fungsi rfid
  pinMode(relay, OUTPUT);       //jalankan relay dengan memberikan output tegangan
  pinMode(buzzer, OUTPUT);      //jalankan buzzer dengan memberikan output tegangan
  pinMode(hijau, OUTPUT);       //jalankan led hijau dengan memberikan output tegangan
  pinMode(merah, OUTPUT);       //jalankan led merah dengan memberikan output tegangan
  digitalWrite(relay, HIGH);     //mematikan relay diawal
}

void loop() {
  // buka pintu melalui idCard
if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {  //cek apakah ada kartu yang di scand atau tidak
    for (byte i = 0; i < mfrc522.uid.size; i++) {             //jika ada jalankan tangkap data bitnya
      idKartu.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));   //untuk mengolah data bit dari rfid dan mebandingkannya dengan kondisi ternary
      idKartu.concat(String(mfrc522.uid.uidByte[i], HEX));                //untuk menggabungan byte id dari kartu ke dalam variabel string
    }
  
    mfrc522.PICC_HaltA(); //menghentikan komunikasi dengan kartu untuk menjalankan aksi di bawah
    mfrc522.PCD_StopCrypto1(); // Hentikan enkripsi pada kartu RFID
    delay(500);               //sistem menunggu stengah detik
}
if(idKartu !=""){            // cek apakah ada ktp yg di scant atau tidak
  if(idKartu == naila){       //jika ada ktp di scan periksa id nya dengan id yang ada di variabel naila, jalankan fungsi didalamnya jika sama.
    Serial.println("NAILA -> MASUK RUANGAN");     // cetak data ke serial monitor dan kirim ke node mcu
    delay(20);
    digitalWrite(hijau, HIGH);
    digitalWrite(relay, LOW);
    delay(5000);
    digitalWrite(relay, HIGH);
    digitalWrite(hijau, LOW);
    Serial.println("PINTU TERTUTUP");
    idKartu = "";
    delay(1000);
  }else if(idKartu == amina){
    Serial.println("AMINAH -> MASUK RUANGAN");
    delay(20);
    digitalWrite(hijau, HIGH);
    digitalWrite(relay, LOW);
    delay(5000);
    digitalWrite(relay, HIGH);
    digitalWrite(hijau, LOW);
    Serial.println("PINTU TERTUTUP");
    idKartu = "";
    delay(1000);
  }else if(idKartu == aninda){
    Serial.println("Anindah -> MASUK RUANGAN");
    delay(20);
    digitalWrite(hijau, HIGH);
    digitalWrite(relay, LOW);
    delay(5000);
    digitalWrite(relay, HIGH);
    digitalWrite(hijau, LOW);
    Serial.println("PINTU TERTUTUP");
    idKartu = "";
    delay(1000);
  }else if(idKartu == kartuRusak){
    Serial.println("KARTU RUSAK -> MASUK RUANGAN");
    delay(20);
    digitalWrite(hijau, HIGH);
    digitalWrite(relay, LOW);
    delay(5000);
    digitalWrite(relay, HIGH);
    digitalWrite(hijau, LOW);
    Serial.println("PINTU TERTUTUP");
    idKartu = "";
    delay(1000);
  }else if(idKartu != naila && idKartu != amina && idKartu != aninda && idKartu != kartuRusak){       //jika data id dari variabel yang di definisikan diatas tidak sama maka jalankan ini

    Serial.println("SEORANG MENCOBA MASUK");
    // Serial.println(idKartu);
    delay(20);

    digitalWrite(relay, HIGH);   //relay mati, artinya selonoid tidak membuka pintu
    digitalWrite(merah, HIGH);   //nyalakan led merah
    digitalWrite(buzzer, HIGH);   //nyalakan buzzer
    delay(1000);
    digitalWrite(merah, LOW);   //led mati
    digitalWrite(buzzer, LOW);    //buzzer mati
    delay(500);
    digitalWrite(merah, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(merah, LOW);
    digitalWrite(buzzer, LOW);
    delay(500);
    digitalWrite(merah, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(merah, LOW);
    digitalWrite(buzzer, LOW);
    delay(1000);
    idKartu = "";
  } 
}    
  else {
    if (Serial.available()){        //menerima data dari inputan blink yang di kirim oleh node mcu
        String data = String(char(Serial.read()));      //cetak data nya dan tampung du variabel data
        // Serial.println(data);
          if (data == "1") {        //ketika data yang di terima bernilai 1 maka jalankan fungsi didalam kondisi if(buka pintu)
              digitalWrite(hijau, HIGH);
              digitalWrite(relay, LOW);
              Serial.println("PINTU TERBUKA");
              data = "";
              delay(1000);
            } else if(data == "0"){
              digitalWrite(relay, HIGH);
              digitalWrite(hijau, LOW);
              Serial.println("PINTU TERTUTUP");
              data = "";
              delay(1000);
          }
    }
  }
  delay(50);
}