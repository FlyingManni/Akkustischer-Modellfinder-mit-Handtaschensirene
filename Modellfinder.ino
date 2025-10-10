/* RC-Steuerung für Taschenalarm
 *  atTiny 45 mit 8 Mhz internal Clock 
 *
 * Es muss mindestens einmal ein Signal unter 1,4ms vom Empfänger gekommen sein
 * damit sich die Steuerung "scharf" schaltet, ohne vorheriges Signal wird kein
 * Alarm ausgelöst.
 * Am Empfänger sollte ein Failsave von 1,5ms aktiviert sein. Im Bereichzwischen
 * 1,4 und 1,7ms startet ein 1 Minütiger Tamer nach dessen Ablauf Alarm ausgelöst
 * wird.
 * Bei Signal über 1,7ms wird sofort Alarm ausgelöst. Auch wenn vom Empfänger gar 
 * kein Signal mehr kommt wird sofort Alarm ausgelöst (sofern der einmal "scharf"
 * geschalztet wurde).
 * 
 * Anzeigen der Status-Led:
 * aus : Alarmgeber ist nicht "scharf", es wird überhaupt kein Alarm ausgelöst
 * leuctet dauerhaft: Alarm ist "scharf" und gibt kein Alarm aus
 * blinkt schnell: 1 minuten Timer aktiv, nach Ablauf wird Alarm ausgelöst
 * blinkt langsam: Alarm ausgelöst, es sollte was zu hören sein ;-)
 * 
 */

#define INPIN 4       // Tiny45 PB4 (Pin 3) 
#define alarmpin 1    // Tiny45 PB1 (Pin 6) 
#define StatusLed 3   // Tiny45 PB3 (Pin 2) 
#define StatusLedOn digitalWrite(StatusLed, LOW)
#define StatusLedOff digitalWrite(StatusLed, HIGH)
#define ToggleStatusLed PINB |= 1<<StatusLed
#define AlarmOn digitalWrite(alarmpin, HIGH);
#define AlarmOff digitalWrite(alarmpin, LOW);

bool AlarmScharf = false;
bool DoAlarm = false;
bool CheckAlarm = false;
unsigned long res;
unsigned long countDownStart = millis();
const unsigned long CountDownTimer = 60;  // 60 Sekunden
unsigned long BlinkStart = millis();
unsigned long BlinkTime;

void setup() {
   pinMode(INPIN, INPUT);
   pinMode(StatusLed, OUTPUT);
   pinMode(alarmpin, OUTPUT);
   digitalWrite(alarmpin, LOW);
   StatusLedOff;
}

bool inRange(unsigned long val, unsigned long minimum, unsigned long maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

void StatusBlink(bool blinkFast)
{
  unsigned int TimeChangeStatus = 500;
  if (blinkFast) { TimeChangeStatus = 200; } 
  BlinkTime = (millis() - BlinkStart);
  if (BlinkTime >  TimeChangeStatus) {
    ToggleStatusLed;
    BlinkStart = millis();
  }
}

void MakeAlarm(void) {
  AlarmOn;
  StatusBlink(false);
}

void WarnungIfCountdownRunning(void) {
  StatusBlink(true);
}

void ResetContdown(void) {
  countDownStart = millis();
}

void loop() {
  CheckAlarm = true;
  res = pulseIn(INPIN, HIGH, 30000UL);
  if (res) {
      if (inRange(res, 900, 1399) == true) {
        AlarmScharf = true;
        StatusLedOn;
        AlarmOff;
        DoAlarm = false;
        CheckAlarm = false;
        ResetContdown();
        BlinkStart = millis();
      }
  } else
  {
     res = 30000;
  }  

  if ((AlarmScharf == true) && CheckAlarm) {
    if (((res > 2500) || (inRange(res, 1400, 1700) == true)) && (((millis() - countDownStart) / 1000) > CountDownTimer)) { DoAlarm = true; }  // kein Signal mehr
    if (inRange(res, 1701, 2100) == true) { // Signal am Sender aufgelöst
       DoAlarm = true; 
       ResetContdown();
    }  
    if (DoAlarm == true) { 
      MakeAlarm(); 
    } 
    else { 
      AlarmOff; 
      WarnungIfCountdownRunning();
    }
  }
  else ResetContdown();
}
