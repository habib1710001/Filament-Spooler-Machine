//LCD config
//Include the library code:
#include <LiquidCrystal.h>

#define STEPPER1EN    38
#define STEPPER1STEP  A0
#define STEPPER1DIR   A1

#define STEPPER2EN    A2
#define STEPPER2STEP  A6
#define STEPPER2DIR   A7

#define STEPPER3EN    A8
#define STEPPER3STEP  46
#define STEPPER3DIR   48

#define ENCODERSW     35     // Rotary encoder switch
#define ENCODERADT    33     // Rotary encoder Pin A/DT
#define ENCODERBCLK   31     // Rotary encoder Pin B/CLK

#define LCDRS 16
#define LCDEN 17
#define LCDD4 23
#define LCDD5 25
#define LCDD6 27
#define LCDD7 29
#define LCDROW    4
#define LCDCOLUMN 20

#define BUZZERPIN 37

LiquidCrystal lcd(LCDRS, LCDEN, LCDD4, LCDD5, LCDD6, LCDD7);

// Rotary Encoder Variables
uint8_t switchPin = 2;       // button pin
uint8_t switchState = HIGH; // button value
uint8_t pinAstateCurrent = LOW;                // Current state of Pin A
uint8_t pinAStateLast = pinAstateCurrent;      // Last read value of Pin A

//Menu and submenue variables
volatile uint8_t  subMenuSet;
volatile uint8_t  menuSet = 1;

volatile uint8_t  optmenu;
volatile uint8_t  submenu;
volatile uint8_t  menu;

uint8_t rightPosition;
uint8_t leftPosition

//For showing the menu properly:
uint8_t flag1 = 1 ;
uint8_t flag2 = 1 ;
uint8_t flag3 = 1 ;
uint8_t flag4 = 1;
uint8_t flag5 = 1;

uint32_t debouncing_time = 1000;//Debouncing Time in Milliseconds
volatile uint32_t last_micros;


//For counting the rotaion of rotary encoder:
volatile uint16_t count = 0;


//Vectors for musical note, arrow, speaker , battery level
uint8_t arrow[8] = {0x0, 0x04 ,0x06, 0x1f, 0x06, 0x04, 0x00, 0x00};

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    push();
    last_micros = micros();
  }
}

void push()
{
  count = 0; 
  subMenuSet = submenu;
  menuSet = menu;
  optMenuSet = optmanu;
}

void update() {
  // ROTATION DIRECTION
  pinAstateCurrent = digitalRead(ENCODERADT);    // Read the current state of Pin A
  
  // If there is a minimal movement of 1 step
  if ((pinAStateLast == LOW) && (pinAstateCurrent == HIGH)) 
  {
    if (digitalRead(ENCODERBCLK) == HIGH) 
     {
      count--;
     } 
    else 
      {
      count++;
     }  
  }
  pinAStateLast = pinAstateCurrent;        // Store the latest read value in the currect state variable
}



void setup() 
{
  Serial.begin (9600); // Initialise the serial monitor
  
  // initialize the LCD
  lcd.begin(LCDCOLUMN, LCDROW);
  
  // Turn on the blacklight and print a message.
  lcd.clear();
  lcd.print("Spooler Machine");
  delay(2000);
  lcd.clear();

  
  lcd.createChar(0, arrow);   //Create the arrow symbol
  lcd.home(); 

  lcd.setCursor(0, 0);
  lcd.print("Initializing..");
  delay(1000);
  lcd.clear();
  
  pinMode (ENCODERSW, INPUT_PULLUP);              // Enable the switchPin as input with a PULLUP resistor
  pinMode (ENCODERADT, INPUT);                    // Set PinA as input
  pinMode (ENCODERBCLK, INPUT);                   // Set PinB as input

  // Attach a CHANGE interrupt to PinB and exectute the update function when this change occurs.
  attachInterrupt(digitalPinToInterrupt(ENCODERBCLK), update, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(ENCODERSW), debounceInterrupt , FALLING);
  
  menuSet = 1; //default page selection initialization.
}

