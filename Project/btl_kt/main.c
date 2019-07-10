
#include"hien.h"
#include"soundex.h"


// ham tim kiem 1 tu cho truoc, tra ve 1 neu ton tai, 0 neu ko ton tai. 
//tra ve 5 tu goi y luu trong suggess






int main()
{
	btinit();
	BTA *Dic,*soundexTree;
	Dic=btopn("data",0,0);
	if(!Dic){
		printf("Creating data\n");
		creat(&Dic,"anhviet2.txt");
	}
	soundexTree=btopn("soundexTree",0,0);
	if(!soundexTree){
		printf("creating soundextree\n");
		creatSoundexTree(Dic,&soundexTree);
	}
	//printSoundexTree(soundexTree);
	//printDic(Dic);
	int n;
	char word[40];
	do
	{
		printf("1. Goi y\n2. AutoComplete\n3.Exit\n");
		scanf("%d%*c",&n);
		switch(n){
			case 1: {
				
				char suggest[15][40];
				printf("nhap tu can goi y:\n"); gets(word);
				int i,k;
				k=suggestion(soundexTree,word,suggest);
				if(k!=0)
				for(i=0;i<k;i++) printf("%s\n",suggest[i]);

			}break;
			case 2:{
				char result[100];
				int k;
				printf("nhap tu can dien du:\n"); gets(word);
				k=autoComplete(soundexTree,word,result);
				if(k!=0)
				printf("%s\n",result);
			}break;
			case 3: {
				btcls(Dic);
				btcls(soundexTree);
			}break;
		}
	}while(n!=3);
}
	





	
