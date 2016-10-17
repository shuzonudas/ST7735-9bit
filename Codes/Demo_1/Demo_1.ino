// see user manual for pin connections
void setup() {
init_LCD();

setBackColor(0xFF,0x00,0x00);
fillScreen();
delay(1000);

setBackColor(0x00,0xFF,0x00);
fillScreen();
delay(1000);

setBackColor(0x00,0x00,0xFF);
fillScreen();
delay(1000);

setBackColor(0x00,0x00,0x00);
fillScreen();
delay(1000);

setColor(0xFF,0xFF,0xFF);


rotate(0);
setBackColor(0xFF,0x00,0x00);
fillScreen();
setCursor(30,50);
setTextSize(2);
println("1.8 inch TFT Display");
delay(3000);

rotate(1);
setBackColor(0x00,0xFF,0x00);
fillScreen();
setCursor(30,50);
setTextSize(2);
println("1.8 inch TFT Display");
delay(3000);

rotate(2);
setBackColor(0x00,0x00,0xFF);
fillScreen();
setCursor(30,50);
setTextSize(2);
println("1.8 inch TFT Display");
delay(3000);

rotate(3);
setBackColor(0x00,0x00,0x00);
fillScreen();
setCursor(30,50);
setTextSize(2);
println("1.8 inch TFT Display");
delay(3000);

setTextSize(1);
setCursor(1,1);
println("font size 1");
delay(1000);

setTextSize(3);
println("font size 3");
delay(1000);


setBackColor(0x00,0x00,0x00);
fillScreen();
delay(1000);


setTextSize(1);
setCursor(1,2);
println("this is a text");
println("");

char buffer[100];
sprintf(buffer,"to use formatted text use  sprintf function");
println(buffer);
println("");
delay(1000);

println("starting counter:");
delay(1000);

setTextSize(2);
for(int i =0 ;i<1000;i++)
{
setCursor(35,60);
sprintf(buffer,"%.4d",i);
print(buffer);
delay(100);
}
}


void loop() {
}



