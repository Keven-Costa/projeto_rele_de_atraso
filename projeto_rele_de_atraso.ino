#define USE_SERIAL_2004_LCD
#include "LCDBigNumbers.hpp"  // Inclui a biblioteca para mostrar os números grandes (já inclui a biblioteca LiquidCrystal_I2C)
LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, LCD_ROWS);

LCDBigNumbers bigNumberLCD(&lcd, BIG_NUMBERS_FONT_3_COLUMN_2_ROWS_VARIANT_2);

// Define os pinos dos componetes
#define CHAVE_SEGURANCA 2
#define BUZZINA 3
#define BOTAO_INICIAR 4
#define BOTAO_RESET 5
#define LED 6
#define BOTAO_SAIR 7
#define BOTAO_SELECIONAR 8
#define BOTAO_NAVEGAR 9
#define SENSOR_FOTOELETRICO 10
#define POTENCIOMETRO A0


unsigned int tempoAtraso = 0;  // Armazena o tempo do potenciometro
unsigned int duracaoMilisegundos = 0;
unsigned int valor = 0;  // Armazena o valor da função 'medirFolha'

// Estados dos componentes
bool estadoBotaoIniciar = false;
bool estadoChaveSeguranca = false;

// Variáveis para função millis 1° Tarefa
unsigned long tempo_atual = 0;
unsigned long ultimo_tempo = 0;


// Variáveis para função millis 2° Tarefa (função Medir Pulso)
unsigned long startTime;
unsigned long endTime;
bool sensorActive = false;  // Flag para verificar se o sensor está ativo


// Variáveis para função millis 3° Tarefa
unsigned long ultimo_tempo3 = 0;

// Variáveis auxiliarres
bool auxiliarChaveSeguranca = true;
bool auxiliarChaveSeguranca2 = true;
bool auxiliarContador = false;


// Variáveis para o menu
unsigned int estadoMenu = 0;
unsigned int menuSelecionar = 0;

//=====================================================================
unsigned int valorSensorFotoeletrico = 0;
unsigned int contador = 0;
int auxiliarContador2 = -1;
int auxiliarTimer = -1;

void setup() {

  // Define os botões como INPUT_PULLUP
  pinMode(BOTAO_INICIAR, INPUT_PULLUP);
  pinMode(BOTAO_RESET, INPUT_PULLUP);
  pinMode(BOTAO_SAIR, INPUT_PULLUP);
  pinMode(BOTAO_SELECIONAR, INPUT_PULLUP);
  pinMode(BOTAO_NAVEGAR, INPUT_PULLUP);

  // Define a chave como INPUT
  pinMode(CHAVE_SEGURANCA, INPUT);

  // Define o LED como OUTPUT
  pinMode(LED, OUTPUT);

  // Define o buzzer como OUTPUT
  pinMode(BUZZINA, OUTPUT);

  // Define o Sensor Foto  como INPUT
  pinMode(SENSOR_FOTOELETRICO, INPUT);

  definirCaracteresLCD();

  // Loop para animar o LCD
  for (int i = 0; i < 20; i++) {
    animarLCD();
  }
  mensagemInicializacao();
  configuracaoInicialLcd();
}

