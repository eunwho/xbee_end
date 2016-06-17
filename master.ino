String fs="uh160526master1"; //temp
long ms00=0;
long rep0=1;//8초 반복 횟수
volatile int f_wdt=1;

String gg="";
String s="";
String ss="";
String cmd="";

void wait_pd()
{
	delay(100);
	digitalWrite(13,HIGH);
    	delay(10);
    	digitalWrite(13,LOW);
	delay(100);

  	Serial.println("Garbage [");
  	while (Serial.available()) 
  	{
    		Serial.print(int(Serial.read()));
  	} 
    	Serial.println("] EndGarbage!!!");
	
	char cc=0;
    // ? 보내고 ! 응답 있으면 코디가 처리 중이므로 아래 실행
    // 아니면 무한루프
    //!12345678#
    //!00000001#
	//rep0=2;
  	Serial.println("rep0 ?");
	delay(1000);
	//  while (!Serial.available()){};//? !
  
  	if (Serial.available()){//? !
    // ? 보내고 ! 응답 있으면 코디가 처리 중이므로 아래 실행
    // 아니면 무한루프
    //!12345678#
    //!00000001#
      cc=Serial.read();
          Serial.print("cc=");
          Serial.println(int(cc));
      
      if (cc=='!')
      {
  
          long repi=0;
          for (long i=0; i<8; i++)
          {
            while (!(Serial.available())){}
            char cc=Serial.read();
            Serial.write(cc);
            repi=repi*10+int(cc)-48;
           
          }//for
            while (!(Serial.available())){}
            char cc=Serial.read();
            Serial.write(cc);
            Serial.print("repi=");
            Serial.println(repi);
            if (cc=='#') if (repi!=0) rep0=repi;
       }}//if (Serial.available()//? !
  
  Serial.print("rep0=");
  Serial.println(rep0);
//  Serial.println("bye.....");

  Serial.println("EndGarbage!!! [");
    while (Serial.available()) 
  {
    Serial.print(int(Serial.read()));
    } 
    Serial.println("] EndGarbage!!!");

 Serial.println(millis()-ms00);
 Serial.println("bye.....");
//160526
 s="";      ATCmd("DB"); s+=ss;
delay(100);
          digitalWrite(13,HIGH);//160516
 delay(100);
  for (int i=0; i<rep0; i++){ 
//    Serial.println(millis());delay(10);
    f_wdt = 0;
    enterSleep();  //Serial.println(millis());
//    Serial.println(ms);
  }
}

#include <SoftwareSerial.h>
float f200=231.95;
float f200s=142.1;

//analogReference(INTERNAL);
SoftwareSerial mySerial(2, 3); // RX, TX

int eead=0;
int een=0;
#include <EEPROM.h>

/*
 * Sketch for testing sleep mode with wake up on WDT.
 * Donal Morrissey - 2011.
 *
 */
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#define LED_PIN (13)
/***************************************************
 *  Name:        ISR(WDT_vect)
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Watchdog Interrupt Service. This
 *               is executed when watchdog timed out.
 *
 ***************************************************/
ISR(WDT_vect)
{
  if(f_wdt == 0)
  {
    f_wdt=1;
  }
  else
  {
    Serial.println("WDT Overrun!!!");
  }
}
/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Enters the arduino into sleep mode.
 *
 ***************************************************/
void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();
 
  /* Now enter sleep mode. */
  sleep_mode();
 
  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */
 
  /* Re-enable the peripherals. */
  power_all_enable();
}
/***************************************************
 *  Name:        setup
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Setup for the serial comms and the
 *                Watch dog timeout.
 *
 ***************************************************/
void pd_setup()
{
  Serial.begin(9600);
  Serial.println("Initialising...");
  delay(100); //Allow for serial print to complete.
  pinMode(LED_PIN,OUTPUT);
  /*** Setup the WDT ***/
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  /* set new watchdog timeout prescaler value */
  WDTCSR = 1<<WDP0 | 1<<WDP3; /* 8.0 seconds */
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
  Serial.println("Initialisation complete.");
  delay(100); //Allow for serial print to complete.
}
/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Main application loop.
 *
 ***************************************************/
int i;
void pd_wdt()
{
  if(f_wdt == 1)
  {
    /* Toggle the LED */
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    i++;
Serial.println("?1");
Serial.println(i);
    delay(100);
    /* Don't forget to clear the flag. */
    f_wdt = 0;
   
    /* Re-enter sleep mode. */
    enterSleep();
//    delay(100);
    i++;Serial.println("?2");Serial.println(i);
  }
  else
  {
    /* Do nothing. */
    //i++;Serial.println("?3");Serial.println(i);
  }
}

