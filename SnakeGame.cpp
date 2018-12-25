#include<bits/stdc++.h>
#include<conio.h>
#define bou 26
using namespace std;
char ch='d';

struct  food {
  int row,col;
  char data;
};

struct mysnake{
int row,col;
char data;
struct mysnake * next;
};



//boundary making
void boundry(char arr[bou][bou]){
for(int i=0;i<bou;i++){
    for(int j=0;j<bou;j++){
        if(i==0||j==0||i==bou-1||j==bou-1)
            arr[i][j]='*';
        else
            arr[i][j]=' ';
    }
}
}

//printing mysnake
void print(struct mysnake *head,char arr[bou][bou],int score){
    struct mysnake *copy1=head;

    while(copy1!=NULL){
        arr[copy1->row][copy1->col]=copy1->data;
        copy1=copy1->next;
    }
    for(int i=0;i<bou;i++){
        for(int j=0;j<bou;j++){
            cout<<arr[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"score->"<<score<<endl;
    cout<<"Press e For Save And q For Quit"<<endl;
}

//initial mysnake
struct mysnake *snakeatstart(struct mysnake * head,char arr[bou][bou]){
struct mysnake *newnode;
struct mysnake *copy1=head;
int r,c;
r=12;
c=14;
for(int i=0;i<6;i++){
    newnode=new mysnake;
    newnode->data='*';
    newnode->next=NULL;
    newnode->row=r;
    newnode->col=c;
    c--;
    if(head==NULL){
        head=newnode;
        newnode->data='&';
    }
    else{
            copy1=head;
        while(copy1->next!=NULL){
            copy1=copy1->next;
        }
        copy1->next=newnode;
    }
}
return head;
};


//generatefood
void generatefood(mysnake *head,char arr[bou][bou],struct food *f){
struct mysnake *copy1=head;
int flag=1;
while(flag){
    f->row=rand()%(24-1+1)+1;
    f->col=rand()%(24-1+1)+1;
    copy1=head;
    while(copy1!=NULL){
        if(copy1->row!=f->row&&copy1->col!=f->col){
            flag=0;
        }
        else{
            flag=1;
            break;
        }
        copy1=copy1->next;
    }
}
f->data='O';
arr[f->row][f->col]=f->data;
}

//actual movement
void shift(mysnake *head,int r,int c,char arr[bou][bou]){
struct mysnake *copy1=head,*copy2=head;
int r1,r2,c1,c2;
r1=copy1->row;
c1=copy1->col;
while(copy2->next!=NULL){
    copy2=copy2->next;
}
arr[copy2->row][copy2->col]=' ';
while(copy1->next!=NULL){
    copy1=copy1->next;
    r2=copy1->row;
    c2=copy1->col;
    copy1->row=r1;
    copy1->col=c1;
    r1=r2;
    c1=c2;
}
head->row=r;
head->col=c;
}

//keymovement
int movement(mysnake *head,char arr[bou][bou],char &curr,char &prev){
    struct mysnake *copy1;
    int r,c;
    copy1=head;


if(curr=='d'&&prev!='a'){
    if(copy1->col==bou-2){
        r=copy1->row;
        c=1;
    }
    else{
        r=copy1->row;
        c=copy1->col+1;
    }
    shift(head,r,c,arr);
}

else if(curr=='s'&&prev!='w'){
    if(copy1->row==bou-2){
        r=1;
        c=copy1->col;
    }
    else{
        r=copy1->row+1;
        c=copy1->col;
    }
    shift(head,r,c,arr);
}

else if(curr=='a'&&prev!='d'){
    if(copy1->col==1){
        r=copy1->row;
        c=bou-2;
    }
    else{
        r=copy1->row;
        c=copy1->col-1;
    }
    shift(head,r,c,arr);
}

else if(curr=='w'&&prev!='s'){
    if(copy1->row==1){
        r=bou-2;
        c=copy1->col;
    }
    else{
        r=copy1->row-1;
        c=copy1->col;
    }
    shift(head,r,c,arr);
}

//dont stop if opposite key is pressed
//------------------------------------------------
else if (curr=='d'&&prev=='a'){
  if(copy1->col==1){
      r=copy1->row;
      c=bou-2;
  }
  else{
      r=copy1->row;
      c=copy1->col-1;
  }
  shift(head,r,c,arr);
//changing prev and curr
  curr=prev;
  prev='s';
    }

else if(curr=='s'&&prev=='w'){
  if(copy1->row==1){
      r=bou-2;
      c=copy1->col;
  }
  else{
      r=copy1->row-1;
      c=copy1->col;
  }
  shift(head,r,c,arr);
  curr=prev;
  prev='a';
}

else if(curr=='a'&&prev=='d'){
  if(copy1->col==bou-2){
      r=copy1->row;
      c=1;
  }
  else{
      r=copy1->row;
      c=copy1->col+1;
  }
  shift(head,r,c,arr);
  curr=prev;
  prev='w';
}

else if(curr=='w'&&prev=='s'){

    if(copy1->row==bou-2){
        r=1;
        c=copy1->col;
    }
    else{
        r=copy1->row+1;
        c=copy1->col;
    }
    shift(head,r,c,arr);
    curr=prev;
    prev='d';
}
//--------------------------------------------------
else if(curr=='e'){
	return 1;
}


else if (curr=='q'){
  return 2;
}
};


// bc mysnake na apna aap ko to nahi kha liya
int checkingsnakeeatingitself(struct mysnake *head){
int flag=1;
struct mysnake *copy1=head->next;
while(copy1!=NULL){
    if(head->row ==copy1->row&&head->col==copy1->col){
        flag=0;
        break;
    }
    copy1=copy1->next;
}
return flag;
}


// kya mysnake ka head ..food pr to nahi aa gaya
int saapkasirequaltofood(struct mysnake *head,struct food *f){
int flag=0;
if(head->row==f->row&&head->col==f->col){
        flag=1;
    }
return flag;
}


//saap na khana kha lia
struct mysnake* bhukhasaapnakhanakhaliya(mysnake *head,char arr[bou][bou],struct food *f){
struct mysnake *copy1=head,*newnode;

newnode=new mysnake;
newnode->data='^';
newnode->row=f->row;
newnode->col=f->col;
newnode->next=NULL;
while(copy1->next!=NULL){
    copy1=copy1->next;
}
copy1->next=newnode;
return head;
}


//insertion for resume function
struct mysnake* insertion(struct mysnake *head,int r,int c,int data)
{
           struct mysnake *ptr,*n;
        ptr=head;
        n=new mysnake;
        n->row=r;
        n->col=c;
        n->data=data;
        n->next=NULL;
       if(head==NULL)
        {
       head=n;
       head->next=NULL;
        }
        else
        {
       ptr=head;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=n;
        ptr=ptr->next;
        }
   return head;
}




//resume function
struct mysnake *resume(struct mysnake *head,char arr[bou][bou],struct food *f,int &score){
  FILE *fp,*fp1,*fp2;
  fp=fopen("ssnake.txt","r");
  fp1=fopen("food.txt","r");
  fp2=fopen("score.txt","r");

 if(fp==NULL){
    cout<<"Sorry no save game please head game again"<<endl;
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    return NULL;
  }

{
  //snake resume
  char ch,s;
  int a,b;
  ch=fgetc(fp);
  while(ch!=EOF)
    {
      if(ch!='/'){
        a=ch-'0';
        ch=fgetc(fp);
        b=ch-'0';
        ch=fgetc(fp);
        s=ch;
        head=insertion(head,a,b,s);
      }
      ch=fgetc(fp);
    }


    //food resume
    char ch1;
    ch1=fgetc(fp1);
    while(ch1!=EOF)
    {
      f->row=ch1-'0';
      ch1=fgetc(fp1);
      f->col=ch1-'0';
      ch1=fgetc(fp1);
      f->data=ch1;
      arr[f->row][f->col]=f->data;
      ch1=fgetc(fp1);
    }

    //score resume
    score=fgetc(fp2)-'0';

    fclose(fp);
    fclose(fp1);
    fclose(fp2);
  }
  return head;
}


//starting option
struct mysnake * option(struct mysnake *head,char mat[bou][bou],struct food *f,int &score){
	int st;
cout<<"Press 1 For Start New Game"<<endl;
cout<<"Press 2 For Resume Game"<<endl;
cin>>st;
if(st==1){
boundry(mat);
head=snakeatstart(head,mat);
generatefood(head,mat,f);
	return head;
}
else if(st==2){
  boundry(mat);
  head=resume(head,mat,f,score);
	if(head==NULL){
  option(head,mat,f,score);
}
  else{
  return head;
}
}
else{
cout<<"Invalid Number Entered"<<endl;
option(head,mat,f,score);
}
}



//save and quit
void save(struct mysnake *head,struct food *f,int s){
	FILE *fp,*fp1,*fp2;
  fp=fopen("ssnake.txt","w");
  fp1=fopen("food.txt","w");
  fp2=fopen("score.txt","w");
  struct mysnake *copy1=head;

  while(copy1!=NULL)
    {
      fputc(copy1->row+'0',fp);
      fputc(copy1->col+'0',fp);
      fputc(copy1->data,fp);
      fputc('/',fp);
      copy1=copy1->next;
    }

    fputc(f->row+'0',fp1);
    fputc(f->col+'0',fp1);
    fputc(f->data,fp1);

    fputc(s+'0',fp2);

fclose(fp);
fclose(fp1);
fclose(fp2);
}

int main(){
struct mysnake *head=NULL;
struct food *f,z;
f=&z;
char mat[bou][bou];
int score =0;
char prech='w';
head=option(head,mat,f,score);
print(head,mat,score);

while(1){
	for(int i=0;i<100000000;i++);
  if(saapkasirequaltofood(head,f)){
    bhukhasaapnakhanakhaliya(head,mat,f);
    generatefood(head,mat,f);
    score=score+1;
  }
  int a=movement(head,mat,ch,prech);
  if(a==1){
    save(head,f,score);
		return 0;
  }
  if(a==2){
    remove("ssnake.txt");
    remove("score.txt");
    remove("food.txt");
    return 0;
  }

  if(kbhit()){
    prech=ch;
            ch=getch();
            //scanf("%c",&ch);
            //while(getchar()!='\n');
		}
    int b=checkingsnakeeatingitself(head);
    if(b==0){
      remove("ssnake.txt");
      remove("score.txt");
      remove("food.txt");
      cout<<"Game Over";
        break;
    }

    system("CLS");
    print(head,mat,score);
}
}
