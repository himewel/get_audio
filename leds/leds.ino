#include <LiquidCrystal.h>

int pino6 = 6;
int button1 = 2;
int posicao_nota;
int receber0 = A0;
int receber1 = A1;
int receber2 = A2;
int escala_atual = 0;
int controle = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 8);

void setup(){
  Serial.begin(9600);
  pinMode(pino6, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(A4,OUTPUT);
  lcd.begin(16, 2);
  analogWrite(pino6, 80);
  estado(escala_atual);
}

void andador(){
  if(escala_atual == 0){
    if(posicao_nota == 1){
      lcd.setCursor(0,0);
      lcd.print("  *             ");
    }else
    if(posicao_nota == 2){
      lcd.setCursor(0,0);
      lcd.print("    *           ");
    }else
    if(posicao_nota == 3){
      lcd.setCursor(0,0);
      lcd.print("      *         ");
    }else
    if(posicao_nota == 4){
      lcd.setCursor(0,0);
      lcd.print("        *       ");
    }else
    if(posicao_nota == 5){
      lcd.setCursor(0,0);
      lcd.print("          *     ");
    }else
    if(posicao_nota == 6){
      lcd.setCursor(0,0);
      lcd.print("            *   ");
    }else
    if(posicao_nota == 7){
      lcd.setCursor(0,0);
      lcd.print("              * ");
    } else {
      lcd.setCursor(0,0);
      lcd.print("*               ");
    }
  } else{
    if(posicao_nota == 0){
      lcd.setCursor(0,0);
      lcd.print("*               ");
    }else
    if(posicao_nota == 1){
      lcd.setCursor(0,0);
      lcd.print("  *             ");

    }else
    if(posicao_nota == 2){
      lcd.setCursor(0,0);
      lcd.print("    *           ");

    }else
    if(posicao_nota == 3){
      lcd.setCursor(0,0);
      lcd.print("      *         ");

    }else
    if(posicao_nota == 4){
      lcd.setCursor(0,0);
      lcd.print("        *       ");
    } else {
      lcd.setCursor(0,0);
      lcd.print("*               ");
    }
  }
}

void estado(int escala){
  lcd.setCursor(0,1);
  lcd.print("                         ");
  switch (escala){
    case 0: //linha e coluna
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

void loop(){
    analogWrite(A4, controle);
    int bit0 = analogRead(receber0);
    int bit1 = analogRead(receber1);
    int bit2 = analogRead(receber2);

    if(bit0 == 0 && bit1 == 0 && bit2== 0){
      posicao_nota = 0;
    } else if(bit0 >= 900 && bit1 == 0 && bit2 == 0){
      posicao_nota = 1;
    } else if(bit0 == 0 && bit1 >= 900 && bit2 == 0){
      posicao_nota = 2;
    } else if(bit0 >= 900 && bit1 >= 900 && bit2 == 0){
      posicao_nota = 3;
    } else if(bit0 == 0 && bit1 == 0 && bit2 >= 900){
      posicao_nota = 4;
    } else if(bit0 >= 900 && bit1 == 0 && bit2 >= 900){
      posicao_nota = 5;
    } else if(bit0 == 0 && bit1 >= 900 && bit2 >= 900){
      posicao_nota = 6;
    } else if(bit0 >= 900 && bit1 >= 900 && bit2 >= 900){
      posicao_nota = 7;
    }

    if (digitalRead(button1) == LOW) {
      escala_atual = !escala_atual;
      if (controle == 255) {
        controle = 0;
      } else {
        controle = 255;
      }
      delay(200);
      Serial.println("Trocou");
      estado(escala_atual);
    }

    Serial.println(posicao_nota);
    andador();
}
