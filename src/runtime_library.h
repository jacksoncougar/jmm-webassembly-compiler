//
// Created by Jackson Cougar Wiebe on 4/16/2020.
//

#ifndef SCANNER_RUNTIME_LIBRARY_H
#define SCANNER_RUNTIME_LIBRARY_H

#include <iostream>

class RuntimeLibrary
{
  void putchar(int c)
  {
    std::cout << c;
  }

  void printc(int c)
  {
    putchar(c);
  }

  void printb(int b)
  {
    //    if(b) prints("true");
    //    else prints("false");
  }

  void prints(char *str, int length)
  {
    int i = 0;
    while (i < length)
    {
      putchar(str[i]);
    }
  }

  void printi(int i)
  {
    int remainder;
    int quotient;

    remainder = 0;
    quotient = i;

    while (quotient > 0)
    {
      remainder = quotient % 10;
      quotient = quotient / 10;
      putchar('0' + remainder);
    }
  }
};


#endif//SCANNER_RUNTIME_LIBRARY_H
