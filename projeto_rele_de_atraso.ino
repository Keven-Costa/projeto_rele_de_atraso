#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Objeto LCD

// Define os pinos dos componetes
#define CHAVE_SEGURANCA 2
#define CHAVE_MEDIR 3
#define BUZZINA 4
#define BOTAO_INICIAR 5
#define BOTAO_RESET 6
#define LED 7
#define LED_DESTAVADO 8
#define LED_TRAVADO 9
#define SENSOR_FOTOELETRICO 10
#define POTENCIOMETRO A0
#define BOTAO_SAIR A1
#define BOTAO_SELECIONAR A2
#define BOTAO_NAVEGAR A3

unsigned int tempoAtraso = 0;  // Armazena o tempo
unsigned int valorSensorAproximidade = 0;

bool estadoBotaoIniciar = false;
bool estadoChaveSeguranca = false;
bool estadoChaveMedir = false;

unsigned int duracaoMilisegundos = 0;

// Variáveis para função millis 1° Tarefa
unsigned long tempo_atual = 0;
unsigned long ultimo_tempo = 0;

// Variáveis para função millis 2° Tarefa (função Medir Pulso)
unsigned long startTime;    // Variável para armazenar o tempo de início do pulso
unsigned long endTime;      // Variável para armazenar o tempo de fim do pulso
bool sensorActive = false;  // Flag para verificar se o sensor está ativo
float duracao;              //variável para guardar a duração do pulso

// Variáveis para função millis 3° Tarefa
unsigned long ultimo_tempo3 = 0;
bool auxiliarChaveSeguranca = true;  // Variável para auxiliar na ativação da Chave de Segurança
bool auxiliarChaveMedir = true;      // Variável para auxiliar na ativação da Chave de Medir o pulso
bool sensor;
int teste = 0;

// Variáveis para o menu
int estadoMenu = 0;
int menuSelecionar = 0;



