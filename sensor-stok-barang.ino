//Pengecekan Stok Barang Real-time menggunakan PIR sensor

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned int barang = 0; // Variabel untuk menyimpan jumlah barang yang terdeteksi
byte pinPIR = 12; // Pin yang digunakan untuk sensor PIR

void ISR(){
  barang++; // Jika ada barang yang terdeteksi, jumlah barang bertambah satu
}

void setup() {
  Serial.begin(115200);
  Serial.println("Pengecekan Stok Barang Real-time");
  attachInterrupt(pinPIR, ISR, RISING); // Melampirkan fungsi ISR ke interrupt pada pin PIR yang aktif pada naiknya sinyal

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("PENGHITUNG ITEM");
  delay(250);
  lcd.setCursor(0, 1);
  lcd.print("OTOMATIS");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("JUMLAH ITEM");
}

void loop() {
  boolean deteksi = digitalRead(pinPIR); // Membaca status sensor PIR (ada/tidaknya pergerakan)
  Serial.print(deteksi);
  Serial.print(" Jumlah barang = ");
  Serial.println(barang); // Mencetak jumlah barang yang terdeteksi ke Serial Monitor
  lcd.setCursor(0,1);
  lcd.print(barang); // Menampilkan jumlah barang yang terdeteksi di LCD
  delay(100); // Delay untuk memberikan jeda antar pembacaan sensor
}