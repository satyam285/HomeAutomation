int DOPin = 2;
int greenLed=6;
int redLed =7;
int buzzer =9;
int led1=13;
int led2=12; 
int water = A0;    //water Pin
int ldrPin = A1;   // select the input pin for LDR                                         
int ldrvalue = 0; 
int pir=3;         //pir pin 
int pirState = LOW;  
int ps = LOW;
int val = 0;                    
int count = 0;
int wl=0;
int prev=0;
int current=0;
char c;
String st;


void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(DOPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pir, INPUT); 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(water, INPUT );
  
  Serial.begin(9600);
}

void pirsen()
{
 ldrvalue = analogRead(ldrPin);
 Serial.println(ldrvalue);
if( ldrvalue > 50)                 //day
 {
  
  val = digitalRead(pir);  
  if (val == HIGH) 
  {            
    digitalWrite(greenLed, HIGH);  
    if (pirState == LOW)
    {
       Serial.println("Motion detected!");
       pirState = HIGH;   }
  } else {
    digitalWrite(greenLed, LOW); // turn LED OFF
    if (pirState == HIGH)
    {
       Serial.println("Motion ended!");
       pirState = LOW;
      count++;
    }
  }
  if ((count%2)!=0)
  {
    
  if (ps == LOW)
   {
    digitalWrite(led1, HIGH);
    digitalWrite(led2,HIGH);
      ps = HIGH;
    }
  }
  else 
  {
   
     if (ps == HIGH)
      {
      digitalWrite(led1, LOW);
      digitalWrite(led2,LOW);
      ps = LOW;
      
    } 
  }
}
 
  else if( ldrvalue <= 50 )                       //night
  {  
     val = digitalRead(pir);  
  if (val == HIGH)
  {            
    digitalWrite(greenLed, HIGH);
    
    if (pirState == LOW)
    {
       Serial.println("Infiltration");
    tone(buzzer,1000);
    delay(1000);
    pirState = HIGH;
    }
    
  } else {
    digitalWrite(greenLed, LOW); // turn LED OFF
    if (pirState == HIGH)
    {
      Serial.println("Infiltration Done");
      pirState = LOW;
    }
  }
  }
}

void gassen()
{
  if (digitalRead(DOPin) == LOW)              //GAS 
  {                    
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    
    tone(buzzer,1000,500);
    
    Serial.println("Gas leak = ON");
  } 
  else 
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
  delay(1000);
}
void  watersen()
{
  if(analogRead(water)>=200)
  { 
    
    tone(buzzer,1000,500);
    Serial.println("Tank Full !!!");
}
delay(500);
}

void loop() {
  


pirsen();
gassen(); 
watersen();

while(Serial.available() > 0)              //For Bluetooth 
{
  delay(10);
  c = Serial.read();
  if(c=='#')
  {break;}
  st+=c;  
}
if(st.length() > 0)
{  
if(st.equalsIgnoreCase("*All On"))
{
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);  
}
if(st.equalsIgnoreCase("*All Off"))
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);  
}
st="";
}
}               
