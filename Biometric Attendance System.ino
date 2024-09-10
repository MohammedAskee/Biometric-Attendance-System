#include <LiquidCrystal.h>
#include <Adafruit_Fingerprint.h> //Libraries needed
#include <SoftwareSerial.h>
#include <Keypad.h>

const int rs = 14, en =15, d4 = 16, d5 = 17, d6 = 18, d7 = 19;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial mySerial(2, 3);                //Fingerprint sensor wiring RX 3, TX 2

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

char keypressed;

char code[]={'1','2','3','4'};     //Passcode we can change it just need to keep the format "4 digits as char array" char c[4];        
//Array to get the code from the user
int ij;


//Here, keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]=
{
  {'1', '2', '3', 'E'}, 
  {'4', '5', '6', 'D'}, 
  {'7', '8', '9', 'O'},
  {'*', '0', '#', 'X'}
};

byte rowPins[numRows] = {12,11,10,9};   //Rows 0 to 3     //if we modify our pins we should modify this too
byte colPins[numCols]={8,7,6,5};        //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;


void setup()
{
  Serial.begin(9600);   //Establishing data communication
  finger.begin(57600);   // Verify that sensor is present
  lcd.begin(16, 2);    // sets the dimensions of the LCD

  lcd.setCursor(4,0);   // (col,row)
  lcd.print("WELCOME!");
  lcd.setCursor(2,1);
  lcd.print("COAL Project"); 
  delay(3000);
  lcd.clear();

  lcd.setCursor(1,0);
  //lcd.print("FingerPrint Based Attendance System");
  //delay(1000);
  marquee("FingerPrint Based Attendance System  ");
  delay(1000);
  lcd.clear();  
    
  // Print a message to the LCD.
  lcd.setCursor(3,0);
  lcd.print("Loading...");
  lcd.blink();
  delay(2000);
}

