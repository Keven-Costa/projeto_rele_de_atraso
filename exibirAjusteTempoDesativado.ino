void exibirAjusteTempoDesativado() {
  // Exibi no LCD 'AJUSTAR TEMPO DESATIVADO'
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("AJUSTAR TEMPO");
  lcd.setCursor(3, 1);
  lcd.print("DESATIVADO");
  delay(800);
  lcd.clear();
}