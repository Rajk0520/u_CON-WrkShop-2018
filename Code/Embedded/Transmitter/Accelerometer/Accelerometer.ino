#include <avr/io.h>   /* Include AVR std. library file */
#include <util/delay.h>   /* Include defined delay header file */

void ADC_Init()     /* ADC Initialization function */
{
  ADMUX =(1<<REFS0)|(1<<ADLAR);   /* Vref: Avcc, ADC channel: 0 */
  ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

unsigned char ADC_Read(unsigned char channel)  /* ADC Read function */
{
  ADMUX =(1<<REFS0)|(1<<ADLAR)|(channel & 0x07);/* set input channel to read */
  ADCSRA |= (1<<ADSC);  /* Start ADC conversion */
  while (!(ADCSRA & (1<<ADIF)));  /* Wait until end of conversion by polling ADC interrupt flag */
  ADCSRA |= (1<<ADIF);  /* Clear interrupt flag */
  return ADCH;    /* Return ADC word */
}
int main(void)
{
  int X,Y,Z;
  DDRB=0xFF;
  Serial.begin(9600);
  ADC_Init();   /* Initialize ADC */
  int flag=0;
  while(1)
  {
    X= ADC_Read(0)-86;  /* Read X, Y, Z axis ADC value */
    Y= ADC_Read(1)-85;
    Z= ADC_Read(2)-77;

    /*if(X>-4&& X<4 && Y<4 && Y>-4) {
      if(flag==1) {
        Serial.println("Resetted");
      }
      flag=0;
      
    }

    if(X<-13) {
      if(!flag) {
        //
        Serial.println("Left");
         _delay_ms(10);
        flag=1;
      }
    }
  else
    if(X>13) {
      if(!flag) {
        //
        Serial.println("Right");
        _delay_ms(10);
        flag=1;
      }
    }*/
    
    Serial.print("X: ");
    Serial.print(X);Serial.print('\t');
    Serial.print("Y: ");
    Serial.print(Y);Serial.print('\t');
    Serial.print("Z:");
    Serial.println(Z);
    _delay_ms(10);
  }
}
