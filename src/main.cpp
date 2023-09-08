#include <Arduino.h>
#include "encoder.h"
#include "digital_out.h"


//Part 1 and 2
// int main()
// {
//   Digital_out led(5); //Built-in LED
//   Encoder encoder(4, 5); //c1: D2, c2: D3

//   led.init();
//   encoder.init();

//   Serial.begin(9600);

//   while (1) {
    
    
//     bool c1_hi = encoder.is_C1_hi();
//     bool c2_hi = encoder.is_C2_hi();


//     if (c1_hi && !c2_hi) {
//       encoder.updateCounter(true);
//       Serial.println(encoder.getPosition());
//     } else if (!c1_hi && c2_hi) {
//       encoder.updateCounter(false);
//       Serial.println(encoder.getPosition());
//     }
    

//     while (c1_hi || c2_hi) {
//       c1_hi = encoder.is_C1_hi();
//       c2_hi = encoder.is_C2_hi();
//       led.set_hi();
//     }
    
//     _delay_us(1000);  //sampling rate of 1 ms
//     led.set_lo();
//   }

//   return 0;
// }


//Part 3
bool c1_hi = false;
bool clockwise = false;

Digital_out led(5); //Built-in LED
Encoder encoder(2, 3); //c1: D2, c2: D3

int main()
{
  Serial.begin(9600);
 
  led.init();
  encoder.init();

  DDRD &= ~(1 << DDD2); // set the PD2 pin as input
  PORTD |= (1 << PORTD2); // enable pull-up resistor on PD2
  EICRA |= (1 << ISC01) | (1 << ISC00); // set INT0 on rising edge
  EIMSK |= (1 << INT0); // Turns on INT0
  sei();

  while(1)
  {
    _delay_us(2000);
    
    if(c1_hi)
    {
      encoder.updateCounter(clockwise);
      Serial.println(encoder.getPosition());
      c1_hi = false;
      clockwise = false;

      led.toggle();
    }
  }

  return 0;
}

ISR (INT0_vect)
{
  c1_hi = true;
  if(!encoder.is_C2_hi())
  {
    clockwise = true;
  }
}
