#include <avr/io.h>
#include <util/delay.h>
//Cat's comment
int main(void){
  DDRB = 0xFF; // Sets PB0 and PB1 to outputs
  DDRD = 0x00;
  while(1){
    if(PIND & (1<<PD0)){
      PORTB = PORTB | (1<<PB0); // Turns on only PB0
      _delay_ms(100);
      PORTB = PORTB & ~(1<<PB0);
      _delay_ms(100); 
    }
    if(PIND & (1<<PD1)){
      PORTB = PORTB | (1<<1); // Turns on only PB1
      _delay_ms(100); 
      PORTB = PORTB & ~(1<<1);
      _delay_ms(100);
    }
  }
  return(0);
}
