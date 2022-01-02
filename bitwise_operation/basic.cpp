#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

  // extract bit from 9th to 14th
  // make a mask 
  //* my version
  unsigned int a = 0; 
  for(int i = 9;i <= 14;i++) {
    a |= (1 << i);
  }

  unsigned int b = 0xb10;
  b &= a; // extract b's 9th to 14th bits
  b = b >> 9;
  cout << b << endl;
  //*/
  
  //* teacher's version
  //1. shift the identified portion to right hand side until it touches the least significant bit(0th bit)
  //2. mask the value to extract only 6 bits [5:0] and then save it into another variable
  uint16_t data = 0xb10;
  uint8_t output = 0;
  uint8_t mask_6_bits = 0x3f;
  output = (uint8_t)((data >> 9) & mask_6_bits);
  cout << (uint16_t)output << endl;
  fflush(stdout);
  //*/
  return 0;
}

