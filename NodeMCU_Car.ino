#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h" // DHT11 Sensör için kütüphane
#define WLAN_SSID  "Okan"     
#define WLAN_PASSWORD  "okan12345"
unsigned long channelID = 2795688;             // ThingSpeak kanal ID
const char* writeAPIKey = "CW4RIARGZQ9W48OI";  // ThingSpeak yazma API anahtarı
const char* serverTS = "api.thingspeak.com";   // ThingSpeak yazma API anahtarı
#define DHTPIN D1   // DHT11 Sensörünün bağlı olduğu pin (D1 örnektir, kendi pininizi yazın)
#define DHTTYPE DHT11  // Sensör tipi (DHT11 için sabit)
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
void wifiSetup() {
  Serial.println("\nWiFi Bağlantısı Başlatılıyor...");
  WiFi.begin(WLAN_SSID, WLAN_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); }
  Serial.println("\nWiFi Bağlantısı Sağlandı!");
  Serial.print("IP Adresi: ");
  Serial.println(WiFi.localIP());}
void setup() {
  Serial.begin(9600);              // Seri Haberleşme başlatılıyor
  wifiSetup();                     // WiFi kurulum fonksiyonu
  ThingSpeak.begin(client);        // ThingSpeak başlatılıyor
  dht.begin();                     // DHT Sensörü başlatılıyor
  Serial.println("Kurulum Tamamlandı.");}
#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)
#include <ESP8266WebServer.h>
String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "NodeMCU Car";
ESP8266WebServer serverMotor(80);
void setupMotorServer() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);  
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT); 
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP); 
  serverMotor.on ( "/", HTTP_handleMotorRoot );
  serverMotor.onNotFound ( HTTP_handleMotorRoot );
  serverMotor.begin();    }
void goAhead(){ 
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);}
void goBack(){ 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);}
void goRight(){ 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);}
void goLeft(){
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);}
void stopRobot(){  
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);}
void loop() {
  serverMotor.handleClient(); // Motor serverini dinleyin
  sicaklikVeNem();   
  delay(2000);      // 2 saniye bekle (ThingSpeak limiti için)}
void sicaklikVeNem() {
  float sicaklik = dht.readTemperature(); // Santigrat sıcaklık okuma
  float nem = dht.readHumidity();         // Nem okuma
  if (isnan(sicaklik) || isnan(nem)) { // Sensörden değer okunamıyorsa hata mesajı
    Serial.println("DHT11'dan değer okunamadı! Lütfen bağlantıyı kontrol edin.");
    return;}
  Serial.print("Hesaplanan Sıcaklık: ");
  Serial.print(sicaklik);
  Serial.println(" °C");
  Serial.print("Hesaplanan Nem: ");
  Serial.print(nem);
  Serial.println(" %");
  Serial.println("ThingSpeak'e sıcaklık ve nem değerleri gönderiliyor...");
  int sicaklikDurum = ThingSpeak.writeField(channelID, 1, sicaklik, writeAPIKey); // 1. field'a sıcaklık
  int nemDurum = ThingSpeak.writeField(channelID, 2, nem, writeAPIKey);           // 2. field'a nem
  if (sicaklikDurum == 200 && nemDurum == 200) {
    Serial.println("Veriler başarıyla gönderildi!");
  } else {
    Serial.print("Veri gönderme başarısız! Sıcaklık Hata Kodu: ");
    Serial.println(sicaklikDurum);
    Serial.print("Nem Hata Kodu: ");
    Serial.println(nemDurum);}
  float okunanSicaklik = ThingSpeak.readFloatField(channelID, 1); // 1. field'dan sıcaklık
  float okunanNem = ThingSpeak.readFloatField(channelID, 2);      // 2. field'dan nem
  Serial.print("ThingSpeak'ten Okunan Sıcaklık: ");
  Serial.println(okunanSicaklik);
  Serial.print("ThingSpeak'ten Okunan Nem: ");
  Serial.println(okunanNem);}
void HTTP_handleMotorRoot(void) {
  if (serverMotor.hasArg("State")) {
    Serial.println(serverMotor.arg("State")); }
  serverMotor.send(200, "text/html", "");
  delay(1);}
