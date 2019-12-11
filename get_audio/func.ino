/* pentatonica

A2 [105 - 112]
C3 [116 - 135]
D3 [140 - 150]
E3 [160 - 168]
G4 [380 - 390]


E -5-8-------
A -----5-7---
D ---------5-
G -----------

*/

/* DO

C3 [116 - 124] **
D3 [140 - 150] **
E3 [160 - 168] **
F4 [335 - 355] -- PEGAR O DA GUITARRA
G4 [380 - 390] **
A4 [435 - 455] -- PEGAR O DA GUITARRA
B3 [240 - 250] -- PEGAR O DA GUITARRA

E ---------------
A -3-5-7---------
D -------3-5-7---
G -------------4- */

void codifica_nota (int nota) {
  switch (nota) {
    case 0:
      analogWrite(A2, 0);
      analogWrite(A1, 0);
      analogWrite(A0, 0);
      break;
    case 1:
      analogWrite(A2, 0);
      analogWrite(A1, 0);
      analogWrite(A0, 255);
      break;
    case 2:
      analogWrite(A2, 0);
      analogWrite(A1, 255);
      analogWrite(A0, 0);
      break;
    case 3:
      analogWrite(A2, 0);
      analogWrite(A1, 255);
      analogWrite(A0, 255);
      break;
    case 4:
      analogWrite(A2, 255);
      analogWrite(A1, 0);
      analogWrite(A0, 0);
      break;
    case 5:
      analogWrite(A2, 255);
      analogWrite(A1, 0);
      analogWrite(A0, 255);
      break;
    case 6:
      analogWrite(A2, 255);
      analogWrite(A1, 255);
      analogWrite(A0, 0);
      break;
    case 7:
      analogWrite(A2, 255);
      analogWrite(A1, 255);
      analogWrite(A0, 255);
      break;
  }
}

int descobre_nota (float nota) {
  if (((nota <= 112)&&(nota >= 105))||((nota >= 218)&&(nota <= 225))||((nota >= 435)&&(nota <= 440))) {
    return 6; // A
  } else if ((nota <= 250)&&(nota >= 240)||((nota >= 112)&&(nota <= 115))) {
    return 7; // B
  } else if ((nota >= 116)&&(nota <= 135)){
    return 1; // C
  } else if ((nota <= 150)&&(nota >= 140)||((nota >= 289)&&(nota <= 295))) {
    return 2; // D
  } else if ((nota >= 170)&&(nota <= 180)) {
    return 4; // F
  } else if ((nota >= 190)&&(nota <= 200)||((nota >= 345)&&(nota <= 350))) {
    return 5; // G
  } else if ((nota <= 168)&&(nota >= 160)||((nota >= 320)&&(nota <= 330))) {
    return 3; // E
  }

  return 0;
}

// recebe a nota, a escala e a posição e retorna
// se a nota tocada é a certa
bool verificador (int nota) {
  int aux_pos = posicao_nota;

  // escalas
  // do = 0
  // pentatonica la = 2
  if (escala_atual == 0) {
    while(aux_pos >= 7){
      aux_pos = aux_pos - 7;
      posicao_nota = aux_pos;
    }

    // normaliza a posicao
    if (c[aux_pos] == nota) {
      return true;
    }
    return false;

  } else if (escala_atual == 1) {
    while(aux_pos >= 5){
      aux_pos = aux_pos - 5;
      posicao_nota = aux_pos;
    }

    if (pent_la_menor[aux_pos] == nota) {
      return true;
    }
    return false;
  }

  return false;
}

float captura_frequencia() {
  String amostra = Serial.readStringUntil('\n');
  float frequencia = amostra.toFloat();

  if (frequencia < 80) {
    frequencia = 80;
  } else if (frequencia > 1050) {
    frequencia = 1050;
  }

  return frequencia;
}

void teste_de_nota() {

  float freq = 0;
  int nota = -1;

  freq = captura_frequencia();
  nota = descobre_nota(freq);

  Serial.println(nota);
  codifica_nota(nota);

  // enquanto a nota n'ao mudar fica esperando
  while(freq == captura_frequencia());
}

void praticador(){
  //primeiro captura a nota
  float freq = 0;
  int nota = -1;

  freq = captura_frequencia();
  nota = descobre_nota(freq);

  Serial.println(nota);
  codifica_nota(posicao_nota);

  if (verificador(nota) && nota != 0) {
    // esta certo
    // enquanto a nota n'ao mudar fica esperando
    //while(freq == captura_frequencia());
    // vai para proxima nota da escala
    posicao_nota ++;
  } else {
    // esta errado
    // enquanto a nota n'ao mudar fica esperando
    //while(freq == captura_frequencia());
  }
}

void le_botao(){
  int interrup = analogRead(A4);

  if(interrup > 900){
    if(escala_atual == 0)
      posicao_nota = 0;

    escala_atual = 1;
  }else{
    if(escala_atual == 1)
      posicao_nota = 0;
    escala_atual = 0;
  }

}
