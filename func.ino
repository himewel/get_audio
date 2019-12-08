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

//descobre a nota
/*
1  C [15.35 - 17.35]
2  D [17.36 - 19.5]
3  E [19.6 - 21.2]
4  F [21.3 - 23.2]
5  G [23.3 - 26]
6  A [26.1 - 29.2]
7  B [29.3 - 32]
*/

/*
1  C [885 - 17.35]
2  D [17.36 - 19.5]
3  E [82.407 - 21.2]
4  F [21.3 - 23.2]
5  G [23.3 - 26]
6  A [105 - 104]
7  B [29.3 - 32]
*/

int descobre_nota (float nota) {
  float aux = nota;
  Serial.println(nota);

  // vai dividindo por dois até chegar na frequencia base
  // while (aux >= 32) {
  //   aux -= 14.65;
  // }
  Serial.println(aux);

 if (aux <= 82.47) {
    return 3; // mi
  } else if (aux <= 92.499) {
    return 4; // fa
  } else if (aux <= 103.83) {
    return 5; // sol
  } else if (aux <= 116.54) {
    return 6; // la
  } else if (aux <= 123.47) {
    return 7; // si
  } else if (aux <= 130.81) {
    return 1; // do
  } else {
    return 2; //re
  }

  return 0;
}

// recebe a nota, a escala e a posição e retorna
// se a nota tocada é a certa
bool verificador (int nota) {
  int aux_pos = posicao_nota;

  // escalas
  // do = 1
  // pentatonica la = 2
  if (escala_atual == 1) {
    // normaliza a posicao
    while (aux_pos >= 7) {
      aux_pos = aux_pos - 7;
    }

    if (c[aux_pos] == nota) {
      return true;
    }

    return false;
  } else if (escala_atual == 2) {
    while(aux_pos >= 5){
      aux_pos = aux_pos - 5;
    }

    if (pent_la_menor[aux_pos] == nota) {
      return true;
    }

    return false;
  }

  return 0;
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

// captura a frequencia
float frequencia(){
  // defini tempo de amostragem
  int i = 0;
  float frequencia_final = 0;
  float aux = 0;

//  for (i = 0; i < 50; i++) {
//    // Captura a frequencia
//    aux = captura_frequencia();
//    //tem que pegar a frequencia pico
//    if (aux > frequencia_final) {
//      frequencia_final = aux;
//    }
//  }

  return frequencia_final;
}
