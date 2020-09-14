#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

#include "ArduinoJson.h"
#include "UniversalTelegramBot.h"
#include "LiquidCrystal_I2C.h"
#include "Turbidity.h"
#include "Ph.h"

// Pengaturan pin sensor
#define PH_PIN 36
#define TURBIDITY_PIN 37

// Pengaturan token telegram
#define BOT_TOKEN "1279057851:AAEqZg-zyzETzE3GSD3Se07WB554-28gWp8"
// #define CHAT_ID "407689155"

// Pengaturan koneksi WiFi
const char *SSID = "vivo y50";
const char *PASSWORD = "ad2042cc";

// Pengaturan waktu tunggu
unsigned long prevTime = 0;

// Pengaturan class library yang dipakai
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Ph pH(PH_PIN);
Turbidity turbidity(TURBIDITY_PIN);

void handleNewMessages(int);

/*
 * Mengatur segala perintah yang diterima dari telegram
 * @params: message -> pesan masukan dari telegram
 */
void handleNewMessages(int message)
{
  for (int i = 0; i < message; i++)
  {
    String chat_id = String(bot.messages[i].chat_id);
    // if (chat_id != CHAT_ID)
    // {
    //   bot.sendMessage(chat_id, "Unauthorized user", "");
    //   continue;
    // }

    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;

    // Menjalankan perintah dibawah jika menerima pesan "/start" dari telegram
    if (text == "/start")
    {
      String welcome = "Selamat datang, " + from_name + ".\n";
      welcome += "Gunakan perintah perintah dibawah.\n\n";
      welcome += "/baca untuk membaca nilai sensor \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    // Menjalankan perintah dibawah jika menerima pesan "/baca" dari telegram
    if (text == "/baca")
    {
      String message = "pH: " + String(pH.getValue()) + "\n";
      message += "ppm: " + String(turbidity.getValue()) + "\n";
      bot.sendMessage(chat_id, message, "");
    }
  }
}

/*
 * Fungsi awal sebagai konfigurasi ESP32
 */
void setup()
{
  lcd.init();
  lcd.backlight();
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  // ESP32 menunggu terkoneksi dengan WiFi
  while (WiFi.status() != WL_CONNECTED)
  {
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");
  }
}

void loop()
{
  // Perintah dibawah akan dijalankan dengan rentang waktu 1000 ms (1 detik)
  if (millis() - prevTime > 1000)
  {
    // Menampilkan nilai sensor dalam LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("pH: " + String(pH.getValue()));
    lcd.setCursor(0, 1);
    lcd.print("ppm: " + String(turbidity.getValue()));
    // lcd.print("ppm: " + String(analogRead(TURBIDITY_PIN) / 4096.0 * 3.3));

    // Menerima dan membaca pesan dari telegram
    int newMessage = bot.getUpdates(bot.last_message_received + 1);

    while (newMessage)
    {
      handleNewMessages(newMessage);
      newMessage = bot.getUpdates(bot.last_message_received + 1);
    }
    prevTime = millis();
  }
}