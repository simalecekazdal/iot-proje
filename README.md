# 🚗 Arduino ve ESP8266 ile Akıllı Araç Projesi / Smart Vehicle Project with Arduino & ESP8266

## 📌 Proje Hakkında / About the Project

Bu projede, çevresel verileri algılayan ve uzaktan kontrol edilebilen bir **akıllı araç** geliştirildi. Araç, **Wi-Fi üzerinden kontrol** edilebilmekte ve çeşitli sensörlerle **ortam bilgilerini algılayabilmektedir**. Veriler **ThingSpeak platformuna** aktarılır ve grafiksel olarak takip edilebilir.

In this project, a **smart vehicle** was developed that can be remotely controlled and sense environmental data. The vehicle operates via **Wi-Fi** and transmits environmental information to the **ThingSpeak platform** for real-time monitoring and visualization.

---

## 🚀 Özellikler / Features

### 🎮 Araç Kontrolü / Vehicle Control
- ESP8266 ile oluşturulan web sunucusu üzerinden kontrol.
- İleri, geri, sağa, sola, köşe dönüşü gibi yön hareketleri.
- Ayarlanabilir hız kontrolü (400-1023 PWM aralığında).

Controlled via a web server hosted on ESP8266.  
Supports directional commands such as forward, backward, left, right, and cornering.  
Adjustable speed (400 to 1023 PWM range).

### 🌡️ Çevresel Algılama / Environmental Sensing
- **Ultrasonik Sensör (HC-SR04):** Engel mesafesi ölçümü. Çok yakında lazeri aktive eder.
- **Gaz Sensörü (MQ2):** Gaz algılandığında buzzer ile uyarı verir.
- **DHT11 Sensörü:** Sıcaklık ve nem ölçer; ThingSpeak’e gönderilir.

- **Ultrasonic Sensor (HC-SR04):** Measures obstacle distance; activates laser if too close.
- **Gas Sensor (MQ2):** Triggers buzzer alert if gas is detected.
- **DHT11 Sensor:** Measures temperature and humidity and sends data to ThingSpeak.

### ☁️ Bulut Entegrasyonu / Cloud Integration
- DHT11 verileri ThingSpeak’e gönderilir.
- ThingSpeak üzerinden sıcaklık ve nem değerleri grafiksel olarak takip edilir.

Data from DHT11 is sent to ThingSpeak for visualization.  
Users can monitor temperature and humidity values as real-time graphs.

---

## 🔧 Kullanılan Donanım / Hardware Used

| Donanım / Hardware | Açıklama / Description |
|--------------------|------------------------|
| Arduino Uno / Mega | Ana kontrol birimi / Main controller |
| ESP8266            | Wi-Fi bağlantısı ve web sunucusu / Wi-Fi & web server |
| HC-SR04            | Mesafe sensörü / Distance sensor |
| MQ2                | Gaz sensörü / Gas sensor |
| DHT11              | Sıcaklık & nem sensörü / Temperature & humidity sensor |
| L298N              | Motor sürücü / Motor driver |
| DC Motorlar        | Araç hareketi için / For movement |
| Buzzer             | Gaz uyarısı / Gas alert |
| Lazer Modülü       | Mesafe uyarısı / Distance alert |

---

## 🧠 Yazılım Detayları / Software Details

### 📚 Kullanılan Kütüphaneler / Libraries Used
- `ESP8266WiFi.h` — Wi-Fi bağlantısı
- `ThingSpeak.h` — Bulut veri iletimi
- `DHT.h` — Sıcaklık & nem sensörü verileri

### 🔁 Temel Fonksiyonlar / Core Functions
```cpp
goAhead();     // İleri / Move forward
goBack();      // Geri / Move backward
goRight();     // Sağa / Turn right
goLeft();      // Sola / Turn left
stopRobot();   // Durdur / Stop
