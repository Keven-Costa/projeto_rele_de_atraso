void configuracaoInicialLcd() {
  lcd.init();
  bigNumberLCD.begin();  // Cria os caracteres personalizados
  lcd.clear();           // Limpa o LCD
}