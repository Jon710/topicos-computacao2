// LCD module connections
sbit LCD_RS at PORTC5_bit;
sbit LCD_EN at PORTC4_bit;
sbit LCD_D7 at PORTC3_bit;
sbit LCD_D6 at PORTC2_bit;
sbit LCD_D5 at PORTC1_bit;
sbit LCD_D4 at PORTC0_bit;

// Pin direction
sbit LCD_RS_Direction at DDC5_bit;
sbit LCD_EN_Direction at DDC4_bit;
sbit LCD_D7_Direction at DDC3_bit;
sbit LCD_D6_Direction at DDC2_bit;
sbit LCD_D5_Direction at DDC1_bit;
sbit LCD_D4_Direction at DDC0_bit;

// End LCD module connections
char *text1 = "Duty Cycle:   %";
char *text2 = "Velocidade:";
char current_duty;

int flag;
int state = 0;

 void timer_init(){
 //Timer 1
 TCCR1A |= (1 << WGM10); /* Fast PWM mode, 8-bit */
 TCCR1B |= (1 << WGM12); /* Fast PWM mode, pt.2 */
 TCCR1B |= (1 << CS11); /* PWM Freq = F_CPU/8/256 */
 //TCCR1A |= (1 << COM1A1);
 //TCCR1A |= (1 << COM1B1); /* PWM output on OCR1B */

// Timer 2
   /*TCCR2A |= (1 << WGM20);  //Fast PWM mode
   TCCR2A |= (1 << WGM21);  //Fast PWM mode, pt.2
   TCCR2B |= (1 << CS21);  //PWM Freq = F_CPU/8/256
   TCCR2A |= (1 << COM2A1);  //PWM output on OCR2A*/
 }

  void TIMER1_COMPA_vect () org IVT_ADDR_TIMER1_COMPA {}
void main() {
  
  DDRC = 0B00000000;
  DDRB = 0B00000000;
  DDRD = 0B11111111;
  //PORTB = 0;
  PORTD = 0;
  // INICIALIZA O DISPLAY LCD
 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

  current_duty  = 128;
  SREG_I_bit = 0;               // Interrupt enable
  //TCCR1B |= (1 << WGM12)|(1 << CS11);          //Habilita WGM12 e CS12 para prescaler de 8
  timer_init();
 //TIMSK1 = 0b00000010;


   while(1)
   {

      if (Button(&PINB, 2, 5, 1)) {
       flag = 1;
      }
      if (flag && Button(&PINB, 2, 5, 0)) {
       state = !state;
       flag = 0;
      }

            if(PINB.B0)
            {
             Delay_ms(40);
             current_duty=current_duty+5;
             PWM1_Set_Duty(current_duty);
            }
            else if(PINB.B1)
            {
              Delay_ms(40);
              current_duty=current_duty-5;
              PWM1_Set_Duty(current_duty);
            }

      if(state)
      {
        PWM1_Start();
      }
      if(!state){
         PWM1_Stop();
      }
       OCR1AH = 0;
       OCR1AL = current_duty;
       TIMSK1 |= (1<< OCIE1A);
      //text1[12] = (current_duty/10) + 48 ;
      text1[13] = (current_duty%10) + 48;
      Lcd_Out(1, 3, text1);
   }
}