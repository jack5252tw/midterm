#include "mbed.h"

const int NUM_OF_KEY = 3;
BusIn keyboard(D3, D4, D5);
int store[12];
int cnt = 0;

Serial pc(USBTX, USBRX);

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
  while (cnt <= 11) {

    int key = read_one_key(NUM_OF_KEY);
    
    if (key != -1) {
      store[cnt] = key;
      cnt++;
      printf("%d\r\n",key);
    }
    
    wait(0.5);
  }
  /////////////////////////////////////////////
  int first = cnt[0]*4 + cnt[1]*2 + cnt[2]*1;
  int second = cnt[3]*4 + cnt[4]*2 + cnt[5]*1;
  int third = cnt[6]*4 + cnt[7]*2 + cnt[8]*1;
  int fourth = cnt[9]*4 + cnt[10]*2 + cnt[11]*1;
  int sum = first+second+third+fourth;
  printf("%d\r\n",sum);
}