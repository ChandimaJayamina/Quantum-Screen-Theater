#include <stdio.h>
#include "welcomescreen.h"


int main(void) {
  welcome();
  return 0;
}







/* 
  need PCRE lib for regex - 'sudo apt-get update
sudo apt-get install libpcre3 libpcre3-dev' | mac 'brew install pcre
'
  compile steps: 
    gcc -o app app.c welcomescreen.c show.c  -I/opt/homebrew/Cellar/pcre/8.45/include -L/opt/homebrew/Cellar/pcre/8.45/lib -lpcre
  run : ./app
  quit ctrl+c
*/
