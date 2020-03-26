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

char cent = 0,seg = 0,m = 0,h = 0;
char *text = "00:00:00:00";
int cnt;
char flag1 = 0;
char flag2 = 0;
char flag3 = 0;
char flag4 = 0;
char trava = 1;

void TIMER1_COMPA_vect () org IVT_ADDR_TIMER1_COMPA {


    PORTB.B4 = ~PORTB.B4;             // toggle PORTB
 cent++;
 if(cent>99){
   seg++;
   cent=0;
  if(seg>59){
    seg=0;
    m++;
    if(m>59){
       seg=0;
       m=0;
       h++;
       if(h>23) {
          seg=0;
          m=0;
          h=0;

        }
     }
   }
  }
   TCNT1H = 0;
   TCNT1L = 0;

  }


void main(){

 DDRB = 0b11110000; // COLOCA B4,B5,B6,B7 COMO SAIDA PARA OS BOTÕES
 
  SREG_I_bit = 0;               // Interrupt enable

  TCCR1A = 0;

  TCCR1B = 0b00001100;

  TCCR1C=0;

 TCNT1H = 0;
 TCNT1L = 0;
 /*OCR1AH = 0b00000010;    //PARA 625            00000010 01110001
 OCR1AL = 0b01110001;*/

 OCR1AH = 0b00000001; //PARA 312
 OCR1AL = 0b00111000;
 /*OCR1AH = 0b00000100;   //PARA 1250
 OCR1AL = 0b11100010;*/
 
 TIMSK1 = 0b00000010;


 
 // INICIALIZA O DISPLAY LCD
 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 while (1){


    if (Button(&PINB, 0, 1, 1)) {
      flag1 = 1;
    }
    if (flag1 && Button(&PINB, 0, 1, 0)) {
      SREG_I_bit = ~SREG_I_bit;
      trava = ~trava ;             // Interrupt enable
      flag1 = 0;
    }

   if(trava == 1)
    {
    if (Button(&PINB, 1, 1, 1)) {
      flag2 = 1;
    }
    if (flag2 && Button(&PINB, 1, 1, 0)) {
      seg++;
      if (seg > 59){
         seg = 0;
      }
      flag2 = 0;
    }

  if (Button(&PINB, 2, 1, 1)) {
      flag3 = 1;
    }
    if (flag3 && Button(&PINB, 2, 1, 0)) {
      m++;
      if (m > 59){
         m = 0;
      }

      flag3 = 0;
    }


   if (Button(&PINB, 3, 1, 1)) {
      flag4 = 1;
    }
    if (flag4 && Button(&PINB, 3, 1, 0)) {
      h++;
      if(h > 23){
      h = 0;
      }
      flag4 = 0;
    }
    
   }
   
  text[9] = (cent/10) + 48 ;
  text[10] = (cent%10) + 48;
  text[6] = (seg/10) + 48;
  text[7] = (seg%10) + 48;
  text[3] = (m/10) + 48;
  text[4] = (m%10) + 48;
  text[0] = (h/10) + 48;
  text[1] = (h%10) + 48;

  Lcd_Out(1, 3, text);

  }
 }