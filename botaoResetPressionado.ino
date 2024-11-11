void botaoResetPressionado() {
  // Define o contador para 0 e exibina no LCD
  contador = 0;
  lcd_1.clear();
  lcd_1.print("Contador: 0");
  delay(200);
  lcd_1.clear();

  // Reseta a duranção da Medição de Folha
  duracaoMilisegundos = 0;
}