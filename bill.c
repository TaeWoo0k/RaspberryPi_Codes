
#include<stdio.h>

 

#include<wiringPi.h>

 

#include<lcd.h>

 

#include<unistd.h>

 

#include<termio.h>

 

int getch(void)

 

{

 

   int c;

 

   struct termios oldattr,newattr;

 

   

 

   tcgetattr(STDIN_FILENO,&oldattr);

 

   newattr=oldattr;

 

   newattr.c_lflag&=~(ICANON|ECHO);

 

   newattr.c_cc[VMIN]=1;

 

   newattr.c_cc[VTIME]=0;

 

   tcsetattr(STDIN_FILENO,TCSANOW,&newattr);

 

   c=getchar();

 

   tcsetattr(STDIN_FILENO,TCSANOW,&oldattr);

 

   return c;

 

}

 

int main(void)

 

{

 

int disp1;

 

int i=0,j=1,k=0;

 

char input;

 

char str[6][16]={"1.Onion$2x2=$4","2.Beef$10x1=$10","3.Pizza$5x1=$5","4.Coke$2x3=$6","5.Potato$3x1=$3","6.Total=$28"};

 

if(wiringPiSetupGpio()==-1)

 

  return -1;

 

  disp1=lcdInit(2,16,4,17,4,6,13,19,26,12,16,20,21);

 

lcdClear(disp1);

 

for(k=0;k<6;k++)

 

{

 

   printf("%s\n",str[k]);

 

}

 

     lcdPosition(disp1,0,0);

 

   lcdPuts(disp1,str[i]);

 

   lcdPosition(disp1,0,1);

 

   lcdPuts(disp1,str[j]);

 

  while(1)

 

  {

 

     input=getch();

 

   

 

   

 

       

 

     if(input==65)

 

   {

 

    

 

        if(i==5)

 

        i=0;

 

        else

 

        i++;

 

        if(j==5)

 

        j=0;

 

        else

 

        j++;

 

     }

 

     if(input==66)

 

     {

 

        if(i==0)

 

        i=5;

 

        else

 

        i--;

 

        if(j==0)

 

        j=5;

 

        else

 

        j--;

 

        

 

     }

 

  

 

  

 

  

 

     printf("%d %d\n",i,j);

 

     printf("%s %s",str[i],str[j]);

 

     lcdClear(disp1);

 

     lcdPosition(disp1,0,0);

 

   lcdPuts(disp1,str[i]);

 

   lcdPosition(disp1,0,1);

 

   lcdPuts(disp1,str[j]);

 

}

 

return 0;

 

  }


