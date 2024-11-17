void exibirMedicaoFolha() {
  // Altera a tela do LCD para medir o pulso
  lcd.setCursor(0, 0);
  lcd.print("Medicao de");
  lcd.setCursor(0, 1);
  lcd.print("Folha: ");
  lcd.setCursor(7, 1);
  lcd.print("     ");
  lcd.setCursor(7, 1);
  lcd.print(teste);
  lcd.setCursor(14, 1);
  lcd.print("ms");
}