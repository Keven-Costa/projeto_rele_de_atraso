void medirFolha() {

  // Usa pulseIn para medir a duração do pulso HIGH com timeout de 2 segundos
  unsigned long duracao = pulseIn(SENSOR_PROXIMIDADE, HIGH, 2000000);

  if (duracao > 0) {                         // Se foi detectado um pulso válido
    duracaoMilisegundos = duracao / 1000.0;  // Converte microssegundos para milissegundos
  }
  delay(100);  // Pequeno atraso para evitar leituras constantes
}


  // Função para Medir o Pulso sem usar a função pulseIn()
void medirFolha2() {

  // Verfica se o Sensor de Proximidade esta ativado
  if (valorSensorAproximidade == HIGH && !sensorActive) {
    // Inicia o temporizador quando o sensor é ativado (detecta um objeto)
    startTime = millis();
    sensorActive = true;
  }

  // Verfica se o Sensor de Proximidade esta desativado
  if (valorSensorAproximidade == LOW && sensorActive) {

    // Para o temporizador quando o sensor é desativado
    endTime = millis();
    duracao = endTime - startTime;           // Calcula o tempo de ativação
    duracaoMilisegundos = duracao / 1000.0;  // Converte para milisegundos

    // Exibe o tempo no Serial Monitor
    Serial.print("Duração do pulso: ");
    Serial.print(duracaoMilisegundos, 2);  // Exibe até 6 casas decimais
    Serial.println(" ms");

    sensorActive = false;  // Reseta a flag para aguardar o próximo pulso
  }

  delay(100);  // Pequeno atraso para evitar leitura excessiva
}