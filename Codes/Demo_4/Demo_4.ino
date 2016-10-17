// see user manual for pin connections

void setup() {
init_LCD();
rotate(2);

setBackColor(0x00,0x00,0x00);
fillScreen();
delay(1000);

/*setCursor(1,1);
setTextSize(2);
setColor(0xFF,0xFF,0xFF);
println("drawPixel:");
drawPixel(50, 50);
*/
/*
setCursor(1,1);
setTextSize(2);
setColor(0xFF,0xFF,0xFF);
println("drawRoundRect:");
drawRoundRect(30,50,60,80,9);
*/
/*
setCursor(1,1);
setTextSize(2);
setColor(0xFF,0xFF,0xFF);
println("fillRoundRect:");
fillRoundRect(30,50,60,80,9);
*/

/*setCursor(1,1);
setTextSize(2);
setColor(0xFF,0xFF,0xFF);

setCursor(20,40);
println("println");

setCursor(30,70);
print("print");
*/

setCursor(1,1);
setTextSize(2);
setColor(0xFF,0xFF,0xFF);
println("fillRoundRect:");
fillRoundRect(30,50,60,80,9);

}

void loop() {
}



