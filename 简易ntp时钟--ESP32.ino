
#include <WiFi.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <U8g2lib.h>
#include <Wire.h>

int8_t timeZone = 8;
const PROGMEM char *ntpServer = "ntp1.aliyun.com"; //ntp服务器
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE); 

void page1() {
  u8g2.setFont(u8g2_font_wqy13_t_gb2312);
  u8g2.setFontPosTop();
  u8g2.setCursor(20,5);
  u8g2.print(String(NTP.getDateYear()) + String("年") + String(NTP.getDateMonth()) + String("月") + String(NTP.getDateDay()) + String("日"));
}

void page2() {
  u8g2.setFont(u8g2_font_wqy16_t_gb2312);
  u8g2.setFontPosTop();
  u8g2.setCursor(((NTP.getTimeHour24() > 9)?25:30),28);
  u8g2.print(String(NTP.getTimeHour24()) + String("：") + String(NTP.getTimeMinute()) + String("：") + String(NTP.getTimeSecond()));
}

void page3() {
  u8g2.setFont(u8g2_font_wqy16_t_gb2312);
  u8g2.setFontPosTop();
  u8g2.setCursor(10,51);
  u8g2.print("きみの爱马が！");//屏幕下方内容
}

void setup(){
  WiFi.begin("123", "12345678");//wifi名和密码
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Local IP:");
  Serial.print(WiFi.localIP());

  NTP.setInterval (600);
  NTP.setNTPTimeout (1500);
  NTP.begin (ntpServer, timeZone, false);
  u8g2.setI2CAddress(0x3C*2);
  u8g2.begin();
  // SCL:22
  // SDA:21
  u8g2.enableUTF8Print();

}

void loop(){
  while (true) {
    delay(1000);
    u8g2.firstPage();
    do
    {
      page1();
      page2();
      page3();
    }while(u8g2.nextPage());
  }

}