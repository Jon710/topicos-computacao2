#define MAX 255
#define  MIN 0
char current_duty = 0;
int flag;
int state = 0;

void main(){

  DDRC = 0B00000000;
  DDRB = 0B00000000;
  DDRD = 0B11111111;
  PORTB = 0;
  PORTD = 0;


  current_duty  = 0;
  PWM1_Init(_PWM1_FAST_MODE, _PWM1_PRESCALER_8, _PWM1_NON_INVERTED, current_duty);


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
             current_duty = current_duty + 3;
             if(current_duty  == MAX){
               current_duty  = current_duty;
             }
             PWM1_Set_Duty(current_duty);
            }
            else if(PINB.B1)
            {
              Delay_ms(40);
              current_duty = current_duty - 3;
              if(current_duty == MIN){
                 current_duty = current_duty;
              }
              PWM1_Set_Duty(current_duty);
            }

      if(state)
      {
        PWM1_Start();
      }
      if(!state){
         PWM1_Stop();
         portd.b5 = 0;
      }

   }
}