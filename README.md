# M5dial-ntpclock
Clock with m5dial rtc and ntp update.<br />
When i started i could not compile it. <br />
Turned out when compiling with arduino ide. The partition scheme was nok.<br />
Started from example from Volos Projects. Except for graphics made a lot of changes. 
Especially use of rtc and ntp. I also like to work with a compact main module 
and then with sub inos to make it more structured to my personal liking.
I tried to use autoconnect for interactive settings of wifi but it did not compile.
Autoconnect works not v3 lib for esp32.

# Credits
Based on project i found on youtube Volos Projects :https://www.youtube.com/watch?v=hxD3pI0II-E&t=120s.<br />
Graphics are awesome.<br />
Building partition scheme esp32 great tool to make partition for esp32.<br />
When finished just add partitions.csv to your folder where sketch is.<br />
In arduino ide 2.3.2 you have the option for custom partion. Set that and it will compile with this file./<br />
https://thelastoutpostworkshop.github.io/microcontroller_devkit/esp32partitionbuilder/<br />
# M5dial
Great gadget esp32 s3 8mB flash. The main advantage you have a compact interface module /<br />
with touchscreen, rotary knob, pushbutton and 2 ports to the outside./<br />
What makes it good for projects is that it is all in one especially for userinteraction./<br />
Everybody knows how much work it is to integrate display and buttons to a project and make it look good./<br />
M5dial resolves this for you 45mm circle hole to drill into you project box and you have a/<br />
ready to use interface for your hardware./<br />
A hard thing is the use and programming of the touchscreen. I miss a tool to design screens. 
