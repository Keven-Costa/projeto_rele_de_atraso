void exibirMedicaoFolha() {
  // Altera a tela do LCD para medir o pulso
  lcd_1.setCursor(0, 0);
  lcd_1.print("Medicao de");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Folha: ");
  lcd_1.setCursor(7, 1);
  lcd_1.print(duracaoMilisegundos);  // Imprimi os milisegundos com 3 casas decimais
  lcd_1.setCursor(14, 1);
  lcd_1.print("ms");
}