void setup() {

  // Define os botões como INPUT_PULLUP
  pinMode(BOTAO_INICIAR, INPUT_PULLUP);
  pinMode(BOTAO_RESET, INPUT_PULLUP);
  pinMode(BOTAO_SAIR, INPUT_PULLUP);
  pinMode(BOTAO_SELECIONAR, INPUT_PULLUP);
  pinMode(BOTAO_NAVEGAR, INPUT_PULLUP);

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
  pinMode(SENSOR_FOTOELETRICO, INPUT);

  definirCaracteresLCD();

  // Loop para animar o LCD
  for (int i = 0; i < 20; i++) {
    animarLCD();
  }

  mensagemInicializacao();


  //==========================================
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(BOTAO_RESET));
  tempo_atual = millis();                                      // Armazena o tempo atual desde que o programa começou a rodar,
  estadoChaveSeguranca = digitalRead(CHAVE_SEGURANCA);         // Ler o estado da Chave de Segurança
  estadoChaveMedir = digitalRead(CHAVE_MEDIR);                 // Ler o estado da Chave de Medir o pulso
  valorSensorAproximidade = digitalRead(SENSOR_FOTOELETRICO);  // Ler o estado



  // Verfica se o Botão Reset foi pressionado
  if (digitalRead(BOTAO_RESET) == LOW) {
    botaoResetPressionado();
  }

  switch (estadoMenu) {
    case 0:
      lcd.setCursor(4, 0);
      lcd.print("TacoArt");
      lcd.setCursor(0, 1);
      lcd.print("Pressione OK");

      if (digitalRead(BOTAO_SELECIONAR) == LOW) {
        delay(200);
        estadoMenu = 1;
        lcd.clear();
      }
      break;

    case 1:
      // Exibe no LCD '<< Ajuste: Manual >>'
      lcd.setCursor(4, 0);
      lcd.print("Ajuste:");
      lcd.setCursor(0, 1);
      lcd.print("<<");
      lcd.setCursor(5, 1);
      lcd.print("Manual");
      lcd.setCursor(14, 1);
      lcd.print(">>");

      // Verifica se o Botão Navegar foi pressionado
      if (digitalRead(BOTAO_NAVEGAR) == LOW) {
        delay(200);
        estadoMenu = 2;
        lcd.clear();
      }

      // Verifica se o Botão Sair foi pressionado
      if (digitalRead(BOTAO_SAIR) == LOW) {
        delay(200);
        estadoMenu = 0;
        lcd.clear();
      }

      // Verifica se o Botão Selecionar foi pressionado
      if (digitalRead(BOTAO_SELECIONAR) == LOW) {
        delay(200);
        estadoMenu = 4;
        lcd.clear();
      }
      break;

    case 2:
      // Exibe no LCD '<< Ajuste: Por pulso >>'
      lcd.setCursor(4, 0);
      lcd.print("Ajuste:");
      lcd.setCursor(0, 1);
      lcd.print("<<");
      lcd.setCursor(4, 1);
      lcd.print("Por pulso");
      lcd.setCursor(14, 1);
      lcd.print(">>");

      // Verifica se o Botão Navegar foi pressionado
      if (digitalRead(BOTAO_NAVEGAR) == LOW) {
        delay(200);
        estadoMenu = 1;
        lcd.clear();
      }

      // Verifica se o Botão Sair foi pressionado
      if (digitalRead(BOTAO_SAIR) == LOW) {
        delay(200);
        estadoMenu = 0;
        lcd.clear();
      }

      // Verifica se o Botão Selecionar foi pressionado
      if (digitalRead(BOTAO_SELECIONAR) == LOW) {
        delay(200);
        estadoMenu = 3;
        lcd.clear();
      }

      break;

    case 3:  // Menu: Ajustar Por Pulso

      exibirMedicaoFolha();

      teste = medirFolha2();

      // Verifica se o Botão Sair foi pressionado
      if (digitalRead(BOTAO_SAIR) == LOW) {
        delay(200);
        estadoMenu = 1;
        lcd.clear();
      }

      auxiliarChaveMedir = true;  // Recebe true para que a função map mapeie para um intervalo de tempo (0 a 4000 ms)

      break;

    case 4:  // Menu: Ajustar Manual

      exibirTimer();

      // Verifica se o Botão Iniciar foi pressionado
      if (digitalRead(BOTAO_INICIAR) == LOW) {
        ultimo_tempo = tempo_atual;  // Registra o tempo em que o botão foi pressionado
        estadoBotaoIniciar = true;
        ativaBuzzerELed(tempoAtraso);
      }

      // Verifica o botão foi pressionado e se o tempo definido por 'tempoAtraso' já passou
      if (estadoBotaoIniciar && (tempo_atual - ultimo_tempo >= tempoAtraso)) {
        desativaBuzzerELed();
      }


      // Verifica o Botão Sair
      if (digitalRead(BOTAO_SAIR) == LOW) {
        delay(200);
        estadoMenu = 2;
        lcd.clear();
      }

      // Verifica se a Chave de Segurança está ativada
      switch (estadoChaveSeguranca) {
        case HIGH:

          // Liga o LED vermelho e apaga o verde
          digitalWrite(LED_TRAVADO, HIGH);
          digitalWrite(LED_DESTAVADO, LOW);

          // Exeucuta a função apenas uma vez
          if (!auxiliarChaveSeguranca) {
            exibirAjusteTempoDesativado();
            auxiliarChaveSeguranca = true;  // Marca como executado
          }
          break;

        case LOW:
          // Liga o LED verde e apaga o  vermelho
          digitalWrite(LED_DESTAVADO, HIGH);
          digitalWrite(LED_TRAVADO, LOW);


          if (auxiliarChaveMedir) {
            // Mapeia o valor lido do potenciômetro (0 a 1023) para um intervalo de tempo (0 a 4000 ms)
            tempoAtraso = map(analogRead(POTENCIOMETRO), 0, 1023, 0, 4000);
            auxiliarChaveMedir = false;
          } else {
            // Mapeia o valor lido do potenciômetro (0 a 1023) para um intervalo de tempo (0 a 4000 ms)
            tempoAtraso = map(analogRead(POTENCIOMETRO), 0, 1023, teste, 4000);
          }

          // Quando a chave de segurança é desativada, reseta o flag
          auxiliarChaveSeguranca = false;
          break;
      }

      break;
  }
}
