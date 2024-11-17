void mensagemMedirPulso() {
  // Exibi no LCD 'Ajuste: Por pulso'
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Ajuste:");
  lcd.setCursor(4, 1);
  lcd.print("Por pulso");
  delay(1700);
  lcd.clear();
}