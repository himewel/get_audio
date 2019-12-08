float freq = 0;
int nota = -1;

void setup() {
  Serial.begin(9600);
}

void loop() {

  // testa a nota tocada
  teste_de_nota();

  // testa escala
  //praticador();
}
