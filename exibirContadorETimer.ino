void exibirContadorETimer(int tempo) {

  // Altera a tela do LCD para exibir o contador e o tempo
    float seg = tempo / 1000.0;
    lcd_1.setCursor(0, 0);
    lcd_1.print("Contador: ");
    lcd_1.print(contador);
    lcd_1.setCursor(0, 1);
    lcd_1.print("Timer: ");
    lcd_1.setCursor(7, 1);
    lcd_1.print(seg, 2);  // Imprimi os segundos com 2 casas decimais
    lcd_1.setCursor(13, 1);
    lcd_1.print("seg");
  
}
