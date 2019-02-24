#include <unistd.h>

char hex2asc[17]="0123456789ABCDEF";

void write_hex(int a, int b)
{
  int counter;
  a %= 65536;
  int div = 4096;

  if (b == 2) // let b denote how many characters
    div = 16;

  for (div; div >= 1; div /= 16) {
    counter = 0;   
    while ((a / div) > 0 ) {
        counter++;
        a -= div;
    }
    write(1, &hex2asc[counter], 1);
  }
}


int main()
{
  int a = 0; //address decimal value
  unsigned char c[8]; //next 8 characters read in
  int n = read(0,c,8);

  while (n != 0) {
    //error checking
    if (n == -1) {
      write(1, "Error", 5);
      continue;
    }

    //address output
    write_hex(a,4);
    write(1, "  ", 2);
    
    //hh output
    for (int i = 0; i < n; i++) {
      write_hex(c[i],2);
      write(1, " ", 1);

      //conversion of non printable chars
      if ((c[i] > 126) || (c[i] < 32)) 
        c[i] = '.';
    }
   
    //print remaining spaces
    for (int i = 0; i < (3*(8-n)+1); i++)
      write(1, " ", 1);

    //print cached chars
    write(1, c, n);
    write(1, "\n", 1);
    
    a += 8;
    n = read(0,c,8);
  }  
  return(0);
}
