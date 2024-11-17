void mensagemInicializacao() {
  // Exibi no LCD 'TacoArt'
  lcd.begin(16, 2);  // Inicializa o LCD
  lcd.backlight();   // Liga a luz de fundo do display
  lcd.setCursor(4, 0);
  lcd.print("TacoArt");
  delay(1700);
  lcd.clear();
}