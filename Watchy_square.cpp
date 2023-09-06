#include "Watchy_square.h"

#define DARKMODE false

const uint8_t WIDTH = 66;
const uint8_t HEIGHT = 20;
const uint8_t MINW = 10;
const uint8_t MINH = 10;
int8_t batLev;
int Minx[59] = { 100,109,118,127,136,145,154,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,154, 145, 136, 127, 118, 109, 100, 91, 82, 73, 64, 55, 46, 37, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 40, 50, 60, 70, 80, 90 };
int Miny[59] = { 30, 30, 30, 30, 30, 30, 30, 30, 39, 48, 57, 66, 73, 82, 90,100,109,118,127,136,145,154, 160,160, 160, 160, 160, 160, 160, 160,160,160,160,160,160,160,160,160,154, 145,136,127,118,109,100, 91, 82,73, 64, 55, 46, 37, 30, 30, 30, 30, 30, 30, 30};

void Watchysquare::drawWatchFace(){
    display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    drawTime();
    drawDate();
    drawBattery();
    
}
void Watchysquare::drawTime(){
  
    // reset step counter at midnight
    if (currentTime.Hour == 00 && currentTime.Minute == 00){
      sensor.resetStepCounter();
              //turn off radios
      WiFi.mode(WIFI_OFF);
      btStop();
    }
	// time adjustment of 15,5 seconds each day (Watchy runs too fast)

    if (currentTime.Hour == 00 && currentTime.Minute == 30){
        
        RTC.read(currentTime);
        int8_t sekunde = currentTime.Second;
        int8_t minute = currentTime.Minute;
        int8_t hour = currentTime.Hour;
        int8_t day = currentTime.Day;
        int8_t month = currentTime.Month;
        int8_t year = tmYearToY2k(currentTime.Year);

        delay(15500);

        tmElements_t tm;
        tm.Month = month;
        tm.Day = day;
        tm.Year = y2kYearToTm(year);
        tm.Hour = hour;
        tm.Minute = minute ;
        tm.Second = sekunde;

        RTC.set(tm);
        
         }
	// end of time adjustment, if you don't like a time adjustment, just delete above lines

    int8_t Stunde = currentTime.Hour;
    int8_t Minute = currentTime.Minute;

    if (Stunde >= 1 && Stunde<13) {
        display.fillRect(100 , 0, WIDTH, HEIGHT, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    if (Stunde >= 2 && Stunde<14) {
        display.fillRect(166, 0,  WIDTH/2, HEIGHT, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        display.fillRect(180, 0, HEIGHT-1, WIDTH/2, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    if (Stunde >= 3 && Stunde < 15) {
        display.fillRect(180, 33, HEIGHT-1, WIDTH, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    if (Stunde >= 4 && Stunde < 16) {
        display.fillRect(180, 99, HEIGHT-1, WIDTH+1, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    if (Stunde >= 5 && Stunde < 17) {
        display.fillRect(180, 166, HEIGHT-1, WIDTH/2, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        display.fillRect(166, 180, WIDTH / 2, HEIGHT-1, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    if (Stunde >= 6 && Stunde < 18) {
        display.fillRect(100, 180, WIDTH, HEIGHT-1, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    if (Stunde >= 7 && Stunde < 19) {
        display.fillRect(34, 180, WIDTH, HEIGHT-1, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    if (Stunde >= 8 && Stunde < 20) {
        display.fillRect(0, 180,  WIDTH/2+1, HEIGHT-1, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        display.fillRect(0, 166,  HEIGHT, WIDTH / 2, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    if (Stunde >= 9 && Stunde < 21) {
        display.fillRect(0, 100, HEIGHT, WIDTH, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    if (Stunde >= 10 && Stunde < 22) {
        display.fillRect(0, 34, HEIGHT, WIDTH, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    if (Stunde >= 11 && Stunde < 23) {
        display.fillRect(0, 0, HEIGHT, WIDTH/2+1, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        display.fillRect(0, 0, WIDTH / 2 +1, HEIGHT, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    if (Stunde >= 12 ) {
        display.fillRect(34, 0, WIDTH, HEIGHT, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    for (int n = 1; n <= Minute; n++) {

        display.fillRect(Minx[n-1], Miny[n-1], MINW, MINH, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }


}
void Watchysquare::drawBattery() {
    float VBAT = getBatteryVoltage();

   batLev = 100 - ((4.15 - VBAT)*100);

   
    if (batLev >= 10) {
        display.fillRect(100, 50, 50, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    if (batLev >= 25) {
        display.fillRect(145, 50, 5, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    if (batLev > 38) {
        display.fillRect(145, 50, 5, 95, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    if (batLev >= 50) {
        display.fillRect(100, 145, 50, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }    
    
    if (batLev > 62) {
        display.fillRect(50, 145, 100, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    if (batLev >= 75) {
        display.fillRect(50, 100, 5, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    if (batLev > 86) {
        display.fillRect(50, 50, 5, 100, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    if (batLev > 97) {
        display.fillRect(50, 50, 50, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }   
}

void Watchysquare::drawDate() {
        display.setFont(&MONOFONT20pt7b);
        display.setCursor(75, 80);
        String WTag = dayShortStr(currentTime.Wday);
        display.println(WTag);

        display.setCursor(85, 108);
        if (currentTime.Day < 10) {
            display.print("0");
        }
        display.println(currentTime.Day);

        String Monat = monthShortStr(currentTime.Month);
        display.setCursor(75, 135);
        display.println(Monat);

               
    }

