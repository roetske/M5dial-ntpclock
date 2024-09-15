const String cc[12]={"45","40","35","30","25","20","15","10","05","0","55","50"};
const String days[]={"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY","NANDAY"};
const String months[]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC","UND"};

bool getNTPtime_check() 
{   bool ok = false;  
    tm timeinfox;
    Serial.println("check ntp");
    if (WiFi.status() == WL_CONNECTED)
    { Serial.println(WiFi.localIP());
      //NTP short function but works
      configTzTime(TZ_INFO,NTP_SERVER,NTP_SERVER2,NTP_SERVER3);//esp32 only esp8266 withoutTz
      if (getLocalTime(&timeinfox))
           {  
             Serial.println(&timeinfox ,"%A, %B %d %Y %H:%M:%S zone %Z %z ");
             rtc.setTimeStruct(timeinfox);
             Serial.println("Update NTP clock succeeded");
             
          ok = true;
        }
     else
      {Serial.println("Error get ntp");}
      
    }  
    return ok;
}


bool getNTPtime() 
{   bool ok = false;  
    tm timeinfox;
    Serial.println("check ntp");
    if (check_Wifi())
    { //NTP short function but works
      configTzTime(TZ_INFO,NTP_SERVER,NTP_SERVER2,NTP_SERVER3);//esp32 only esp8266 withoutTz
      if (getLocalTime(&timeinfox))
        { Serial.println(&timeinfox ,"%A, %B %d %Y %H:%M:%S zone %Z %z ");
          rtc.setTimeStruct(timeinfox);
          Serial.println("update NTP clock succeeded");
          ok = true;
        }
     else
      {Serial.println("error getlocaltime");}
      
    }  
    stop_Wifi();
    
    return ok;
}
void checkNTPupdate()
{
  if ((lastupdate + updateinterval) < rtc.getMinute())
   {lastupdate = rtc.getMinute();
    getNTPtime();
   }
  if (rtc.getMinute() == 0)
    {lastupdate = 0;}    
}
