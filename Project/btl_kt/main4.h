#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#define MAX_WORD 40
#define MAX_DATA 100000
void congchuoi(char *a,char *b){
  int i,j=0;
  for(i=strlen(a);i<=strlen(a)+strlen(b);i++){
    a[i]=b[j];
    j++;
  }
}

void xulichuoi(char *nguon,char *dich)
{
  int i,j,k=0,check=0;
  for(i=0;i<strlen(nguon);i++)
  {
    if(nguon[i]=='/'){
      dich[0]='\0';
      check=1;
      break;
    }
  }
  if(check==0) {
    nguon[strlen(nguon)-1]='\0';
    return;
  }
  for(j=i;j<=strlen(nguon);j++){
    dich[k]=nguon[j];
    k++;
  }
  nguon[i-1]='\0';
}
void suachuoi(char *a){
  int i;
  for(i=1;i<=strlen(a);i++)
    {
      a[i-1]=a[i];
    }
}
void creat(BTA **root,char *filename){
  FILE *f;
  int count=0;
  if(!(f=fopen("anhviet.txt","r"))){
    printf("mo file khong thanh cong\n");
    return ;
  }
  *root=btcrt("data",0,0);
  char word[MAX_WORD],data[100000],tmp[100];
  data[0]='\0';
  while(!feof(f)){
    fgets(tmp,100,f);
    while(tmp[0]!='@'){
      congchuoi(data,tmp);
      if(feof(f)) break;
      fgets(tmp,100,f);
      //puts(data);
    }
    //puts(data);
    int k=btins(*root,word,data,500*sizeof(char));
    if(k==0) count++;
    if(tmp[0]=='@'){
      strcpy(word,tmp);
      data[0]='\0';
      xulichuoi(word,data);
      suachuoi(word);
    }
    //if(count<30)puts(word);
  }
  //char data2[10000];
  printf("da them %d tu vao tu dien\n",count);
  fclose(f);
}

void load(BTA **root,char *data){
  *root=btopn("data",0,0);
}