void eewr(int i)
{
  Serial.println();
  Serial.print("EEwr");
  Serial.println(eead);
  EEPROM.write(eead,i/256);
  eead++;
  EEPROM.write(eead,i%256);
  eead++;
  EEPROM.write(eead,255);
}

int eer0[30];
void eer()
{
  eead=0;
  while (EEPROM.read(eead)<255)
  {
    eead++;
    eead++;   
  }
  Serial.println(eead);
een=eead/2;
  Serial.println(een);


  for (int i=0; i<een; i++)
{
    eer0[i]=EEPROM.read(i*2)*256;
    eer0[i]+=EEPROM.read(i*2+1);
    Serial.print(i);
    Serial.print(":");
    Serial.println(eer0[i]);
}
Serial.println("End");
}


void Find()
{
  Serial.println("[f]ind");
 
eead=0;
//  EEPROM.write(eead,255);
//for (int i=1; i<9999; i++)
for (int i=1; i<999; i++)
{
  if (Serial.available())
  if (Serial.read()=='E') i=9999;
 
  mySerial.print("F");
if (i<1000) mySerial.print("0");
if (i<100) mySerial.print("0");
if (i<10) mySerial.print("0");
  mySerial.print(i);
  mySerial.write(13);

  delay(5);

  while (mySerial.available())
{
  char cc;
  cc=mySerial.read();
  Serial.write(cc);
  if (cc=='E') eewr(i);
}

  Serial.print(".");
}
  Serial.println();
  Serial.println("Find End");
}

