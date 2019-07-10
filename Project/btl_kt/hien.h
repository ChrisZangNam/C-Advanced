
//#include"viet2.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "btree.h"
#include"soundex.h"

//			*** HAM CUA HIEN ***

// tao cay soundex
void creatSoundexTree(BTA *Dic, BTA **soundexTree){
	char en[40],vi[100000];
	int rsize,i=0;
	char soundex[5];
	*soundexTree=btcrt("soundexTree",0,0);
	btsel(Dic,"",vi,100000*sizeof(char),&rsize);
	while(btseln(Dic,en,vi,100000*sizeof(char),&rsize)==0){
		SoundEx(soundex,en,4,1);
		btins(*soundexTree,en,soundex,5*sizeof(char));
		i++;
	}
	g_print("da them %d vao soundexTree\n",i);
}


// in ra cay soundex
void printSoundexTree(BTA *soundexTree){
	char en[40],soundex[5];
	int rsize;
	int i=0;
	btsel(soundexTree,"",soundex,5*sizeof(char),&rsize); //printf("1\n");
	while(btseln(soundexTree,en,soundex,5*sizeof(char),&rsize)==0){
		printf("%s\n%s\n",en,soundex);
	}
}
//in cay tu dien
void printDic(BTA *Dic){
	char en[40],mean[100000];
	int rsize;
	int i=0;
	//Dic=btopn("data",0,0);
	btsel(Dic,"",mean,100000*sizeof(char),&rsize); //printf("1\n");
	while(btseln(Dic,en,mean,100000*sizeof(char),&rsize)==0){
		printf("%s\n%s\n",en,mean);
	}
	//btcls(Dic);
}

int suggestion(BTA *soundexTree, char *word, char s[][100]){
	int rsize,i=0;
	char en[40],soundex[5],code[5];
	SoundEx(code,word,4,1);
	btsel(soundexTree,"",soundex,5*sizeof(char),&rsize);
	while(btseln(soundexTree,en,soundex,5*sizeof(char),&rsize)==0 && i<49){
		if(strcmp(code,soundex)==0)
			//printf("%s\n",en);
			strcpy(s[i++],en);
			// xu li luu xau en chua tu co cung ma soundex
	}
	return i;
}

// kiem tra s1 co trong phan dau cua s2 hay khong
int replace(char *s1, char *s2){
	int len1=strlen(s1);
	int len2=strlen(s2),i;
	if(len1>len2) return 0;
	else{
		for(i=0;i<len1;i++){
			if(s1[i]!=s2[i])
				return 0;
		}
	}
	return 1;
}

// tim kiem tu complete, luu trong xau result,
//tra ve 1 neu thanh cong, 0 neu that bai
int autoComplete(BTA *soundexTree, char *word, char *result){
	int len1=strlen(word);
	int rsize;
	char en[40], soundex[5];
	btsel(soundexTree,"",soundex,5*sizeof(char),&rsize);
	while(btseln(soundexTree,en,soundex,5*sizeof(char),&rsize)==0){
		if(replace(word,en)==1){
			strcpy(result,en);
			return 1;
		}
	}
	return 0;
}


