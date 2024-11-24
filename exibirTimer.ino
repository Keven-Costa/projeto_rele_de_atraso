void exibirTimer() {
  lcd.setCursor(0, 0);
  lcd.print("Timer");

  // Atualiza o valor somente se ele mudou
  if (tempoAtraso != auxiliarTimer) {
    auxiliarTimer = tempoAtraso;

    // Limpa o espaço apenas ao redor do número, sem apagar a tela inteira
    lcd.setCursor(5, 0);
    lcd.print("            ");  // Limpa apenas o espaço usado pelos números grandes
    lcd.setCursor(5, 1);
    lcd.print("            ");  // Limpa apenas o espaço usado pelos números grandes
  }
  bigNumberLCD.setBigNumberCursor(5);
  bigNumberLCD.print(tempoAtraso);  // Mostra o valor atualizado

  lcd.setCursor(18, 0);
  lcd.print("ms");
}
// Exibe no LCD o texto "Timer: " seguido do valor de tempoAtraso e a unidade "ms"
// lcd.setCursor(0, 0);
// lcd.print("Timer: ");
// lcd.setCursor(5, 0);
// lcd.print("            ");  // Limpa o espaço à direita de "Timer: "
// lcd.setCursor(5, 1);
// lcd.print("            ");  // Limpa o espaço à direita de "Timer: "


// bigNumberLCD.setBigNumberCursor(5);
// bigNumberLCD.print(tempoAtraso);  // use the standard print function
// lcd.setCursor(18, 0);
// lcd.print("ms");