float v1,v2;
void setup() {
  analogReference(INTERNAL);
  pinMode(9,OUTPUT); //160519 solar down
  pinMode(5,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(5,LOW);
//  digitalWrite(13,HIGH);
  digitalWrite(13,LOW);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println(fs);
ss=""; 
      ATCmd("ZS"); ss+=":"+s;
      ATCmd("MY"); ss+=":"+s;
      ATCmd("MP"); ss+=":"+s;
      ATCmd("SH"); ss+=":"+s;
      ATCmd("SL"); ss+=":"+s;
      ATCmd("DH"); ss+=":"+s;
      ATCmd("DL"); ss+=":"+s;
      ATCmd("GT"); ss+=":"+s;
      ATCmd("%V"); ss+=":"+s;
      ATCmd("NI");// ss+=":"+s;
gg=s;
s="";      ATCmd("DB"); s+=ss;
  while (!Serial) {
    Serial.read();
  }

  Serial.println("Goodnight moon!");

delay(20);
  Serial.print(v1=float (analogRead(A2))/f200s,4);
  Serial.println("v");
  Serial.print(v2=float (analogRead(A3))/f200,4);
  Serial.println("v");

  mySerial.begin(9600);
  mySerial.println("Hello, world?");

eer();
digitalWrite(5,HIGH);

delay(100);
Find();eer();

digitalWrite(5,LOW);
delay(300);
pd_setup();
}

long ms0=0;
int ms=10*1000;

int coreTemp;
float currentVolt;   // device voltage
void getTempVolt()
{
 ADMUX = (_BV(REFS1)|_BV(REFS0)|_BV(MUX3)); //internal ref 1.1V and MUX=1000
 ADCSRA |= _BV(ADEN);      //enable ADC
 delay(15);         // wait for ADC stable
    digitalWrite(3,1);
 ADCSRA |= _BV(ADSC);      //start ADC
 while(bit_is_set(ADCSRA,ADSC));
 coreTemp=ADCW;
 coreTemp=float(ADCW*100-32431)/1.22;
 
 ADMUX = (_BV(REFS1)|_BV(REFS0)|7); //internal ref 1.1V and MUX=0111
 ADCSRA |= _BV(ADSC);      //start ADC
 while(bit_is_set(ADCSRA,ADSC));
 currentVolt=float(ADCW)/1024*1.1*13.3/3.3;
//    digitalWrite(3,0);
}


void loop() { // run over and over

	analogReference(DEFAULT);
   	getTempVolt();
  	analogReference(INTERNAL);

    	Serial.print("t = ");
    	Serial.print(coreTemp);
    	Serial.print(", volt = ");
    	Serial.print(currentVolt);
    	Serial.print(",");
    
	v2=float (analogRead(A3))/f200;
	v1=float (analogRead(A2))/f200s;

	if (v2>3.3)	loop0();

	wait_pd();   
}


void loop0()
{
	if (ms>millis()) ms0=ms;
	{
		ms00=millis();
  		ms0+=ms;
  		digitalWrite(5,HIGH);
  		digitalWrite(13,LOW);
  		delay(100);
  		
  		Serial.println("LH");
  		Serial.println();
  		Serial.println(ms0/1000);
 
  		Serial.println("LH");
  		Serial.println("LH");
		{

    	}
    	digitalWrite(9,LOW);
	delay(300);
	v2=float (analogRead(A3))/f200;
	v1=float (analogRead(A2))/f200s;
  	Serial.print(v1,3);  Serial.println("v");
  	Serial.print(v2,3);  Serial.println("v");
  	Serial.print("Solar = ");
  	Serial.println(v2);

	if (v2>3.9)
	{
  		digitalWrite(9,HIGH);
  		Serial.println("Solar Down");
		delay(300);
		float v11=float (analogRead(A2))/f200s;
  		Serial.print(v11,3);  Serial.println("v");
	}
	else digitalWrite(9,LOW);
	
	s="";     
 	ATCmd("DB"); 
	//        Serial.print("L,0,0,RSSI=");
	int i=eer0[0];
	//        Serial.print("L,0,0,");
    Serial.print("L,");
    Serial.print(i/100+90);
    Serial.print(",");
    Serial.print(i%100);
    Serial.print(",");
    Serial.print(gg);
    Serial.print(":RSSI=");
    Serial.print(s);
	
	s=ss;
	s+=":"+String(v1,3)+":"+String(v2,3);
	s+=":"+String(float(coreTemp)/100)+":"+String(currentVolt);
        
     Serial.println(s);

  	Log0();
  	Serial.println("LH");

  	Serial.print("...");
	delay (10);

  	digitalWrite(13,HIGH);
  	digitalWrite(5,LOW);
}
  	if (mySerial.available()) {
    		Serial.write(mySerial.read());
  	}

  	if (Serial.available()) {  
	    //mySerial.write(
    	 	char cc;
     	cc=Serial.read();
     	mySerial.write(cc);
	    if (cc=='g') Log0();
  	}
}


void Log0()
{
  Serial.println("LO[g]");

  mySerial.write(13);
delay (10);
while (mySerial.available()) mySerial.read();

  for (int j=0; j<een; j++)
{

int i=eer0[j];

int ccp=0;//160526
  delay(100);
          digitalWrite(13,HIGH);
          delay(10);
          digitalWrite(13,LOW);

  delay(100);
  Serial.print("L");
if (i<1000) Serial.print("0");
if (i<100) Serial.print("0");
if (i<10) Serial.print("0");
  Serial.println(i);


    mySerial.print("L");
if (i<1000) mySerial.print("0");
if (i<100) mySerial.print("0");
if (i<10) mySerial.print("0");
  mySerial.print(i);
  mySerial.write(13);

  delay(100);

  while (!(mySerial.available())){};
 
  while (mySerial.available()) {
char cc=mySerial.read();
//if (!(mySerial.available())) delay(20);
if (!(mySerial.available())) delay(3);//160519
    if ((int(cc)!=13)&&(cc!='\n'))
    {
    Serial.write(cc);
if (cc==',') ccp++;
if (ccp==3)
{
  ccp=0;
  Serial.print(gg);
  Serial.print(":");    
}
    }
  }

  Serial.println("");
  delay(100);//160519

}

delay(100);
          digitalWrite(13,HIGH);
          delay(10);
          digitalWrite(13,LOW);


}

/////////////////////////////////////////////////
//
//   Functions
//
/////////////////////////////////////////////////

void ATCmd(String c){
  	if (xBeeConn()){
      	c="AT"+c;
      	Serial.println(c);
	     s=Serial.readString();
		s.replace("\r","");
  	}
   	int a= xBeeDisConn();
     Serial.print(c);
     Serial.print("= ");
     Serial.println(s);
}
 
/////////////////////////////////////////////////



int xBeeRSSI(){
  if (xBeeConn()){
      Serial.println("ATDB");
      s=Serial.readString();
  }
   return xBeeDisConn();
}



int ATID(){
  if (xBeeConn()){
      Serial.println("ATID");
      s=Serial.readString();
  }
   return xBeeDisConn();
}



int ATMY(){
  if (xBeeConn()){
      Serial.println("ATMY");
      s=Serial.readString();
  }
   return xBeeDisConn();
}

int xBeeConn(){
  delay(30);
//  delay(5);
//  delay(100);  delay(1400);
  Serial.print("+++");
//  delay(100);  delay(1400);
//  delay(20);
  return checkOK();
}


int xBeeDisConn(){
  Serial.println("ATCN");
  return checkOK();
}

int checkOK(){
  String reply="";
  char r=0;
  long ii=0;
  Serial.setTimeout(200);
  reply=Serial.readString();
  if( reply =="OK\r"){
//  if( reply =="OK"){
    return 1;
  } else{
    return 0;
  }
 
}