void ativaSensorFotoeletrico() {

  // Verfica se o Sensor de Proximidade esta ativado
  if (valorSensorFotoeletrico == HIGH && !sensorActive) {
    // Inicia o temporizador quando o sensor é ativado (detecta um objeto)
    startTime = millis();
    sensorActive = true;
  }

  // Verfica se o Sensor de Proximidade esta desativado
  if (valorSensorFotoeletrico == LOW && sensorActive) {

    // Para o temporizador quando o sensor é desativado
    endTime = millis();
    float duracao = endTime - startTime;  // Calcula o tempo de ativação
    duracaoMilisegundos = duracao;        // Converte para milisegundos
    auxiliarContador = true;
    adicionaContador(auxiliarContador);

    sensorActive = false;  // Reseta a flag para aguardar o próximo pulso
  }


  delay(100);  // Pequeno atraso para evitar leitura excessiva
}