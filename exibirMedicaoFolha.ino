void exibirMedicaoFolha() {

  lcd.setCursor(2, 0);
  lcd.print("Medicao de Folha");

  static int ultimoTempoAtraso = -1;  // Armazena o último valor exibido para evitar atualizações desnecessárias

  // Atualiza o valor somente se ele mudou
  if (valor != ultimoTempoAtraso) {
    ultimoTempoAtraso = valor;

    // Limpa o espaço apenas ao redor do número, sem apagar a tela inteira
    lcd.setCursor(0, 1);
    lcd.print("                  ");  // Limpa apenas o espaço usado pelos números grandes
    lcd.setCursor(0, 2);
    lcd.print("                  ");  // Limpa apenas o espaço usado pelos números grandes
  }

  // Atualiza o valor da medição no display
  bigNumberLCD.setBigNumberCursor(0, 1);  
  bigNumberLCD.print(valor);              

  // Mostra a unidade "ms" na posição correta
  lcd.setCursor(18, 1);
  lcd.print("ms");
}
