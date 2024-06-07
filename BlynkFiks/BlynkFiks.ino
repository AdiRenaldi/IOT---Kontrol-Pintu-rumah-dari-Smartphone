#define BLYNK_TEMPLATE_ID "TMPL6Qwcemnl1"                   //id tamplate untuk menjalankan alat
#define BLYNK_TEMPLATE_NAME "NailaIOT"                      //nama tamplate
#define BLYNK_AUTH_TOKEN "m1heKIzoeYTVSkU9t1DwDrosNpL_NZTC"  //token atau id yang tehubung dengan node mcu dan hp

#define BLYNK_PRINT Serial       //jalankan blynk dalam serial


#include <ESP8266WiFi.h>          //libraries wifi
#include <BlynkSimpleEsp8266.h>   //libraries untuk koneksi ke blynk

char ssid[] = "V2022";
char pass[] = "ilacannn";

int dataBlink;        //menampung data yg diterima dari blynk
String dataBaru = "";   //untuk menampung data yang barusan di cetak


// pin Lcd Blynk
WidgetLCD lcd(V1);        //mencetak data pada blynk dengan inisialisasi v1 dalam blynk

void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);    // jalakan fungsi blynk dengan mengirim data ke parameter
  lcd.clear();      //hapus data di layar blynk
  lcd.print(1, 0, "PINTU IOT");     //cetak data pintu iot
}

void loop()
{
  Blynk.run();    //jalankan blynk

  String data = "";     //tampung data dari arduino
  while(Serial.available() > 0){      //perulangan untuk periksa jika ada data dari arduino. jila data ada
    data += char(Serial.read());  //ambil data tersebut lalu tampung di variabel data
  }

  // print data di Lcd blynk 
  if(data.length() > 0){    //jika ada data jalankan kfungsi didalamnya
    lcd.clear();            //hapus dara di layar blynk
    lcd.print(1, 0, data);    //cetak data baru di layar blynk
  }

  // instruksi pintu dari blybk
  if(dataBlink == 1 && dataBaru != "1"){        //data yang dikirim dari blynk yaitu nilai 1 dan data yang tampung dalam variabel data baru bukan 1 makan jalankan fungsi didalamnya
    Serial.println("1");      //kirim nilai 1 ke arduino, artinya pintu terbuka
    dataBaru = "1";           //set data baru == 1
  }else if(dataBlink == 0 && dataBaru != "0"){
    Serial.println("0");
    dataBaru = "0";
  }
  
  delay(1000);
}
BLYNK_WRITE(V5) {       //fungsi untuk mendapatkan data dari blynk seperti angka 1 dan 0
  dataBlink = param.asInt();    //ketika ada datanya, tangkap data tersebut dan tampung di variabel dataBlink.
}