void loop() {
  tempo_atual = millis();                               // Armazena o tempo atual desde que o programa começou a rodar,
  estadoChaveSeguranca = digitalRead(CHAVE_SEGURANCA);  // Ler o estado da Chave de Segurança
  valorSensorFotoeletrico = digitalRead(SENSOR_FOTOELETRICO);

  // Verfica se o Botão Reset foi pressionado
  if (digitalRead(BOTAO_RESET) == LOW) {
    botaoResetPressionado();
  }

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

  switch (estadoMenu) {
    case 0:
      lcd.setCursor(6, 0);
      lcd.print("TacoArt");
      lcd.setCursor(4, 3);
      lcd.print("Pressione OK");

      if (digitalRead(BOTAO_SELECIONAR) == LOW) {
        delay(200);
        estadoMenu = 1;
        lcd.clear();
      }
      break;

    case 1:  // Menu: Ajustar Manual
      // Exibe no LCD '<< Ajuste: Manual >>'
      lcd.setCursor(6, 1);
      lcd.print("Ajuste:");
      lcd.setCursor(2, 2);
      lcd.print("<<");
      lcd.setCursor(7, 2);
      lcd.print("Manual");
      lcd.setCursor(16, 2);
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
        estadoMenu = 5;
        lcd.clear();
      }
      break;

    case 2:  // Menu: Ajustar Por Pulso
      // Exibe no LCD '<< Ajuste: Por pulso >>'
      lcd.setCursor(6, 1);
      lcd.print("Ajuste:");
      lcd.setCursor(2, 2);
      lcd.print("<<");
      lcd.setCursor(5, 2);
      lcd.print("Por pulso");
      lcd.setCursor(16, 2);
      lcd.print(">>");

      // Verifica se o Botão Navegar foi pressionado
      if (digitalRead(BOTAO_NAVEGAR) == LOW) {
        delay(200);
        estadoMenu = 3;
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

    case 3:  // Menu: Operação

      // Exibe no LCD '<< Ajuste: Por pulso >>'
      lcd.setCursor(6, 1);
      lcd.print("Comecar");
      lcd.setCursor(2, 2);
      lcd.print("<<");
      lcd.setCursor(5, 2);
      lcd.print("Operacao");
      lcd.setCursor(16, 2);
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
        estadoMenu = 6;
        lcd.clear();
      }

      break;

    case 4:  // Ajuste por Pulso
      auxiliarContador == false;
      exibirMedicaoFolha();

      valor = medirFolha2();
      tempoAtraso = valor;

      auxiliarChaveSeguranca2 = false;  // Recebe true para que a função map mapeie para um intervalo de tempo (0 a 4000 ms)

      // Verifica o Botão Sair
      if (digitalRead(BOTAO_SAIR) == LOW) {
        delay(200);
        estadoMenu = 2;
        lcd.clear();
      }
      break;
    case 5:  // Ajuste Manual

      exibirTimer();


      // Verifica o Botão Sair
      if (digitalRead(BOTAO_SAIR) == LOW) {
        delay(200);
        estadoMenu = 1;
        lcd.clear();
      }

      // Verifica se a Chave de Segurança está ativada
      switch (estadoChaveSeguranca) {
        case HIGH:

          // Exeucuta a função apenas uma vez
          if (!auxiliarChaveSeguranca) {
            exibirAjusteTempoDesativado();
            auxiliarChaveSeguranca = true;  // Marca como executado
          }



          break;

        case LOW:


          if (auxiliarChaveSeguranca2) {
            // Mapeia o valor lido do potenciômetro (0 a 1023) para um intervalo de tempo (0 a 4000 ms)
            tempoAtraso = map(analogRead(POTENCIOMETRO), 0, 1023, 0, 4000);
            delay(100);

          } else {
            // Mapeia o valor lido do potenciômetro (0 a 1023) para um intervalo de tempo (0 a 4000 ms)
            tempoAtraso = map(analogRead(POTENCIOMETRO), 0, 1023, valor, 4000);
            delay(100);
          }

          // Quando a chave de segurança é desativada, reseta o flag
          auxiliarChaveSeguranca = false;
          break;
      }

      break;

    case 6:  // Operação

      exibirTimer();
      lcd.setCursor(0, 3);
      lcd.print("Contador:");  // Espaços suficientes para cobrir qualquer valor anterior

      ativaSensorFotoeletrico();
      // Atualiza o valor somente se ele mudoar
      if (contador != auxiliarContador2) {
        auxiliarContador2 = contador;

        lcd.setCursor(10, 2);
        lcd.print("          ");
        lcd.setCursor(10, 3);
        lcd.print("          ");
      }

      bigNumberLCD.setBigNumberCursor(10, 2);
      bigNumberLCD.print(contador);  // Mostra o valor atualizado

      // Verifica se o Botão Sair foi pressionado
      if (digitalRead(BOTAO_SAIR) == LOW) {
        delay(200);
        estadoMenu = 3;
        lcd.clear();
      }

      break;
  }
}
