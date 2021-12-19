//#link "chr_generic.s"

#include "neslib.h"

#define STRLEN(s) (sizeof(s) / sizeof(s[0]))
const char HEX[16] = "0123456789ABCDEF";

char text[] = "Hello world!";
char password[] = "12345";

void crypt(char *msg, char msgLen, char *key, char keyLen) {
  char i, j, k;  
  for (i = 0; i < msgLen; ++i) {    
    k = key[i % keyLen];
    for (j = 0; j < keyLen; ++j) {
      k = k ^ (key[(i + j) % keyLen]) + (k / 2);
    }
    msg[i] = msg[i] ^ k;
  }  
}

void printVar(char x, char y, char *str, char len) {
  vram_adr(NTADR_A(x, y));
  vram_write(str, len);
}

void printTxt(char x, char y, char *str) {
  char len = 0;    
  while (str[len++]);
  vram_adr(NTADR_A(x, y));
  vram_write(str, len);
}

void main(void) {  
  
  // Set colors
  pal_col(0, 0x02);
  pal_col(1, 0x14);
  pal_col(2, 0x20);
  pal_col(3, 0x30);

  // Encrypt
  crypt(text, STRLEN(text), password, STRLEN(password));
  printTxt(2, 2, "Encrypted:");
  printVar(2, 3, text, STRLEN(text));  
  
  // Decrypt
  crypt(text, STRLEN(text), password, STRLEN(password));
  printTxt(2, 5, "Decrypted:");
  printVar(2, 6, text, STRLEN(text));  

  // Turn on the PPU
  ppu_on_all();  
  
  // Loop
  while (1);
}

