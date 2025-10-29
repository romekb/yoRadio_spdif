#include "options.h"
#include "rtcsupport.h"

#if RTCSUPPORTED
#include <Wire.h>

TwoWire RTCWire = TwoWire(1);			// I2C interface 1 is used to avoid conflict with I2C Display or I2C Touchscreen
  
RTC rtc;

bool RTC::init(){
	RTCWire.begin(RTC_SDA, RTC_SCL);
	return begin(&RTCWire);
}

bool RTC::isRunning(){
#if RTC_MODULE==DS3231
	return !lostPower();
#elif RTC_MODULE==DS1307
	return isrunning();
#endif
}

bool RTC::getTime(struct tm* tinfo){
	if(isRunning()){
		DateTime nowTm = rtc.now();
		if(nowTm.second()>59 || nowTm.minute()>59 || nowTm.hour()>23 || nowTm.day()==0 || 
			 nowTm.day()>31 || nowTm.month()==0 || nowTm.month()>12) return false;
		tinfo->tm_sec  = nowTm.second();
		tinfo->tm_min  = nowTm.minute();
		tinfo->tm_hour = nowTm.hour();
		tinfo->tm_wday = nowTm.dayOfTheWeek();
		tinfo->tm_mday = nowTm.day();
		tinfo->tm_mon  = nowTm.month() - 1;
		tinfo->tm_year = nowTm.year() - 1900;
		return true;
	}
	return false;
}

void RTC::setTime(struct tm* tinfo){
	adjust(DateTime(tinfo->tm_year + 1900, tinfo->tm_mon + 1, tinfo->tm_mday, tinfo->tm_hour, tinfo->tm_min, tinfo->tm_sec));
}

#endif
