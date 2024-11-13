#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);  // Objeto LCD

// Define os pinos dos componetes
#define CHAVE_SEGURANCA 2
#define CHAVE_MEDIR 3
#define BUZZINA 4
#define BOTAO_INICIAR 5
#define BOTAO_RESET 6
#define LED 7
#define LED_DESTAVADO 8
#define LED_TRAVADO 9
#define SENSOR_PROXIMIDADE 10
#define POTENCIOMETRO A0

unsigned int tempoAtraso = 0;  // Armazena o tempo
unsigned int valorSensorAproximidade = 0;

bool estadoBotaoIniciar = false;
bool estadoBotaoMedir = false;
bool estadoChaveSeguranca = false;
bool estadoChaveMedir = false;
float duracaoMilisegundos = 0.0;

// Variáveis para função millis 1° Tarefa
unsigned long tempo_atual = 0;
unsigned long ultimo_tempo = 0;

// Variáveis para função millis 2° Tarefa (função Medir Pulso)
unsigned long startTime;    // Variável para armazenar o tempo de início do pulso
unsigned long endTime;      // Variável para armazenar o tempo de fim do pulso
bool sensorActive = false;  // Flag para verificar se o sensor está ativo
float duracao;              //variável para guardar a duração do pulso

int contador = 0;
bool auxiliarChaveSeguranca = true;  // Variável para auxiliar na ativação da Chave de Segurança
bool auxiliarChaveMedir = true;      // Variável para auxiliar na ativação da Chave de Medir o pulso

void setup() {
Serial.begin(9600);
  // Define os botões como INPUT_PULLUP
  pinMode(BOTAO_INICIAR, INPUT_PULLUP);
  pinMode(BOTAO_RESET, INPUT_PULLUP);

  // Define as chaves como INPUT
  pinMode(CHAVE_SEGURANCA, INPUT);
  pinMode(CHAVE_MEDIR, INPUT);

  // Define os LEDs como OUTPUT
  pinMode(LED, OUTPUT);
  pinMode(LED_TRAVADO, OUTPUT);
  pinMode(LED_DESTAVADO, OUTPUT);

  // Define o buzzer como OUTPUT
  pinMode(BUZZINA, OUTPUT);

  // Define o sensor proximidade como INPUT
  pinMode(SENSOR_PROXIMIDADE, INPUT);


  mensagemInicializacao();  // Função para exibir o texto do LCD;
}

void loop() {

  tempo_atual = millis();  // Armazena o tempo atual desde que o programa começou a rodar,
  estadoChaveSeguranca = digitalRead(CHAVE_SEGURANCA);  // Ler o estado da Chave de Segurança
  estadoChaveMedir = digitalRead(CHAVE_MEDIR);          // Ler o estado da Chave de Medir o pulso

  // Verifica se o Botão Iniciar foi pressionado
  if (digitalRead(BOTAO_INICIAR) == LOW) {
    ultimo_tempo = tempo_atual;  // Registra o tempo em que o botão foi pressionado
    estadoBotaoIniciar = true;
    ativaBuzzerELed(tempoAtraso);
    botaoIniciarPressionado();
  }

  // Verifica o botão foi pressionado e se o tempo definido por 'tempoAtraso' já passou
  if (estadoBotaoIniciar && (tempo_atual - ultimo_tempo >= tempoAtraso)) {
    desativaBuzzerELed();
  }

  // Verfica se o Botão Reset foi pressionado
  if (digitalRead(BOTAO_RESET) == LOW) {
    botaoResetPressionado();
  }

  // Verifica se a chave de segurança está ativada
  if (estadoChaveSeguranca == HIGH) {
    // Liga o LED vermelho e apaga o verde
    digitalWrite(LED_TRAVADO, HIGH);
    digitalWrite(LED_DESTAVADO, LOW);

    // Exeucuta a função apenas uma vez
    if (!auxiliarChaveSeguranca) {
      exibirAjusteTempoDesativado();
      auxiliarChaveSeguranca = true;  // Marca como executado
    }

  } else {
    // Liga o LED verde e apaga o  vermelho
    digitalWrite(LED_DESTAVADO, HIGH);
    digitalWrite(LED_TRAVADO, LOW);

    // Mapeia o valor lido do potenciômetro (0 a 1023) para um intervalo de tempo (0 a 4000 ms)
    tempoAtraso = map(analogRead(POTENCIOMETRO), 0, 1023, 0, 4000);

    // Quando a chave de segurança é desativada, reseta o flag
    auxiliarChaveSeguranca = false;
  }

  // Verifica se a Chave para Medir o pulso foi ativada
  if (estadoChaveMedir == HIGH) {

    lcd_1.clear();

    // // Executa a função clear() apenas uma vez
    // if (!auxiliarChaveMedir) {
    //   lcd_1.clear();
    //   auxiliarChaveMedir = true;
    // }
    exibirMedicaoFolha();

    medirFolha();


    lcd_1.clear();
    valorSensorAproximidade = digitalRead(SENSOR_PROXIMIDADE);  // Ler o valor do Sensor de Proximidade

  } else {
    exibirContadorETimer(tempoAtraso);
    auxiliarChaveMedir = false;
  }
}
