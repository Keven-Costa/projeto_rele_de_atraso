void exibirAjusteTempoDesativado() {
// Exibi no LCD 'AJUSTAR TEMPO DESATIVADO'
  lcd_1.clear();
  lcd_1.backlight();
  lcd_1.setCursor(2, 0);
  lcd_1.print("AJUSTAR TEMPO");
  lcd_1.setCursor(3, 1);
  lcd_1.print("DESATIVADO");
  delay(500);
  lcd_1.clear();
}