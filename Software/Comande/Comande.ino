#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define up A3
#define ok A4
#define down A5
#define led_y 11
#define led_r 17

int comanda[50];
int count,showcount,val,upval,okval,downval;

#define OLED_RESET 4

Adafruit_SSD1306 oled(128,64,&Wire, OLED_RESET);

void setup() {
  
  delay(100);
  
  pinMode(led_r,OUTPUT);
  pinMode(led_y,OUTPUT);
  pinMode(up,INPUT);
  pinMode(ok,INPUT);
  pinMode(down,INPUT);
  
  Serial1.begin(115200);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Non c'e'");
  oled.setCursor(0,16);
  oled.print("nessuna");
  oled.setCursor(0,32);
  oled.print("comanda");
  oled.display();
  count = 0;
  showcount=0;
}

void loop() {
  
  if(Serial1.available()>0){
    val=Serial1.read()-48;
    if((val>0)&&(val<10)){
      comanda[count]=val;
      count++;
      blinkyell();
      }
    }

   upval=debounce(up);
   okval=debounce(ok);
   downval=debounce(down);

   if(upval==0&&showcount<(count-1)){showcount++;}
   else if(downval==0&&showcount>=1){showcount--;}
   else if(okval==0&&count>0){
    blinkred();
    for(int i=showcount;i<count;i++){
       comanda[i]=comanda[i+1];
       oled.clearDisplay();
       oled.setCursor(0,0);
       oled.setTextSize(2);
       oled.println("Comanda");
       oled.print("eliminata");
       oled.display();
       delay(1500);
    }
    count--;
    showcount--;
   }

   
   writedisplay();
}


void writedisplay(){
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.setTextSize(2);
  if(count==0){
    oled.println("Non c'e'");
    oled.setCursor(0,16);
    oled.println("nessuna");
    oled.setCursor(0,32);
    oled.println("comanda");
  }
  else{
  switch(comanda[showcount]){
    case 1:
    oled.print("Antipasto");
    oled.setCursor(80,50);
    oled.print(showcount+1);
    oled.print("/");
    oled.print(count);
    break;
    case 2:
    oled.print("Carbonara");
    oled.setCursor(80,50);
    oled.print(showcount+1);
    oled.print("/");
    oled.print(count);
    break;
    case 3:
    oled.print("Gricia");
    oled.setCursor(80,50);
    oled.print(showcount+1);
    oled.print("/");
    oled.print(count);
    break;
    case 4:
    oled.print("Arrosticini");
    oled.setCursor(80,50);
    oled.print(showcount+1);
    oled.print("/");
    oled.print(count);
    break;
    case 5:
    oled.print("Spuntature");
    oled.setCursor(80,50);
    oled.print(showcount+1);
    oled.print("/");
    oled.print(count);
    break;
    case 6:
    oled.print("Sorbetto");
    oled.setCursor(80,50);
    oled.print(showcount+1);
    oled.print("/");
    oled.print(count);
    break;
    case 7:
    oled.print("Tartufo");
    oled.setCursor(80,50);
    oled.print(showcount+1);
    oled.print("/");
    oled.print(count);
    break;
    case 8:
    oled.print("Caffe'");
    oled.setCursor(80,50);
    oled.print(showcount+1);
    oled.print("/");
    oled.print(count);
    break;
    case 9:
    oled.print("Amaro");
    oled.setCursor(80,50);
    oled.print(showcount+1);
    oled.print("/");
    oled.print(count);
    default:
    break;
  }
  }
  oled.display();
  }





void blinkred()
{
  digitalWrite(led_r,HIGH);
  delay(75);
  digitalWrite(led_r,LOW);
  delay(75);
  digitalWrite(led_r,HIGH);
  delay(75);
  digitalWrite(led_r,LOW);
  delay(75);
  digitalWrite(led_r,HIGH);
  delay(75);
  digitalWrite(led_r,LOW);
  delay(75);
  digitalWrite(led_r,HIGH);
  delay(75);
  digitalWrite(led_r,LOW);
  delay(75);
  digitalWrite(led_r,HIGH);
  delay(75);
  digitalWrite(led_r,LOW);
  return;
}

void blinkyell()
{
  digitalWrite(led_y,HIGH);
  delay(75);
  digitalWrite(led_y,LOW);
  delay(75);
  digitalWrite(led_y,HIGH);
  delay(75);
  digitalWrite(led_y,LOW);
  delay(75);
  digitalWrite(led_y,HIGH);
  delay(75);
  digitalWrite(led_y,LOW);
  delay(75);
  digitalWrite(led_y,HIGH);
  delay(75);
  digitalWrite(led_y,LOW);
  delay(75);
  digitalWrite(led_y,HIGH);
  delay(75);
  digitalWrite(led_y,LOW);
  return;
}

bool debounce(int pin){
  int stato,statoprec;
  statoprec=digitalRead(pin);

  for(int i=0;i<15;i++){
    delay(1);
    stato=digitalRead(pin);
    if(stato!=statoprec){
      i=0;
      statoprec=stato;}
    }
   while(stato==0){stato=digitalRead(pin);}
   return statoprec;
  }
