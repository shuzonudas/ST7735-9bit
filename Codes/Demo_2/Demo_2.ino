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

setCursor(1,1);
setTextSize(2);
println("lines:");

for(int i =0 ;i<27;i++)
{
drawLine(0,16,i*5,128);
delay(100);
}

for(int i =0 ;i<27;i++)
{
drawLine(128,16,i*5,128);
delay(100);
}


fillScreen();
delay(1000);

setCursor(1,1);
setTextSize(2);
println("circle:r+1");
setColor(0x00,0xFF,0xFF);

for(int i =0 ;i<40;i++)
{
drawCircle(64,72,i);
delay(100);
}


fillScreen();
delay(1000);

setCursor(1,1);
setTextSize(2);
println("circle:r+3");
setColor(0x00,0xFF,0x00);

for(int i =0 ;i<15;i++)
{
drawCircle(64,72,i*3);
delay(100);
}


fillScreen();
delay(1000);

setCursor(1,1);
setTextSize(1);
println("fill circle:");
setColor(0xFF,0x00,0x00);

for(int i =0 ;i<150;i++)
{
setColor(random(255),random(255),random(255));
fillCircle(random(10,160),random(128),random(10));
delay(100);
}

fillScreen();
delay(1000);

setCursor(1,1);
setTextSize(1);
println("rectangle");
setColor(0xFF,0xFF,0x00);


for(int i =0 ;i<120;i+=6)
{
drawRect(64-i/2,80-i/2,i,i);
delay(100);
}

fillScreen();
delay(1000);

setCursor(1,1);
setTextSize(2);
println("fillRect");
setColor(0xFF,0x00,0xFF);

for (int16_t x=0; x <127; x+=12) {

  setColor(0x00,0x00,0xFF);
    drawRect(64 -x/2, 80 -x/2 , x, x);

delay(200);
 setColor(random(255),random(255),random(255));

    fillRect(64 -x/2, 80 -x/2 , x, x);
 
  }


fillScreen();
delay(1000);
rotate(3);
setColor(0xFF,0x00,0x00);
setCursor(10,30);
print(" animation");
setCursor(60,60);
print("ENDs!");

}

void loop() {
}