void loop(){
  keypressed = myKeypad.getKey();   //Now, Reading the buttons typed by the keypad
  
  
  getFingerprintIDez();             //Waiting for a fingerprint to scan if it's valid or not
  if(keypressed == 'E')
  { 
    //If it's 'E' it triggers "Adding new template" sequence
    ij=0;                      //ij is set to 0
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("ENROLL NEW USER:");
    lcd.setCursor(0, 1);
    lcd.write("Please wait...");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Password.");
    getPassword();            //Getting the passcode function
      if(ij==4)
      { 
        //If the passcode is correct we can start enrolling new finger template
        Enrolling();          //Enrolling the function
        delay(2000);
        lcd.clear();
      }
      else
      { 
        //If the code is wrong we can't add new users (templates)
        lcd.setCursor(0,0);
        lcd.print("Wrong code");
        delay(2000);
        lcd.clear();
      }
  }




if(keypressed == 'D')
{
    lcd.clear();
    lcd.print("Enter ID# to Delete..");
    // Serial.println("Please type in the ID # (from 1 to 127) you want to delete...");
    uint8_t id = readnumber();
    if (id == 0) {
      // ID #0 not allowed, try again!
      return;
  }else{
    // Serial.print("Deleting ID #");
    lcd.clear();
    lcd.print("Deleting ID #");
    // Serial.println(id);
    lcd.print(id);
    delay(2000);
    deleteFingerprint(id);
    }
  }


  if(keypressed == 'O')
  { 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Override User");
    lcd.blink();
    delay(2000);
    ij=0;                       //ij is set to 0
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Password");
    getPassword();              //Getting the passcode function
      if(ij==4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter ID# to");
        lcd.setCursor(5,1);
        lcd.print("..Override");
       
        // Serial.println("Please type in the ID # (from 1 to 127) you want to delete...");
        uint8_t id = readnumber();
        if (id == 0) {
          // ID #0 not allowed, try again!
          return;
        }else{
          lcd.clear();
          lcd.print("Erasing ID# ");
          delay(1000);
          // Serial.println(id);
          lcd.print(id);
          lcd.setCursor(1, 0);
          delay(2000);
          deleteFingerprint(id);
        }
        Enrolling();
        lcd.clear();
        lcd.write("Success!!");
        lcd.blink();
        lcd.setCursor(0, 1);
        delay(2000); 
      }
      else
      { 
        //If the code is wrong we can't add new users (templates)
        lcd.setCursor(0,0);
        lcd.print("Override Unsucc..");
        delay(2000);
        lcd.clear();
        lcd.clear();
      }
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("PLACE FINGER NOW");
  lcd.write("Ready to scan");
  lcd.setCursor(0, 1);
  lcd.write("Ready to Scan...");
  delay(50);


//  if(keypressed == 'X')
//  {
//    exit(0);
//  }

}
    
//Getting password (code) function, it gets the characters typed and store them in c[4] array
void getPassword()
{
  for (int i=0 ; i<4 ; i++)
  {
    int c[i];
    c[i]= myKeypad.waitForKey();
    lcd.setCursor(i,1);
    lcd.print("*");
  }
  lcd.clear();
  for (int j=0 ; j<4 ; j++)
  { 
            //comparing the code entred with the code stored if(c[j]==code[j])
    ij++;   //Everytime the char is correct we increment the ij until it reaches 4 which means the code is correct
  } 
            //Otherwise it won't reach 4 and it will show "wrong code" as written above
}



//The Enrolling and getFingerprintEnroll functions are mainly based on the "Enroll" example code from the library

void Enrolling() 
{
  keypressed == NULL;
  lcd.clear();
  lcd.print("Enroll New");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter new ID#");
  id = readnumber();        //This function gets the Id it was meant to get it from the Serial monitor 
    if (id == 0) 
    {
      // ID #0 not allowed, try again!
      return;
    }
    while (! getFingerprintEnroll() );
}

//Enrolling function only the modifications are commented
uint8_t getFingerprintEnroll() 
{
  int p = -1;
  lcd.clear();
  lcd.print("Enroll ID:");    //Message to print for every step
  lcd.setCursor(10,0);
  lcd.print(id);
  lcd.setCursor(0,1);
  lcd.print("Place finger"); //First step
  while (p != FINGERPRINT_OK) 
  {
    p = finger.getImage();
  }
  // OK success!
  p = finger.image2Tz(1);      //convert captured image into template
  switch (p) 
  {
    case FINGERPRINT_OK:
    break;
    case FINGERPRINT_IMAGEMESS:
    return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    return p;
    case FINGERPRINT_FEATUREFAIL:
    return p;
    case FINGERPRINT_INVALIDIMAGE:
    return p;
    default:
    return p;
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Please");           //After getting the first template successfully
  lcd.setCursor(0,1);
  lcd.print("Remove Finger!!");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) 
  {
    p = finger.getImage();
  }
  
  p = -1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Place");    //We launch the same thing another time to get a second template of the same finger
  lcd.setCursor(0,1);
  lcd.print("Same finger!!");
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
  }
  
  // OK success!
  p = finger.image2Tz(2);
  switch (p) {
  case FINGERPRINT_OK:
  break;
  case FINGERPRINT_IMAGEMESS:
  return p;
  case FINGERPRINT_PACKETRECIEVEERR:
  return p;
  case FINGERPRINT_FEATUREFAIL:
  return p;
  case FINGERPRINT_INVALIDIMAGE:
  return p;
  default:
  return p;
  }
  p = finger.createModel();
  if (p == FINGERPRINT_OK) 
  {
    
  } 
  else if (p == FINGERPRINT_PACKETRECIEVEERR) 
  {
    return p;
  } 
  else if (p == FINGERPRINT_ENROLLMISMATCH) 
  {
    return p;
  } 
  else 
  {
    return p;
  }
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) 
  {
    lcd.clear();            //if both images are gotten without problem we store the template as the Id we entered
    lcd.setCursor(0,0);
    lcd.print("Saved in");          //Print a message after storing and showing the ID stored
    lcd.setCursor(0,1);
    lcd.print("ID: ");
    lcd.setCursor(5,1);
    lcd.print(id);
    delay(3000);
    lcd.clear();
  } 
  else if (p == FINGERPRINT_PACKETRECIEVEERR) 
  {
    return p;
  } 
  else if (p == FINGERPRINT_BADLOCATION) 
  {
    return p;
  } 
  else if (p == FINGERPRINT_FLASHERR) 
  {
    return p;
  } 
  else 
  {
    return p;
  }
}

