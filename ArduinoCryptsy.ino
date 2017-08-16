#include <LiquidCrystal.h>
#include <EEPROM.h>

String str;
String buy = "";
String sell = "";
char buySave[7];
char sellSave[7];
boolean mainFlag= false;
boolean loadFlag= false;
const int buttonPin10 = 10;
const int buttonPin11 = 11;
const int buttonPin12 = 12;
const int buzzerPin = 8;
boolean saveButton = 0;
boolean loadButton = 0;
boolean mainButton = 0;
float buyFloat = 0.00f;
float sellFloat = 0.00f;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() 
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode (buttonPin10, INPUT);
  pinMode (buttonPin11, INPUT);
  pinMode (buttonPin12, INPUT);
  lcd.setCursor(0,0);
  lcd.print("Waiting");
  tone(buzzerPin, 1000, 1000);
}

void loop() 
{
  str = Serial.readString();
  saveButton = digitalRead (buttonPin10);
  loadButton = digitalRead (buttonPin11);
  mainButton = digitalRead (buttonPin12);
  if (!mainButton) 
  {
    tone(buzzerPin, 4000, 50);
    lcd.clear();
    mainFlag = true;
    loadFlag = false;
  }
  if (!loadButton) 
  {
    tone(buzzerPin, 4000, 50);
    lcd.clear();
    loadFlag = true;
    mainFlag = false;
  }
  if (!saveButton && buy != "" && sell != "")
    {
      tone(buzzerPin, 4000, 50);
      lcd.clear();
      mainFlag= false;
      buy.toCharArray(buySave,7);
      sell.toCharArray(sellSave,7);
      EEPROM.put(1, buySave);
      EEPROM.put(10, sellSave);
      lcd.print("Saved!");
      delay(1000);
    }
  if (str != "")
  {
    buy = str.substring(1, str.substring(0,1).toInt() + 1);
    sell = str.substring(str.substring(0,1).toInt() + 1);     
  }
  
  if (buy != "" && sell != "" && mainFlag == true)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Buy");
    lcd.setCursor(4,0);
    lcd.print(buy);
    lcd.setCursor(0,1);
    lcd.print("Sell");
    lcd.setCursor(5,1);
    lcd.print(sell);
  }
  
  if (buy == "" && sell == "" && mainFlag == true)
  {
    lcd.clear();
    lcd.print("Nothing to show");
  }
  
    if (loadFlag == true)
    {
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print ("Loaded:");
      lcd.setCursor (0,1);
      EEPROM.get(1, buySave); 
      EEPROM.get(10, sellSave);
      lcd.print (buySave);
      lcd.setCursor(8,1); 
      lcd.print(sellSave);
    }
  

}

