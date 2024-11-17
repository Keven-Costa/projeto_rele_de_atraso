void mensagemAjusteManual() {
  // Exibi no LCD 'Ajuste: Manual'
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Ajuste:");
  lcd.setCursor(4, 1);
  lcd.print("Manual");
  delay(1700);
  lcd.clear();
}