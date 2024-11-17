void exibirTimer() {
  // Exibe no LCD o texto "Timer: " seguido do valor de tempoAtraso e a unidade "ms"
  lcd.setCursor(0, 0);
  lcd.print("Timer: ");
  lcd.setCursor(7, 0);
  lcd.print("    ");  // Limpa o espaço à direita de "Timer: "
  lcd.setCursor(7, 0);
  lcd.print(tempoAtraso);
  lcd.setCursor(14, 0);
  lcd.print("ms");
}