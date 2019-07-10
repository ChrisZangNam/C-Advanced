#include <gtk/gtk.h>

#include"interface.h"
#include<stdlib.h>

int
main (int argc, char **argv)
{
  inital(argc,argv);
  
  btcls(root);
  btcls(soundexTree);

  return 0;
}
//gcc `pkg-config --cflags gtk+-3.0` -o t main1.c `pkg-config --libs gtk+-3.0` libbt.a


