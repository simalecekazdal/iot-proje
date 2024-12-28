# Arduino ve ESP8266 Kullanarak Akıllı Araç Projesi

Bu projede, bir Arduino tabanlı akıllı araç geliştirdim. Araç, bir ESP8266 modülü ile WiFi üzerinden kontrol edilebiliyor, ultrasonik sensör, gaz sensörü ve DHT11 ile çevresel bilgileri algılayabiliyor. Ayrıca ThingSpeak ile sıcaklık ve nem verilerini buluta gönderip görüntüleyebiliyoruz.

## Projenin Özellikleri

### 1. **Araç Kontrolü**
- Araç, ESP8266 üzerinden bir web sunucusu kurularak kontrol ediliyor.
- İleri, geri, sağa, sola, köşe dönüşleri gibi komutlarla hareket edebiliyor.
- Hız seviyeleri ayarlanabilir (400 ile 1023 arasında).

### 2. **Çevresel Algılama**
- **Ultrasonik Sensör:** Araç önündeki mesafeyi ölçmek için kullanılır. Çok yakına gelindiğinde lazeri aktive eder.
- **Gaz Sensörü:** Ortamda gaz sızıntısı algılanırsa buzzer çalar ve uyarı verir.
- **DHT11 Sensörü:** Sıcaklık ve nem değerlerini ölçer ve ThingSpeak platformuna gönderir.

### 3. **Bulut Entegrasyonu**
- Sıcaklık ve nem verileri ThingSpeak platformuna gönderilir ve oradan okunabilir.
- ThingSpeak, sıcaklık ve nem için ayrı ayrı alanlar kullanır.

## Kullanılan Donanımlar

- **Arduino (UNO veya Mega):** Ana kontrol birimi.
- **ESP8266 WiFi Modülü:** Kablosuz bağlantı ve web sunucusu için.
- **Ultrasonik Sensör (HC-SR04):** Mesafe ölçümü.
- **Gaz Sensörü (MQ2):** Gaz algılama.
- **DHT11:** Sıcaklık ve nem ölçümü.
- **L298N Motor Sürücü Modülü:** Motorların kontrolü.
- **DC Motorlar:** Araç hareketi için.
- **Buzzer:** Gaz algılama uyarısı.
- **Lazer Modülü:** Mesafe uyarısı.

## Yazılım Özellikleri

### Kullanılan Kütüphaneler

- **ESP8266WiFi.h:** ESP8266 modülü için WiFi bağlantısı.
- **ThingSpeak.h:** ThingSpeak platformuna veri göndermek için.
- **DHT.h:** DHT11 sensöründen veri almak için.

### Ana İşlevler

1. **Araç Hareketi:**
   - `goAhead()`: İleri git.
   - `goBack()`: Geri git.
   - `goRight()`: Sağa dön.
   - `goLeft()`: Sola dön.
   - `stopRobot()`: Araç durdur.

2. **Sensör Okumaları:**
   - Mesafe ölçümü (HC-SR04): Araç önündeki mesafeyi kontrol eder.
   - Gaz algılama (MQ2): Ortamda gaz sızıntısı olup olmadığını kontrol eder.
   - Sıcaklık ve nem ölçümü (DHT11): Ortam sıcaklığı ve nemi ölçülür.

3. **ThingSpeak Entegrasyonu:**
   - Sıcaklık ve nem verileri ThingSpeak platformuna gönderilir.
   - ThingSpeak'ten mevcut veriler okunur ve seri monitöre yazdırılır.

## Ekran Çıktıları

- Seri monitörde mesafe, gaz sensörü verileri, sıcaklık ve nem bilgilerini görüntüleyebilirsiniz.
- ThingSpeak'te sıcaklık ve nem değerlerini grafik olarak takip edebilirsiniz.

---

