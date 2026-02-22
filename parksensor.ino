// Deklarasi pin
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 6;

// Variabel
long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Mengirim gelombang ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Membaca durasi pantulan
  duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak (cm)
  distance = duration * 0.034 / 2;

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ====== LOGIKA SENSOR PARKIR ======

  // 1. Jika jarak >= 30 cm → bunyi putus-putus medium
  if (distance >= 50) {
    tone(buzzerPin, 1000);   // frekuensi medium
    delay(500);
    noTone(buzzerPin);
    delay(300);
  }

  // 2. Jika jarak >= 20 cm dan < 30 cm → bunyi terus medium
  else if (distance >= 25 && distance < 50) {
    tone(buzzerPin, 1000);   // frekuensi medium
    delay(200);
    noTone(buzzerPin);
    delay(200);
  }

  // 3. Jika jarak < 30 cm → bunyi terus high
  else if (distance < 25 && distance >= 10) {
    tone(buzzerPin, 1100);   // frekuensi lebih tinggi (lebih nyaring)
    delay(200);
    noTone(buzzerPin);
    delay(100);
  }

  // 4. Jika jarak < 10 cm → bunyi terus very high
  else if (distance < 10) {
    tone(buzzerPin, 2000);   // frekuensi lebih tinggi lagi (lebih nyaring)
    delay(100);
  }
}
