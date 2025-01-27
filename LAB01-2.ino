#include <avr/io.h>
#define F_CPU 16000000UL
#define SW1 PD2
#define SW2 PD3
#define LED_R PD4
#define LED_Y PD5
#define LED_G PD6

#define one_second_for_count 62500  // 10/256*62.5ns
uint8_t count = 0;
bool condition = false;

void off_all_LED() {
  PORTD &= ~((1 << LED_R) | (1 << LED_Y) | (1 << LED_G));  // led off
}

void Start() {
  if (!(PIND & (1 << SW1))) {
    condition = true;
  }
}

void Reset() {
  if (!(PIND & (1 << SW2))) {
    condition = false;
    count = 0;
    off_all_LED();
  }
}

int main(void) {
  //Set PORT
  DDRD |= ((1 << LED_R) | (1 << LED_Y) | (1 << LED_G));
  DDRD &= ~((1 << SW1) | (1 << SW2));
  //Set timer
  TCCR1A = 0x00;  // normal mode
  TCCR1B = 0x04;  // 256 prescale
  TCNT1 = 0;      //set initial timer = 0

  while (true) {
    Start();
    Reset();
    if ((condition == true) && (TCNT1 > one_second_for_count)) {
      count += 1;
      TCNT1 = 0;
    }
    switch (count) {
      case 0:
        off_all_LED();
        break;
      case 10:
        off_all_LED();
        PORTD |= 0b01000000;
        break;
      case 20:
        off_all_LED();
        PORTD |= 0b00100000;
        break;
      case 30:
        off_all_LED();
        PORTD |= 0b01100000;
        break;
      case 40:
        off_all_LED();
        PORTD |= 0b00010000;
        break;
      case 50:
        off_all_LED();
        PORTD |= 0b01010000;
        break;
      case 60:
        off_all_LED();
        PORTD |= 0b01110000;
        break;
      default:
        if (count > 60) {
          off_all_LED();
          PORTD |= 0b01110000;
        }
        break;
    }
  }
}