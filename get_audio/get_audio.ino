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

void setup() {
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
}

void loop() {
  // testa a nota tocada
  //teste_de_nota();
  // testa escala
  praticador();
  le_botao();
}
