float freq = 0;
int nota = -1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  freq = captura_frequencia();
  nota = descobre_nota(freq);

  Serial.println(nota);

//  if (verificador(freq) == 1) {
//    Serial.println(nota);
//  }
}
