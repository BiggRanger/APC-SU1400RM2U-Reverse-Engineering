/*
LED Driver = A6276ELW

APC Display Panel Cable
Pin 1 = Latch Enable
Pin 2 = Off Button (returns to ground)
Pin 3 = On Button (returns to ground)
Pin 4 = Clock
Pin 5 = SDI
Pin 6 = +5V
Pin 7 = Ground
Pin 8 = NC

LED Index 0x0 = Load 1
LED Index 0x1 = Load 2
LED Index 0x2 = Load 3
LED Index 0x3 = Load 4
LED Index 0x4 = Load 5
LED Index 0x5 = Overload
LED Index 0x6 = Battery Drained
LED Index 0x7 = Input Undervoltage
LED Index 0x8 = Input Overvoltage
LED Index 0x9 = On Battery
LED Index 0xA = On AC
LED Index 0xB = Battery 1
LED Index 0xC = Battery 2
LED Index 0xD = Battery 3
LED Index 0xE = Battery 4
LED Index 0xF = Battery 5

set latch low
  clock high
  set bit
  clock low
  unset bit
set latch high
set latch low
*/

bool ledIndex[16];

#define btnON 2   // Pin D2 = On Button pullup
#define btnOFF 3  // Pin D3 = On Button pullup
#define LE 4      // Pin D4 = LE
#define CK 5      // Pin D5 = CK
#define SDI 6     // Pin D6 = SDI

void setup() 
{
  pinMode(LE,OUTPUT);
  pinMode(CK,OUTPUT);
  pinMode(SDI,OUTPUT);
  pinMode(btnON,INPUT_PULLUP);
  pinMode(btnOFF,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(btnON), btnON_Press, FALLING);
  attachInterrupt(digitalPinToInterrupt(btnOFF), btnOFF_Press, FALLING);
  
  Serial.begin(9600);
  Serial.println("Starting LED Driver");

  allLed(false);
}

void loop() 
{
  Serial.println("Increment 1 LED");
  for (byte j = 0; j < 16; j++)
  {
    ledOn(j);  
    delay(100);
  }

  Serial.println("Decrement 1 LED");
  for (byte j = 15; j > 0; j--)
  {
    ledOn(j);  
    delay(100);
  }

  Serial.println("Increment all LEDs on");
  for (byte j = 0; j < 16; j++)
  {
    ledIndex[j] = true;
    ledMatrix();  
    delay(100);
  }

  Serial.println("Increment all LEDs off");
  for (byte j = 0; j < 16; j++)
  {
    ledIndex[j] = false;
    ledMatrix();  
    delay(100);
  }
}

void ledMatrix()
{
   for (byte j=0; j < 16; j++)
   {
      digitalWrite(SDI,ledIndex[j]);
      digitalWrite(CK, HIGH);
      digitalWrite(CK, LOW);
   }
   digitalWrite(LE,HIGH);
   digitalWrite(LE,LOW);
}

void ledOn(byte LED)
{
   for (byte j=0; j < 16; j++)
   {
      if (j == LED)
        digitalWrite(SDI,HIGH);
      else
        digitalWrite(SDI,LOW);        
      digitalWrite(CK, HIGH);
      digitalWrite(CK, LOW);
   }
   digitalWrite(LE,HIGH);
   digitalWrite(LE,LOW);
}

void allLed(bool state)
{
   digitalWrite(SDI,state);
   for (byte j=0; j < 16; j++)
   {
      digitalWrite(CK, HIGH);
      digitalWrite(CK, LOW);
   }
   digitalWrite(LE,HIGH);
   digitalWrite(LE,LOW);
}

void btnON_Press()
{
  Serial.println("Button On Press");  
}

void btnOFF_Press()
{
  Serial.println("Button Off Press");  
}
