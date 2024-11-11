void botaoIniciarPressionado() {
  // Incrementa o valor da variável contador em +1 e exibe no LCD
  contador++;
  lcd_1.clear();
  lcd_1.print("Contador: ");
  lcd_1.print(contador);
  delay(200);
  lcd_1.clear();
}
