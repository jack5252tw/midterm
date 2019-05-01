#include "mbed.h"
#include "uLCD_4DGL.h"

const int NUM_OF_KEY = 3;
BusIn keyboard(D3, D4, D5);
int store[12];
int cnt = 0;
int tmpkey = -1;

Serial pc(USBTX, USBRX);
uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

// Return a key number whose corresponding hardware key is being pressed.
int read_one_key(int key_num) {
  int _press = keyboard.read();

  // scan
  for (int i = 0; i < key_num; i++) {
    if (_press & (1 << i)) return i;
  }

  // no key is pressed
  return -1;
}

int main(void) {
  ////////////////////////////////////////////
  uLCD.background_color(BLUE);
    uLCD.cls();
    uLCD.color(WHITE);
    uLCD.textbackground_color(BLUE);
  while (cnt <= 11) {

    int key = read_one_key(NUM_OF_KEY);
    
    if (key != -1) {

      if(tmpkey == key){
        store[cnt-1] = 0;
        cnt--;
      }
      else{
        tmpkey = key;
        store[cnt] = 1;
      }
      
      printf("%d\r\n",store[cnt]);
      cnt++;
    }
    
    wait(0.5);
  }
  /////////////////////////////////////////////
  int first = store[0]*4 + store[1]*2 + store[2]*1;
  int second = store[3]*4 + store[4]*2 + store[5]*1;
  int third = store[6]*4 + store[7]*2 + store[8]*1;
  int fourth = store[9]*4 + store[10]*2 + store[11]*1;
  int sum = first+second+third+fourth;
  printf("%d\r\n",sum);
  ////////////////////////////
  int out[8] = {0,0,0,0,0,0,0,0};
  out[0] = 0;
  out[1] = 0;
  out[2] = 0;
  int tmp = sum;

  if(tmp >= 16){
      out[3] = 1;
  }
  else{
      out[3] = 0;
  }

  tmp = sum-out[3]*16;
  if( tmp >= 8){
      out[4] = 1;
  }
  else{
      out[4] = 0;
  }

  tmp = tmp-out[4]*8;
  if( tmp >= 4){
      out[5] = 1;
  }
  else{
      out[5] = 0;
  }

  tmp = tmp-out[5]*4;
  if( tmp >= 2){
      out[6] = 1;
  }
  else{
      out[6] = 0;
  }
  
  tmp = tmp-out[6]*2;
  if( tmp >= 1){
      out[7] = 1;
  }
  else{
      out[7] = 0;
  }
  /*
  for(int w = 0; w<8;w++){
    printf("%d\r\n",out[w]);
  }
  */
  uLCD.locate(1,2);
  uLCD.printf("0b%D",out[0]);
  uLCD.printf("%D",out[1]);
  uLCD.printf("%D",out[2]);
  uLCD.printf("%D",out[3]);
  uLCD.printf("%D",out[4]);
  uLCD.printf("%D",out[5]);
  uLCD.printf("%D",out[6]);
  uLCD.printf("%D",out[7]);

}