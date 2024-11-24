void botaoResetPressionado() {
  tempoAtraso = 0;
  valor = 0;
  contador = 0;
  auxiliarChaveSeguranca = true;

  // Reseta a duranção da Medição de Folha
  duracaoMilisegundos = 0;
  delay(150);
}