void loop() 
{ 
 //MAIN MENU
 
 if( menuSet == 1)
 {
  if( count >= 0 && count <= 2)
    { 
      if(flag1 == 1)
      {
        flag1 = 0;
        lcd.clear();
      }
      lcd.setCursor(0, 0);
      lcd.write(byte(0)); 
      lcd.setCursor(1,0);
      lcd.print("Info Screen");
      lcd.setCursor(1 ,1);
      lcd.print("Start Winding"); 
      lcd.setCursor(1,2);
      lcd.print("Speed");
      lcd.setCursor(1 ,3);
      lcd.print("Home Ferrari");
      flag2 = 1;
      flag3 = 1;
      flag4 = 1;
      submenu = 1;
      menu = 2;
    }
   else if(count >2 && count < 4)
    {
      if(flag2 == 1)
      {
        flag2 = 0;
        lcd.clear();
      }
      lcd.setCursor(1,0);
      lcd.print("Info Screen");
      lcd.setCursor(0, 1);
      lcd.write(byte(0)); 
      lcd.setCursor(1 ,1);
      lcd.print("Start Winding"); 
      lcd.setCursor(1,2);
      lcd.print("Speed");
      lcd.setCursor(1 ,3);
      lcd.print("Home Ferrari");
      flag1 = 1;
      flag3 = 1;
      flag4 = 1;
      submenu = 2;
      menu = 2;
    }
   else if(count >4 && count < 6)
   { 
     if(flag3 == 1)
     {
        flag3 = 0;
        lcd.clear();
     }
     lcd.setCursor(1,0);
     lcd.print("Info Screen");
     lcd.setCursor(1 ,1);
     lcd.print("Start Winding"); 
     lcd.setCursor(1,2);
     lcd.setCursor(0, 3);
     lcd.write(byte(0)); 
     lcd.print("Speed");
     lcd.setCursor(1 ,3);
     lcd.print("Home Ferrari");

     flag1 = 1;
     flag2 = 1;
     flag4 = 1;
     submenu = 3;
     menu = 2;
   }
   else if(count >4 && count < 6)
   { 
     if(flag4 == 1)
     {
        flag4 = 0;
        lcd.clear();
     }
     lcd.setCursor(1,0);
     lcd.print("Info Screen");
     lcd.setCursor(1 ,1);
     lcd.print("Start Winding"); 
     lcd.setCursor(1,2);
     lcd.setCursor(0, 3);
     lcd.write(byte(0)); 
     lcd.print("Speed");
     lcd.setCursor(1 ,3);
     lcd.print("Home Ferrari");

     flag1 = 1;
     flag2 = 1;
     flag3 = 1;
     submenu = 4;
     menu = 2;
   }
   
   flag5 = 1;
 }

  //SUB MENU
  if( menuSet == 2)
  {
    if( subMenuSet == 1)
     {
      if( flag5 == 1)
      {
       lcd.clear();
       flag5 = 0 ;
       menu = 1 ; 
      }
      lcd.setCursor(0, 0);
      lcd.print("Filament Spooler");
      lcd.setCursor(5, 1);
      lcd.print("Machine V1");

      flag2 = 1;
      flag3 = 1;
      flag4 = 1;
      optmenu = 0;
      menu = 1; 
     }
    if( subMenuSet == 2)
    { 
      if( flag4 == 1)
      {
       lcd.clear();
       flag4 = 0 ;
       menu = 3; 
      }
      lcd.setCursor(0, 0);
      lcd.print("Adjust Puller Speed?");
      
      lcd.setCursor(0, 1);
      lcd.print("Puller Speed");

      lcd.setCursor(14, 1);
      uint8_t value = map(count, 0, 200, 0, 100);//200 rpm max speed
      
      lcd.print(String(value) + "rpm");
      
      lcd.setCursor(0 ,3);
      lcd.print("Start Spolling?");

      flag2 = 1;
      flag3 = 1;
      flag5 = 1;
      optmenu = 2;
      menu = 3;
    }
    if( subMenuSet == 3)
    { 
     if( flag2 == 1)
     {
       lcd.clear();
       flag2 = 0 ;
       menu = 3; 
     }
     
      lcd.setCursor(0, 0);
      lcd.print("Speed: ");
      
      uint8_t value = map(count, 0, 200, 0, 100);//200 rpm max speed
      lcd.print(String(value) + "rpm");
      lcd.setCursor(0, 1);
      lcd.print("Set Speed?");

      flag3 = 1;
      flag5 = 1;
      flag4 = 1;
      optmenu = 0;
      menu = 3;
    }
    if( subMenuSet == 4)
    { 
     if( flag3 == 1)
     {
       lcd.clear();
       flag3 = 0 ;
       menu = 3; 
     }
      lcd.setCursor(0, 0);
      lcd.print("Setting Ferrari");
      
      lcd.setCursor(2, 1);
      lcd.print("on Home Position");

      flag2 = 1;
      flag5 = 1;
      flag4 = 1;
      optmenu = 4;
      menu = 3;
    }
   flag6 = 1;
  }

  
  // operation menu
  if( menuSet == 3){
     if( optMenuSet == 2)
     {
      if( flag6 == 1)
      {
       lcd.clear();
       flag6 = 0 ;
       menu = 1 ; 
      }
      lcd.setCursor(0, 0);
      lcd.print("Spool and Ferrari");
      lcd.setCursor(9, 1);
      lcd.print("On");

      /*
        Stepper motor rotaion code
       */

      flag3 = 1;
      flag4 = 1;
      flag5 = 1;
      menu = 1;
     }
    if( optMenuSet == 4)
    { 
      if( flag5 == 1)
      {
       lcd.clear();
       flag5 = 0 ;
       menu = 3 ; 
       optmenu = 3;
       
       while(1)
       {
        lcd.setCursor(4, 0);
        lcd.print("Set Ferari on");
        
        lcd.setCursor(4, 1);
        lcd.print("Left Spool side");

        lcd.setCursor(4, 2);
        lcd.print("Left Position: ");
        
        lcd.setCursor(17, 2);
        leftPosition = map(count, 0, 200, 0, 100);//200 rpm max speed
        //move the stepper motor 2 with this code
        
        //
        lcd.print(String(leftPosition));
       }
      }
      lcd.setCursor(4, 0);
      lcd.print("Set Ferari on");

      lcd.setCursor(4, 1);
      lcd.print("Right Spool side");

      lcd.setCursor(4, 2);
      lcd.print("Right Position: ");

      lcd.setCursor(17, 2);
      rightPosition = map(count, 0, 200, 0, 100);//200 rpm max speed
      //move the stepper motor 2 with this code
        
      //
      lcd.print(String(rightPosition));
      
      lcd.setCursor(0 ,3);
      lcd.print("Press okay");

      flag3 = 1;
      flag4 = 1;
      flag6 = 1;
      menu = 1;
    }
  }
}
