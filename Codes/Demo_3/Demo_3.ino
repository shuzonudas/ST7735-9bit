// see user manual for pin connections

void setup() {
init_LCD();
rotate(2);

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

fillScreen();
delay(1000);

setCursor(1,1);
setTextSize(2);
println("drawPixel:");
setColor(0xFF,0x00,0x00);

for(int i =0 ;i<150;i++)
{
setColor(random(255),random(255),random(255));
drawPixel(random(160), random(160));
delay(100);
}

fillScreen();
delay(1000);

setCursor(1,1);
setTextSize(1);
println("drawRoundRect");
setColor(0xFF,0xFF,0x00);


for(int i =0 ;i<120;i+=6)
{
drawRoundRect(64-i/2,80-i/2,i,i,3);
delay(100);
}

fillScreen();
delay(1000);

setCursor(1,1);
setTextSize(2);
println("fillRoundRect");
setColor(0xFF,0x00,0xFF);

for (int16_t x=0; x <127; x+=12) {

  setColor(0x00,0x00,0xFF);
    drawRoundRect(64 -x/2, 80 -x/2 , x, x,3);

delay(200);
 setColor(random(255),random(255),random(255));

    fillRoundRect(64 -x/2, 80 -x/2 , x, x,3);
 
  }


fillScreen();
delay(1000);
rotate(3);
setColor(0xFF,0xFF,0xFF);
setCursor(10,30);
print("1.8 inch TFT    Display ");
setCursor(60,60);
//print("ENDs!");

}

void loop() {
}



