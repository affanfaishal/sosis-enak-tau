#include <DHT.h> // Memanggil library untuk sensor DHT
#include <LiquidCrystal_I2C.h>// Memanggil library untuk LCD I2C
#define DHTPIN 5 // Menentukan pin data DHT22 terhubung ke pin 2
#define DHTTYPE DHT22 // Menentukan tipe sensor yang digunakan (DHT22)
// Membuat objek dht dengan pin dan tipe yang sudah ditentukan
DHT dht(DHTPIN, DHTTYPE);
// Membuat objek lcd dengan alamat I2C 0x27 dan ukuran 16 kolom 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
// Memulai komunikasi serial dengan baud rate 9600
  Serial.begin(9600);
  dht.begin();// Memulai sensor DHT
  lcd.init(); // Memulai LCD
  lcd.backlight();  // Menyalakan lampu latar LCD
  lcd.setCursor(0, 0);      // Menampilkan teks awal di LCD
  lcd.print("Monitoring");
  lcd.setCursor(0, 1);
  lcd.print("Sensor Dimulai");
  delay(2000);// Delay 2 detik sebelum masuk loop
  lcd.clear();// Membersihkan tampilan LCD
  }

void loop() {
  // Membaca nilai kelembapan
  float humidity = dht.readHumidity();
  // Membaca nilai suhu dalam Celcius
  float temperature = dht.readTemperature();
  // Mengecek apakah pembacaan gagal
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca DHT!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    delay(2000);
    return; // Kembali ke awal loop
  }
  // Menampilkan data ke Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.print(" C  ");

  Serial.print("Kelembapan: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Menampilkan suhu di baris pertama LCD
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(temperature);
  lcd.print(" C ");

  // Menampilkan kelembapan di baris kedua LCD
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" % ");
// Delay 2 detik sebelum pembacaan ulang
  delay(2000);
  }