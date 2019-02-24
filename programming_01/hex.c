#include <unistd.h>
#include <stdio.h>

/* Format of output line:
aaaa  hh hh hh hh hh hh hh hh  cccccccc\n
*/

/* You may want to use this */
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
  unsigned char c[8];
  int h;
  
  int n = read(0,c,8);

  while (n > 0) {
    write_hex(a,4);
    write(1, "  ", 2);
    
    for (int i = 0; i < n; i++) {
      h = c[i];
      write_hex(h,2);
      write(1, " ", 1);

      if ((c[i] > 126) || (c[i] < 32)) 
        c[i] = '.';
    }
   
    for (int i = 0; i < (3*(8-n)+1); i++)
      write(1, " ", 1);
    write(1, c, n);
    write(1, "\n", 1);
    
    a += 8;
    n = read(0,c,8);
  }  
  return(0);
}
