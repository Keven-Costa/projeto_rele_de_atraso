void mensagemInicializacao() {
  // Exibi no LCD 'UNINOVE Santo Amaro'
  lcd_1.begin(16, 2);  // Inicializa o LCD
  lcd_1.backlight();   // Liga a luz de fundo do display
  lcd_1.setCursor(4, 0);
  lcd_1.print("UNINOVE");
  lcd_1.setCursor(2, 1);
  lcd_1.print("Santo Amaro");
  delay(1700);
  lcd_1.clear();
  
  // Exibi no LCD 'Rele de Atraso'
  lcd_1.setCursor(5, 0);
  lcd_1.print("Rele de");
  lcd_1.setCursor(5, 1);
  lcd_1.print("Atraso");
  delay(1700);
  lcd_1.clear();
}