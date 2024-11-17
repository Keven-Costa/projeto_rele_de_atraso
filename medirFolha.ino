int medirFolha() {

  // Usa pulseIn para medir a duração do pulso HIGH no pino SENSOR_FOTOELETRICO, com um tempo limite de 9 segundos (9000000 microssegundos)
  unsigned long duracao = pulseIn(SENSOR_FOTOELETRICO, HIGH, 9000000);

  // Verifica se a duração do pulso detectado é maior que 50 microssegundos, indicando que o pulso é válido
  if (duracao > 50) {
    duracaoMilisegundos = duracao / 1000;  // Converte microssegundos para milissegundos
  }
  return duracaoMilisegundos;
  delay(100);  // Pequeno atraso para evitar leituras constantes
}


// Função para Medir o Pulso sem usar a função pulseIn()
int medirFolha2() {

  // Verfica se o Sensor de Proximidade esta ativado
  if (valorSensorAproximidade == HIGH && !sensorActive) {
    // Inicia o temporizador quando o sensor é ativado (detecta um objeto)
    startTime = millis();
    sensorActive = true;
    Serial.println("1° if");
  }

  // Verfica se o Sensor de Proximidade esta desativado
  if (valorSensorAproximidade == LOW && sensorActive) {

    // Para o temporizador quando o sensor é desativado
    endTime = millis();
    float duracao = endTime - startTime;  // Calcula o tempo de ativação
    duracaoMilisegundos = duracao;        // Converte para milisegundos

    // Exibe o tempo no Serial Monitor
    Serial.print("Duração do pulso: ");
    Serial.print(duracaoMilisegundos, 2);  // Exibe até 6 casas decimais
    Serial.println(" ms");

    sensorActive = false;  // Reseta a flag para aguardar o próximo pulso
  }
  return duracaoMilisegundos;

  delay(100);  // Pequeno atraso para evitar leitura excessiva
}
