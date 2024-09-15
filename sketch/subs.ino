void init_M5dial()
{
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, true);
  
  sprite.createSprite(240,240); 
  sprite.setSwapBytes(true);    
  sprite.setSwapBytes(true);
  sprite.setTextDatum(4);

  int b=0;
  int b2=0;

  for(int i=0;i<360;i++)
    {
       x[i]=((r-20)*cos(rad*i))+sx;
       y[i]=((r-20)*sin(rad*i))+sy;
       px[i]=(r*cos(rad*i))+sx;
       py[i]=(r*sin(rad*i))+sy;

       lx[i]=((r-6)*cos(rad*i))+sx;
       ly[i]=((r-6)*sin(rad*i))+sy;
       
       if(i%30==0){
       start[b]=i;
       b++;
       }

       if(i%6==0){
       startP[b2]=i;
       b2++;
       }
      }

    int co=210;
     for(int i=0;i<12;i++)
     { grays[i]=tft.color565(co, co, co);
       co=co-20;
     }

}

void showlocaltime() 
{

  rAngle=rAngle-3;
  angle=rtc.getSecond()*6; 
  
  if(rtc.getSecond()<10) s="0"+String(rtc.getSecond()); else s=String(rtc.getSecond());
  if(rtc.getMinute()<10) m="0"+String(rtc.getMinute()); else m=String(rtc.getMinute());
  if(rtc.getHour(true) <10) h="0"+String(rtc.getHour(true) ); else h=String(rtc.getHour(true) );
  d1=String(rtc.getDay() /10);d2=String(rtc.getDay()%10);
  m1=String((rtc.getMonth()+1)/10);m2=String((rtc.getMonth()+1)%10);
  if(angle>=360)
    angle=0;

   if(rAngle<=0)
    {rAngle=359;}

  if(dir==0)
  circle=circle+0.5;
  else
  circle=circle-0.5;
  
  if(circle>140)
  dir=!dir;

  if(circle<100)
  dir=!dir;

  if(angle>-1)
  {
     lastAngle=angle;      

     VALUE=((angle-270)/3.60)*-1;
     if(VALUE<0)
     VALUE=VALUE+100;
 
     
  sprite.fillSprite(TFT_BLACK);
  sprite.setTextColor(TFT_WHITE,color5);
 
  sprite.loadFont(secFont);
  sprite.setTextColor(grays[1],TFT_BLACK);
  sprite.drawString(s,sx,sy-42);
  sprite.unloadFont();

  sprite.loadFont(smallFont);

  sprite.fillRect(64,82,16,28,grays[8]);
  sprite.fillRect(84,82,16,28,grays[8]);
  sprite.fillRect(144,82,16,28,grays[8]);
  sprite.fillRect(164,82,16,28,grays[8]);

  sprite.setTextColor(0x35D7,TFT_BLACK);
  sprite.drawString(days[rtc.getDayofWeek()].substring(0,3),160,72);
  sprite.setTextColor(0x35D700,TFT_BLACK);
  sprite.drawString(months[rtc.getMonth()],80,72);
  sprite.unloadFont();
  sprite.loadFont(middleFont);
  sprite.setTextColor(grays[2],grays[8]);
  sprite.drawString(m1,71,99,2);
  sprite.drawString(m2,91,99,2);
  sprite.drawString(d1,150,99,2);
  sprite.drawString(d2,170,99,2);
  sprite.unloadFont();

  sprite.loadFont(bigFont);
  sprite.setTextColor(grays[0],TFT_BLACK);
  sprite.drawString(h+":"+m,sx,sy+32);
  sprite.unloadFont();

  sprite.setTextColor(grays[3],TFT_BLACK);

  for(int i=0;i<60;i++)
  if(startP[i]+angle<360)
    sprite.fillSmoothCircle(px[startP[i]+angle],py[startP[i]+angle],1,grays[4],TFT_BLACK);
  else
    sprite.fillSmoothCircle(px[(startP[i]+angle)-360],py[(startP[i]+angle)-360],1,grays[4],TFT_BLACK);

  for(int i=0;i<12;i++)
    if(start[i]+angle<360){
      sprite.drawString(cc[i],x[start[i]+angle],y[start[i]+angle]);
      sprite.drawWedgeLine(px[start[i]+angle],py[start[i]+angle],lx[start[i]+angle],ly[start[i]+angle],2,2,grays[3],TFT_BLACK);
    } else {
      sprite.drawString(cc[i],x[(start[i]+angle)-360],y[(start[i]+angle)-360]);
      sprite.drawWedgeLine(px[(start[i]+angle)-360],py[(start[i]+angle)-360],lx[(start[i]+angle)-360],ly[(start[i]+angle)-360],2,2,grays[3],TFT_BLACK);
    }
   sprite.drawWedgeLine(sx-1,sy-82,sx-1,sy-70,1,5,0xA380,TFT_BLACK);
   sprite.fillSmoothCircle(px[rAngle],py[rAngle],4,TFT_RED,TFT_BLACK);
   sprite.unloadFont();
  }
}