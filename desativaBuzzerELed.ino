void desativaBuzzerELed() {
  estadoBotaoIniciar = false;  // Reseta o estado do botão para permitir uma nova ativação
  digitalWrite(LED, LOW);
  noTone(BUZZINA);
}