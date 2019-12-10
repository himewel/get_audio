/*

UNIVERSIDADE FEDERAL DO PAMPA (UNIPAMPA)
  MICROCONTROLADORES
  PROF.: Gerson
    Graduando (matrícula) - e-mail
  Yann da Silva (161150705) – kyouch@hotmail.com – Gerente de Projeto
  Gabriel Lopes (151151372) – gabriel18.lopes@gmail.com
  Felipe Leite (151150283) – felipe.fls@outlook.com
  Welbert Hime (161151179) – welberthime@hotmail.com
  Cristian Klassen (131151674) – crisklassen@gmail.com

  Projeto Final
    Escala Pentatênica Menor de A: A - C - D - E - G
    Escala Natrual de C: C - D - E - F - G - A - B
    Escala de Em: E - F# - G - A - B - C - D

Capacitores são pra tirar os Ripple dos botões
 */

// include the library code:
#include <LiquidCrystal.h>
int pino6 = 6;
int button1 = 8;
int button2 = 7;
int mov;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// void setup() {
//   Serial.begin(9600);
//   pinMode(pino6, OUTPUT);
//   pinMode(button1, INPUT_PULLUP);
//   pinMode(button2, INPUT_PULLUP);
//  // attachInterrupt(8, oooo, RISING);
//   // set up the LCD's number of columns and rows:
//   lcd.begin(16, 2);
//   // Print a message to the LCD.
//  // lcd.print("hello, world!");
//   analogWrite(pino6, 80);
//   sel();
// }

void oooo(){
  mov = mov+1;
  if(mov > 2){
    mov = 0;
  }
  Serial.println("xxxxxx");
  sel();
}


void sel(){
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("A    C    E");
    Serial.println(mov);
    if(mov == 0) {

      lcd.setCursor(1,0);
      lcd.print("o");
    }
    if(mov == 1) {
      lcd.setCursor(6,0);
      lcd.print("o");
    }
    if(mov == 2) {
      lcd.setCursor(11,0);
      lcd.print("o");
    }
}

void estado(int caso){
  Serial.println(caso);
  lcd.clear();
  switch (caso){
    case 0: //linha e coluna
      lcd.setCursor(0, 0);
      lcd.print("A C D E G");
    break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("C D E F G A B");
    break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("E F# G A B C D");
    break;
    default:
      lcd.setCursor(0, 0);
      lcd.print("Error");
    break;
  }
}

void leds() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  if (digitalRead(button1) == HIGH) {
    oooo();
    if (digitalRead(button1) == HIGH) {
      delay(500);
    }
  }
  if (digitalRead(button2) == HIGH) {
    estado(mov);
    if (digitalRead(button2) == HIGH) {
      delay(500);
    }
  }
}
