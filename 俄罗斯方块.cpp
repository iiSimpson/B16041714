/*******************************/  
   /******Writer:   GJ      *******/  
   /******Language: C       *******/  
   /******Date:   2013 3 23 *******/  
   /*******************************/  
   #include<iostream>  
   #include<stdio.h>  
   //#include<conio.h>  
   #include<string.h>  
   #include<time.h>  
   #include<stdlib.h>  
   #include<windows.h>  
   using namespace std;  
   #define me(a) memset(a,0,sizeof(a))  
   #define judge(bl,ok) for(i=0;i<5;i++)if(bl[i].x&&map[bl[i].x][bl[i].y])ok=0  
   #define is_pure(node,ok) if(map[node.x][node.y])ok=0  
   const int HEIGHT=24,LENGTH=40,SIDE=22;  
   
   char INIT_MAP[HEIGHT+1][LENGTH+1];  
   int map[HEIGHT][SIDE];  
   struct node{int x,y;int color;};  
   const int TIME_DWELL=1000;  
   int state=0;  
   
   /**********获取句柄**********/  
   HANDLE Output=GetStdHandle(STD_OUTPUT_HANDLE);  
   HANDLE Input=GetStdHandle(STD_INPUT_HANDLE);  
   
   /**********设置光标位置**********/  
   void SetCursor(int x,int y){  
       COORD cd={x,y};  
       SetConsoleCursorPosition(Output,cd);  
   }  
   
   /**************初始化图**************/  
   void INITMAP()  
   {  
       for(int i=0;i<HEIGHT;i++)  
           for(int j=0;j<SIDE;j++){  
               if(i==0||i==HEIGHT-1||j==0||j==SIDE-1)map[i][j]=1;  
               else map[i][j]=0;  
           }  
   }  
   
   /********右上方提前显示方块******/  
   node bl[5];  
   void Former_Print_block(int n)  
   {  
       int i;  
       for(i=0;i<5;i++){bl[i].x=bl[i].y=0;}  
       if(n==0){  
           bl[0].x=3,bl[0].y=28;  bl[1].x=3,bl[1].y=30;  
           bl[2].x=4,bl[2].y=30;  bl[3].x=4,bl[3].y=32;  
       }  
       if(n==1){  
           bl[0].x=3,bl[0].y=32;  bl[1].x=3,bl[1].y=30;  
           bl[2].x=4,bl[2].y=30;  bl[3].x=4,bl[3].y=28;  
       }  
       if(n==2){  
           bl[0].x=3,bl[0].y=30;  bl[1].x=4,bl[1].y=28;  
           bl[2].x=4,bl[2].y=30;  bl[3].x=4,bl[3].y=32;  
       }  
       if(n==3){  
           bl[0].x=3,bl[0].y=27;   bl[1].x=3,bl[1].y=29;  
           bl[2].x=3,bl[2].y=31;  bl[3].x=3,bl[3].y=33;  
       }  
       if(n==4){  
           bl[0].x=3,bl[0].y=29;  bl[1].x=3,bl[1].y=31;  
           bl[2].x=4,bl[2].y=29;  bl[3].x=4,bl[3].y=31;  
       }  
       if(n==5){  
           bl[0].x=3,bl[0].y=28;  bl[1].x=4,bl[1].y=28;  
           bl[2].x=4,bl[2].y=30;  bl[3].x=4,bl[3].y=32;  
       }  
       if(n==6){  
           bl[0].x=3,bl[0].y=32;  bl[1].x=4,bl[1].y=28;  
           bl[2].x=4,bl[2].y=30;  bl[3].x=4,bl[3].y=32;  
       }  
       for(i=0;i<5;i++){  
           SetCursor(bl[i].y,bl[i].x);  
           printf("■");  
       }  
   }  
   
   /*********获取不同的方块,出现在中间***********/  
   node block[5];//全局使用的核心!!!  
   void print_block(int n)  
   {int i;  
       for(i=0;i<5;i++){block[i].x=block[i].y=0;}  
       if(n==0){  
           block[0].x=1,block[0].y=7;   block[1].x=1,block[1].y=9;  
           block[2].x=2,block[2].y=9;  block[3].x=2,block[3].y=11;  
       }  
       if(n==1){  
           block[0].x=1,block[0].y=11;  block[1].x=1,block[1].y=9;  
           block[2].x=2,block[2].y=9;  block[3].x=2,block[3].y=7;  
       }  
       if(n==2){  
           block[0].x=1,block[0].y=9;  block[1].x=2,block[1].y=7;  
           block[2].x=2,block[2].y=9;  block[3].x=2,block[3].y=11;  
       }  
       if(n==3){  
           block[0].x=1,block[0].y=7;   block[1].x=1,block[1].y=9;  
           block[2].x=1,block[2].y=11;  block[3].x=1,block[3].y=13;  
       }  
       if(n==4){  
           block[0].x=1,block[0].y=9;  block[1].x=1,block[1].y=11;  
           block[2].x=2,block[2].y=9;  block[3].x=2,block[3].y=11;  
       }  
       if(n==5){  
           block[0].x=1,block[0].y=7;  block[1].x=2,block[1].y=7;  
           block[2].x=2,block[2].y=9;  block[3].x=2,block[3].y=11;  
       }  
       if(n==6){  
           block[0].x=1,block[0].y=11;  block[1].x=2,block[1].y=7;  
           block[2].x=2,block[2].y=9;  block[3].x=2,block[3].y=11;  
       }  
       for(i=0;i<5;i++){  
           SetCursor(block[i].y,block[i].x);  
           printf("■");  
       }  
   }  
   
   
   /*************按 上 键 旋转*************/  
   void Exchange(int m)  
   {  
       int i,ok=1;  
       node blo[5];  
       for(i=0;i<5;i++)blo[i]=block[i];  
       if(m==0){  
           if(state==0){  
               blo[0].x+=1;blo[0].y+=2;blo[2].x-=1;blo[2].y+=2;blo[3].x-=2;  
               judge(blo,ok);  
               if(map[blo[0].x][blo[0].y-2])ok=0;  
               if(ok){for(i=0;i<5;i++)block[i]=blo[i];state=1;}  
           }  
           else{  
               blo[0].x-=1;blo[0].y-=2;blo[2].x+=1;blo[2].y-=2;blo[3].x+=2;  
               judge(blo,ok);  
               if(map[blo[1].x-1][blo[1].y])ok=0;  
               if(ok){for(i=0;i<5;i++)block[i]=blo[i];state=0;}  
           }  
       }  
       else if(m==1){  
           if(state==0){  
               blo[0].x-=1;blo[0].y-=2;blo[2].x-=1;blo[2].y+=2;blo[3].y+=4;  
               judge(blo,ok);  
               if(map[blo[1].x][blo[1].y-2])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=1;}  
           }  
           else {  
               blo[0].x+=1;blo[0].y+=2;blo[2].x+=1;blo[2].y-=2;blo[3].y-=4;  
               judge(blo,ok);  
               if(map[blo[0].x-1][blo[0].y])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=0;}  
           }  
       }  
       else if(m==2)  
       {  
           if(state==0)  
           {  
               blo[0].x+=1;blo[0].y-=2; blo[1].x+=1;blo[1].y+=2;blo[3].x-=1;blo[3].y-=2;  
               judge(blo,ok);  
               if(map[blo[0].x+1][blo[0].y]||map[blo[0].x-1][block[0].y]||map[blo[3].x][blo[3].y+2])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=1;}  
           }  
           else if(state==1)  
           {  
               blo[0].x+=1;blo[0].y+=2; blo[1].x-=1;blo[1].y+=2;blo[3].x+=1;blo[3].y-=2;  
               judge(blo,ok);  
               if(map[blo[0].x][blo[0].y+2]||map[blo[0].x][blo[0].y-2]||map[blo[3].x-1][blo[3].y])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=2;}  
           }  
           else if(state==2)  
           {  
               blo[0].x-=1;blo[0].y+=2; blo[1].x-=1;blo[1].y-=2;blo[3].x+=1;blo[3].y+=2;  
               judge(blo,ok);  
               if(map[blo[0].x+1][blo[0].y]||map[blo[0].x-1][blo[0].y]||map[blo[3].x][blo[3].y-2])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=3;}  
           }  
           else{  
               blo[0].x-=1;blo[0].y-=2; blo[1].x+=1;blo[1].y-=2;blo[3].x-=1;blo[3].y+=2;  
               judge(blo,ok);  
               if(map[blo[0].x][blo[0].y+2]||map[blo[0].x][blo[0].y-2]||map[blo[3].x+1][blo[1].y])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=0;}  
           }  
       }  
       else if(m==3)  
       {  
           if(state==0){  
               blo[0].x+=1;blo[0].y+=2;blo[2].x-=1;blo[2].y-=2;blo[3].x-=2;blo[3].y-=4;  
               judge(blo,ok);  
               if(map[blo[0].x][blo[0].y-2]||map[blo[2].x][blo[2].y+2])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=1;}  
           }  
           else {  
               blo[0].x-=1;blo[0].y-=2;blo[2].x+=1;blo[2].y+=2;blo[3].x+=2;blo[3].y+=4;  
               judge(blo,ok);  
               if(map[blo[0].x+1][blo[0].y]||map[blo[2].x-1][blo[2].y])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=0;}  
           }  
       }  
       else if(m==5)  
       {  
           if(state==0)  
           {  
               blo[0].x+=2;blo[1].x+=1;blo[1].y+=2;blo[3].x-=1;blo[3].y-=2;  
               judge(blo,ok);  
               if(map[blo[3].x][blo[3].y+2])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=1;}  
           }  
           else if(state==1)  
           {  
               blo[0].y+=4;blo[1].x-=1;blo[1].y+=2;blo[3].x+=1;blo[3].y-=2;  
               judge(blo,ok);  
               if(map[blo[3].x-1][blo[3].y])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=2;}  
           }  
           else if(state==2)  
           {  
               blo[0].x-=2;blo[1].x-=1;blo[1].y-=2;blo[3].x+=1;blo[3].y+=2;  
               judge(blo,ok);  
               if(map[blo[3].x][blo[3].y-2])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=3;}  
           }  
           else{  
               blo[0].y-=4;blo[1].x+=1;blo[1].y-=2;blo[3].x-=1;blo[3].y+=2;  
               judge(blo,ok);  
               if(map[blo[3].x+1][blo[3].y])ok=0;  
               if(ok)for(i=0;i<5;i++){block[i]=blo[i];state=0;}  
           }  
       }  
       else if(m==6)  
       {  
           if(state==0)  
           {  
               blo[0].y-=4;blo[1].x+=1;blo[1].y+=2;blo[3].x-=1;blo[3].y-=2;  
               judge(blo,ok);  
               if(map[blo[1].x][blo[1].y-2])ok=0;  
               if(ok){for(i=0;i<5;i++)block[i]=blo[i];state=1;}  
           }  
           else if(state==1)  
           {  
               blo[0].x+=2;blo[1].x-=1;blo[1].y+=2;blo[3].x+=1;blo[3].y-=2;  
               judge(blo,ok);  
               if(map[blo[1].x+1][blo[1].y])ok=0;  
               if(ok){for(i=0;i<5;i++)block[i]=blo[i];state=2;}  
           }  
           else if(state==2)  
           {  
               blo[0].y+=4;blo[1].x-=1;blo[1].y-=2;blo[3].x+=1;blo[3].y+=2;  
               judge(blo,ok);  
               if(map[blo[1].x][blo[1].y+2])ok=0;  
               if(ok){for(i=0;i<5;i++)block[i]=blo[i];state=3;}  
           }  
           else{  
               blo[0].x-=2;blo[1].x+=1;blo[1].y-=2;blo[3].x-=1;blo[3].y+=2;  
               judge(blo,ok);  
               if(map[blo[1].x-1][blo[1].y])ok=0;  
               if(ok){for(i=0;i<5;i++)block[i]=blo[i];state=0;}  
           }  
       }  
   }  
   
   /*********清除当前方块**********/  
   void clear_cube(node* block)  
   {  
       for(int i=0;i<5;i++){  
           if(block[i].x){  
           SetCursor(block[i].y,block[i].x);  
           printf("  ");}  
       }  
   }  
   
   /*******打印当前方块*********/  
   void printt_cube(node* block)  
   {  
       for(int i=0;i<5;i++){  
           if(block[i].x){  
               SetCursor(block[i].y,block[i].x);  
               printf("■");  
           }  
       }  
   }  
   
   /**********按键***********/  
   void Move(int m,int n){  
       int i;  
       if(n==0){//左  
           for(i=0;i<5&&block[i].x;i++)if(block[i].y)block[i].y-=2;  
       }  
       if(n==1){//右  
           for(i=0;i<5&&block[i].x;i++)if(block[i].y)block[i].y+=2;  
       }  
       if(n==2)//上  
       {  
           Exchange(m);  
       }  
       if(n==3)//下  
       {  
           int ok=1;  
           while(ok){  
               for(i=0;i<5;i++)if(block[i].x)  
                   if(map[block[i].x+1][block[i].y])ok=0;  
               if(ok)for(i=0;i<5;i++)if(block[i].x)  
                   block[i].x+=1;  
           }  
       }  
   }  
   
   /******判断是否可以向左移动*****/  
   int If_Can_Left(node* block)  
   {  
       int ok=1,i;  
       int min=22;  
       for(i=0;i<5&&block[i].x;i++)if(block[i].y<min)min=block[i].y;  
       if(min-2<1)ok=0;  
       for(i=0;i<5&&block[i].x;i++)if(block[i].x)  
           if(map[block[i].x][block[i].y-2])ok=0;  
       return ok;  
   }  
   
   /******判断是否可以向右移动********/  
   int If_Can_Right(node* block)  
   {  
       int ok=1,i;  
       int max=0;  
       for(i=0;i<5&&block[i].x;i++)if(block[i].y>max)max=block[i].y;  
       if(max+2>19)ok=0;  
       for(i=0;i<5&&block[i].x;i++)if(block[i].x)  
           if(map[block[i].x][block[i].y+2])ok=0;  
       return ok;  
   }  
   
   /*********打印图**********/  
   void print_map()  
   {  
       int i,j;  
       me(INIT_MAP);  
       for(i=0;i<HEIGHT;i++)  
       {  
           if(i==0||i==23){  
               for(j=0;j<LENGTH;j++)printf("%c",INIT_MAP[i][j]='-');  
           }  
           else{  
               printf("%c",INIT_MAP[i][0]='|');  
               for(j=1;j<SIDE-1;j++)printf("%c",INIT_MAP[i][j]=' ');  
               printf("%c%c",INIT_MAP[i][j++]='|',INIT_MAP[i][j++]='|');  
               for(;j<LENGTH-1;j++)printf("%c",INIT_MAP[i][j]=' ');  
               printf("%c",INIT_MAP[i][j]='|');  
           }  
           cout<<endl;  
       }  
       SetCursor(SIDE+1,10);  
       printf("================");  
       SetCursor(SIDE+1,11);  
       printf("Speed");  
       SetCursor(SIDE+1,13);  
       printf("================");  
       SetCursor(SIDE+1,14);  
       printf("Score");  
       SetCursor(SIDE+1,16);  
       printf("================");  
       SetCursor(SIDE+1,19);  
       printf("   Created By   ");  
       SetCursor(SIDE+1,20);  
       printf("   Gong Jing    ");  
   }  
   
   /*******下降一格*******/  
   void cube_drop(node *block)  
   {  
       int i;  
       for(i=0;i<5;i++)if(block[i].x)  
           block[i].x+=1;  
   }  
   
   /*****到达底部返回1*******/  
   int is_at_botton(node* block)  
   {  
       for(int i=0;i<5;i++)  
           if(block[i].x&&map[block[i].x+1][block[i].y])return 1;  
       return 0;  
   }  
   
   /******到达底部map赋值为1*****/  
   void print_map(node *block)  
   {  
       int i;  
       for(i=0;i<5;i++){  
           if(block[i].x){  
               map[block[i].x][block[i].y]=1;  
               SetCursor(block[i].y,block[i].x);  
               printf("■");  
           }  
       }  
   }  
   
   /******是否可以消去并消去**********/  
   int Can_It_Cut()  
   {  
       int i,j;  
       int cut=0;  
       for(i=HEIGHT-2;i>1;i--){  
           int ok=1;  
           for(j=1;j<SIDE-1;j+=2)  
               if(map[i][j]==0){ok=0;break;}  
           if(ok){  
               for(j=i;j>1;j--)for(int k=1;k<SIDE-1;k+=2)  
                   map[j][k]=map[j-1][k];  
               cut++;i++;  
           }  
       }  
       for(i=HEIGHT-2;i>1;i--)  
           for(int j=1;j<SIDE-1;j+=2)  
           {  
               SetCursor(j,i);  
               if(map[i][j])printf("■");  
               else printf("  ");  
           }  
       return cut;  
   }  
   
   
   /********是否GameOver********/  
   int is_gameover(int num)  
   {  
       int i,j,ok=1;  
       print_block(num);  
       for(i=0;i<5;i++)if(block[i].x&&map[block[i].x][block[i].y])ok=0;  
       if(!ok){  
           char aa[20]={"Game Over!!!"};  
           for(i=9;i<12;i++)  
           {  
               if(i==10){  
                   int t=0;  
                   for(int j=4;j<18;j++){  
                       SetCursor(j,i);  
                       if(j>=5&&j<17)printf("%c",aa[t++]);  
                       else printf(" ");  
                   }  
               }  
               else for(j=4;j<18;j++){  
                       SetCursor(j,i);  
                       printf(" ");  
               }  
           }  
           SetCursor(1,12);printf(" Enter To Continue. ");  
           SetCursor(1,13);printf("    Esc To Escape.  ");  
           SetCursor(1,14);printf("                    ");  
       }  
       return ok;  
   }  
   
   /*******游戏结束，再来一局，清理屏幕******/  
   void Clear_map()  
   {  
       for(int i=22;i>0;i--)  
           for(int j=1;j<SIDE-1;j+=2)  
           {  
               map[i][j]=0;  
               SetCursor(j,i);  
               printf("  ");  
           }  
   }  
   
   int main()  
   {  
       srand(time(NULL));  
       print_map();  
       INITMAP();  
       int gameover=1;  
       int ok=1;//用于判断游戏是否结束  
       while(gameover){  
           int Score=0;  
           int Speed=0;  
            int numm=(rand()%7)*(rand()%7)%7;  
            Sleep(TIME_DWELL);  
           while(ok)  
           {  
               SetCursor(SIDE+4+Speed,12);  
               printf("     ");  
               SetCursor(SIDE+4,15);  
               printf("     ");  
               SetCursor(SIDE+4+Speed,12);  
               printf("*");  
               SetCursor(SIDE+4,15);  
               printf("%d",Score);  
               Sleep(200);  
               int num=numm;        //第num个方块，初始时为0这个状态  
               numm=(rand()%7)*(rand()%7)%7;               //提前显示的方块  
               clear_cube(bl);  
               Former_Print_block(numm);    //打印提前显示的方块  
               print_block(num);             //打印要落下的方块初始位置  
               state=0;  
               int botton=1;//用于判断是否已经落到底部  
               while(botton)  
               {  
                   clear_cube(block);  
                    /**********键位响应**********/  
                    if(GetAsyncKeyState(VK_LEFT)&&If_Can_Left(block))Move(num,0);  
                    else if(GetAsyncKeyState(VK_RIGHT)&&If_Can_Right(block))Move(num,1);  
                    else if(GetAsyncKeyState(VK_UP))Move(num,2);  
                    else if(GetAsyncKeyState(VK_DOWN)){Move(num,3);botton=0;}  
   
                   if(!is_at_botton(block))cube_drop(block);  
                   else botton=0;  
                   printt_cube(block);//打印当前方块  
                   if(!botton)print_map( block);  
                   Sleep(100*(4-Score/80));  
               }  
               int cut=Can_It_Cut();  
               if(cut){  
                   Score+=cut*10;  
                   Speed=Score/80;  
               }  
               ok=is_gameover(numm);  
           }  
           if(GetAsyncKeyState(VK_ESCAPE))gameover=0;  
           else if(GetAsyncKeyState(VK_RETURN)){Clear_map();ok=1;}  
       }  
       return 0;  
   } 
