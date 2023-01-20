
/*
 *  ReducePulseWidth - v1.1 - 10/11/2022 - ing. Cesare M. Casirati
 *
 *  Ritarda il fronte di salita dei segnali ad onda quadra letti tramite interrupt sui piedini 2 e 3,
 *  il ritardo è pari a 255 us - la metà della durata dell'impulso in ingresso.
 *
 *  Il segnale in ingresso è generato internamente in PWM a 490 Hz (2040 us) e duty cycle 25% sul piedino 9.
*/

#define PWM25 64UL
#define PWM_FREQ 490UL
const byte squareWavePin = 9;

unsigned long dwellTime = ( PWM25 * 1000000UL ) / ( PWM_FREQ * 256UL  );
unsigned long dwellDelay = dwellTime / 2UL;
//unsigned long dwellDelay = 3000UL;
const byte ecu1Pin  =  2;
const byte ecu2Pin  =  3;
const byte coil1Pin = 12;
const byte coil2Pin = 13;

volatile byte ecu1Output = LOW;
volatile byte ecu2Output = LOW;
volatile unsigned long startTimer1;
volatile unsigned long startTimer2;

void setup() {

  pinMode(  ecu1Pin, INPUT );
  pinMode(  ecu2Pin, INPUT );
  pinMode( coil1Pin, OUTPUT );
  pinMode( coil2Pin, OUTPUT );

  digitalWrite( coil1Pin, LOW );
  digitalWrite( coil2Pin, LOW );

  attachInterrupt( digitalPinToInterrupt( ecu1Pin ), detect1Edge, CHANGE );
  attachInterrupt( digitalPinToInterrupt( ecu2Pin ), detect2Edge, CHANGE );

  analogWrite( squareWavePin, PWM25 );

}

void loop() {

//  if( ecu1Output ) delayMicroseconds( dwellDelay );
//  digitalWrite( coil1Pin, ecu1Output );

  noInterrupts();
  if( micros() - startTimer1 >= dwellDelay ) digitalWrite( coil1Pin, ecu1Output );
  if( micros() - startTimer2 >= dwellDelay ) digitalWrite( coil2Pin, ecu2Output );
  interrupts();

}

void detect1Edge() {

  if( ecu1Output = digitalRead( ecu1Pin ) == HIGH ) startTimer1 = micros();

}

void detect2Edge() {

  if( ecu2Output = digitalRead( ecu2Pin ) == HIGH ) startTimer2 = micros();

}
