#include <LiquidCrystal.h>

int pino6 = 6;
int button1 = 2;
int mov;
volatile int escala_atual = 0;
char posicao_nota = '0';

LiquidCrystal lcd(12, 11, 5, 4, 3, 8);

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(pino6, OUTPUT);
  pinMode(button1, INPUT);
  attachInterrupt(digitalPinToInterrupt(button1), botaofunc, FALLING);
  analogWrite(pino6, 80);
  estado(escala_atual);
}


void andador() {
  lcd.setCursor(0,0);
  lcd.print("                          ");
  if (escala_atual == 0) {
    if (posicao_nota == 1) {
      lcd.setCursor(0,0);
      lcd.print("o");
    } else if (posicao_nota == 2) {
      lcd.setCursor(2,0);
      lcd.print("o");
    } else if (posicao_nota == 3) {
      lcd.setCursor(4,0);
      lcd.print("o");
    } else if(posicao_nota == 4) {
      lcd.setCursor(6,0);
      lcd.print("o");
    } else if (posicao_nota == 5) {
      lcd.setCursor(8,0);
      lcd.print("o");
    } else if (posicao_nota == 6) {
      lcd.setCursor(10,0);
      lcd.print("o");
    } else if(posicao_nota == 7) {
      lcd.setCursor(12,0);
      lcd.print("o");
    }
  } else {
    if (posicao_nota == 3) {
      lcd.setCursor(0,0);
      lcd.print("o");
    } else if (posicao_nota == 4) {
      lcd.setCursor(2,0);
      lcd.print("o");
    } else if (posicao_nota == 5) {
      lcd.setCursor(4,0);
      lcd.print("o");
    } else if(posicao_nota == 6) {
      lcd.setCursor(6,0);
      lcd.print("o");
    } else if(posicao_nota == 7) {
      lcd.setCursor(8,0);
      lcd.print("o");
    }
  }
}

void estado(int escala) {
  lcd.setCursor(0,1);
  lcd.print("                          ");
  switch (escala) {
    case 0:
      lcd.setCursor(0,1);
      lcd.print("C D E F G A B");
    break;
    case 1:
      lcd.setCursor(0,1);
      lcd.print("A C D E G");
    break;
    default:
      lcd.setCursor(0,0);
      lcd.print("Error");
    break;
  }
}

void botaofunc() {
  escala_atual = !escala_atual;
  estado(escala_atual);
}

void loop() {
  if (Serial.available() > 0) {
    posicao_nota = Serial.read();
    andador();
  }
}