//This function gets the ID number as 3 digits format like 001 for ID 1
//And return the number to the enrolling function

uint8_t readnumber(void) 
{
  uint8_t num = 0;
  while (num == 0) 
  {
    char keey = myKeypad.waitForKey();
    int num1 = keey-48;
    lcd.setCursor(0,1);
    lcd.print(num1);
    keey = myKeypad.waitForKey();
    int num2 = keey-48;
    lcd.setCursor(1,1);
    lcd.print(num2);
    keey = myKeypad.waitForKey();
    int num3 = keey-48;
    lcd.setCursor(2,1);
    lcd.print(num3);
    delay(1000);
    num=(num1*100)+(num2*10)+num3;
    keey=NO_KEY;
  }
  return num;
}

//This function waits for a fingerprint, scan it and give it access if recognised
int getFingerprintIDez() 
{
  uint8_t p = finger.getImage();    //Image scanning
  if (p != FINGERPRINT_OK) return -1;
  p = finger.image2Tz();            //Converting
  if (p != FINGERPRINT_OK) return -1;
  p = finger.fingerFastSearch();    //Looking for matches in the internal memory
  if (p != FINGERPRINT_OK)
  { 
    //if the searching fails it means that the template isn't registered
    lcd.clear();           //And here we write a message or take an action for the denied template
    lcd.print("Access denied");
    delay(2000);
    lcd.clear();
    lcd.print("Place finger");
    return -1;
  }
  
  //If we found a match we proceed in the function
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Scan Success!");
  lcd.setCursor(0, 1);
  lcd.write("Found ID   #");
  lcd.setCursor(13, 1);
  lcd.print(finger.fingerID, DEC);
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Initializing...");
  delay(3000);
  ij=0; //ij is set to 0
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
  getPassword();    //Getting the passcode function
  if(ij==4)
  { 
    //If the passcode is correct we can start enrolling new finger template
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Attendance");
    lcd.setCursor(0, 1);
    lcd.write("Marked | ID#");
    lcd.setCursor(12, 1);
    lcd.print(finger.fingerID, DEC);
    delay(3000);
  }
  else
  { 
    //If the Passcode is wrong we can't add new users (templates)
    lcd.setCursor(0,0);
    lcd.print("Wrong code");
    delay(2000);
    lcd.clear();
    lcd.clear();
  }
  lcd.print("Place finger");
  return finger.fingerID;
}


uint8_t deleteFingerprint(uint8_t id) 
{
  uint8_t p = -1;  
  lcd.clear();
  lcd.print("Please wait");
  p = finger.deleteModel(id);
  if (p == FINGERPRINT_OK) 
  {
    Serial.println("Deleted!");
    lcd.clear();
    lcd.print("Finger Deleted");
    lcd.setCursor(0,1);
    lcd.print("Successfully");
    delay(1000);
  } 
  
  else 
  {
    //Serial.print("Something Wrong"); 
    lcd.clear();
    lcd.print("Something Wrong");
    lcd.setCursor(0,1);
    lcd.print("Try Again Later");
    delay(2000);
    return p;
  }   
}

void marquee(char *text)
{
  int length = strlen(text);
  if(length < 16)
    lcd.print(text);
  else
  {
    int pos;
    for(pos = 0; pos < 16; pos++)
      lcd.print(text[pos]);
    delay(1000);
    while(pos < length)
    {
      lcd.scrollDisplayLeft();
      lcd.print(text[pos]);
      pos = pos + 1;
      delay(750);  
    }  
  }
}
