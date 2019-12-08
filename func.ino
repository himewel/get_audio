// escalas escritas em ordem
// escala de dó
int c[7] = {1,2,3,4,5,6,7};

// Pentatonica la menor
// A - C - D - E - G
int pent_la_menor[5] = {6,1,2,3,5};

// posição em que a nota se encontra na guitarra
volatile int posicao_nota = 0;

// escala
// 0 -> escala de do
// 1 -> pentatonica de la menor
volatile int escala_atual = 0;

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
G -------------4-

*/


int descobre_nota (float nota) {

  //Serial.println(nota);

 if (((nota <= 112)&&(nota >= 105))||((nota >= 210)&&(nota <= 220))) {
    return 6; // A
  } else if ((nota <= 250)&&(nota >= 240)||((nota >= 112)&&(nota <= 115))) {
    return 7; // B
  } else if ((nota >= 116)&&(nota <= 135)){
    return 1; // C
  } else if ((nota <= 150)&&(nota >= 140)) {
    return 2; // D
  } else if ((nota >= 170)&&(nota <= 180)) {
    return 4; // F
  } else if ((nota >= 182)&&(nota <= 195)) {
    return 5; // G
  } else if ((nota <= 168)&&(nota >= 160)) {
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
    }

    // normaliza a posicao
    if (c[aux_pos] == nota) {
      Serial.println("\nCorreto! ");
      Serial.print("Esperado: ");
      Serial.print(c[aux_pos]);
      Serial.print(" Encontrado: ");
      Serial.println(nota);
      return true;
    }
    Serial.println("\nErrado! ");
    Serial.print("Esperado: ");
    Serial.print(c[aux_pos]);
    Serial.print(" Encontrado: ");
    Serial.println(nota);
    return false;

  } else if (escala_atual == 2) {
    while(aux_pos >= 5){
      aux_pos = aux_pos - 5;
    }

    if (pent_la_menor[aux_pos] == nota) {
      Serial.println("\nCorreto! ");
      Serial.print("Esperado: ");
      Serial.print(c[aux_pos]);
      Serial.print(" Encontrado: ");
      Serial.println(nota);
      return true;
    }

    Serial.println("\nErrado! ");
    Serial.print("Esperado: ");
    Serial.print(c[aux_pos]);
    Serial.print(" Encontrado: ");
    Serial.println(nota);
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

void teste_de_nota(){

  float freq = 0;
  int nota = -1;

  freq = captura_frequencia();
  nota = descobre_nota(freq);

  Serial.println(nota);

  // enquanto a nota n'ao mudar fica esperando
  while(freq == captura_frequencia());

  // quando a nota mudar verfica a nova nota
  teste_de_nota();
}

void praticador(){

  //primeiro captura a nota
  float freq = 0;
  int nota = -1;

  freq = captura_frequencia();
  nota = descobre_nota(freq);

  if (verificador(nota) && nota != 0) {
    // esta certo
    // enquanto a nota n'ao mudar fica esperando
    while(freq == captura_frequencia());
    // vai para proxima nota da escala
    posicao_nota ++;
  } else {
    // esta errado
    // enquanto a nota n'ao mudar fica esperando
    while(freq == captura_frequencia());
  }
}
