int posicaoColuna = 0;

// Caracteres Personalizados
byte customChar1[] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};
byte customChar2[] = {
  0x00,
  0x00,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};
byte customChar3[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};
byte customChar4[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x1F,
  0x1F
};
byte customChar5[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};


void definirCaracteresLCD() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar1);
  lcd.createChar(1, customChar2);
  lcd.createChar(2, customChar3);
  lcd.createChar(3, customChar4);
  lcd.createChar(4, customChar5);
  lcd.clear();
}

void animarLCD() {
  lcd.setCursor(posicaoColuna, 0);
  lcd.write(0);
  lcd.setCursor(posicaoColuna, 1);
  lcd.write(0);

  lcd.setCursor(posicaoColuna + 1, 0);
  lcd.write(1);
  lcd.setCursor(posicaoColuna + 1, 1);
  lcd.write(0);

  lcd.setCursor(posicaoColuna - 1, 0);
  lcd.write(1);
  lcd.setCursor(posicaoColuna - 1, 1);
  lcd.write(0);

  lcd.setCursor(posicaoColuna + 2, 0);
  lcd.write(2);
  lcd.setCursor(posicaoColuna + 2, 1);
  lcd.write(0);

  lcd.setCursor(posicaoColuna - 2, 0);
  lcd.write(2);
  lcd.setCursor(posicaoColuna - 2, 1);
  lcd.write(0);


  lcd.setCursor(posicaoColuna + 3, 0);
  lcd.write(3);
  lcd.setCursor(posicaoColuna + 3, 1);
  lcd.write(0);

  lcd.setCursor(posicaoColuna - 3, 0);
  lcd.write(3);
  lcd.setCursor(posicaoColuna - 3, 1);
  lcd.write(0);

  lcd.setCursor(posicaoColuna + 4, 0);
  lcd.write(4);
  lcd.setCursor(posicaoColuna + 4, 1);
  lcd.write(0);

  lcd.setCursor(posicaoColuna - 4, 0);
  lcd.write(4);
  lcd.setCursor(posicaoColuna - 4, 1);
  lcd.write(0);



  lcd.setCursor(posicaoColuna + 5, 1);
  lcd.write(1);

  lcd.setCursor(posicaoColuna - 5, 1);
  lcd.write(1);


  lcd.setCursor(posicaoColuna + 6, 1);
  lcd.write(2);

  lcd.setCursor(posicaoColuna - 6, 1);
  lcd.write(2);

  lcd.setCursor(posicaoColuna + 7, 1);
  lcd.write(3);

  lcd.setCursor(posicaoColuna - 7, 1);
  lcd.write(3);
  delay(50);
  lcd.clear();
  posicaoColuna++;
  if (posicaoColuna == 21)
    posicaoColuna = -7;
}