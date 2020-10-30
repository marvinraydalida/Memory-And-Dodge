#include <graphics.h> //for graphics
#include <dos.h>      //for graphics
#include <stdlib.h>   //rand is here
#include <time.h>     //random and delay
#include <conio.h>    //used for kbhit
#include <stdio.h>    //for database
#include <string.h>   //for naming


//////////// MEMORY
int loop = 3;
int botMoves[1000];
int userMoves[1000];
int circleExes[9] = {148,308,468,148,308,468,148,308,468};
int circleWays[9] = {90,90,90,240,240,240,390,390,390};
                    //b   b    b    a    b    d   b     a    b    b    b    b    a    b    f    e    d    b
int introNotes[] = {145, 145, 145, 130, 145, 176, 145, 130, 145, 145, 145, 145, 130, 145, 207, 195, 176, 145};
int introNotesDelay[] = {200, 200, 170, 140, 200, 200, 170, 140, 190, 200, 200, 170, 140, 200, 200, 170, 140, 190};
int noteInterval[] =    {30 , 30 , 30 , 0  , 30 , 30 , 30 , 0  , 150, 30 , 30 , 30 , 0  , 30 , 30 , 30 , 0  , 190};
int gamePlayNotes[] = {275,275,333,333,415,415,333,415,275,275,333,333,415,415,333,415,275,275,311,311,333,333,311,275,275,275,311,311,333,333,311,275};
int TutorialNotes[] = {275,275,350,350,415,415,350,415,350,350,415,415,520,520,415,520,311,311,370,370,470,470,370,470,415,415,520,520,311,311,520,311};
int transitionX[4] = {-450,0,640,1090};
int topScores[10];
char mtopPlayers[10][15];
int key[9];
int keyCheck[] = {112,112,112,112,112,112,112,112,112};
char array[1000];
int value, stop = 0, finalScore = 0;
int yValue = 390;
int timeG = 0;
float topTime[10];

//////////// DODGE

int attackOn = 0;
int barHX[2];
int barHY[2];
int barVX[2] = {-500,-500};
int barVY[2] = {-500,-500};
int dodge = 0;
int greenDelay = 500;
int redDelay = 200;
int dodgeHighScore;
char name[15];
char topPlayer[15];
int nameLength;

      // circle(148,90,50);
      // circle(308,90,50);
      // circle(468,90,50);
      // circle(148,240,50);
      // circle(308,240,50);
      // circle(468,240,radius);
      // circle(148,390,50);
      // circle(308,390,50);
      // circle(468,390,50);

union REGS i, o;

void randomBar(int barPositionH, int barPositionV, int mode); //AFTER THE RANDOM POSITION IS GENERATED THIS FUNCTION IS USED TO GENERATE BAR DISPLAY.
void randomPosition(); //THIS FUNCTION GENERATES RANDOM NUMBERS AND USES RANDOM BAR TO DISPLAY RANDOM BAR AT THE SCREEN.

void chooseGame(int choice); //CHOOSE GAME IS THE FUNCTION USED WHEN CHOOSING 2 GAMES.

///// MOUSE FUNCTIONS
void showmouseptr();
void getmousepos(int *button, int *x, int *y);

void tutorialBox(); //FUNCTION THAT ASKS THE USER TO VIEW TUTORIAL OR NOT
void tutorial(); //TUTORIAL FUNCTION CONTAINS THE TUTORIAL
void draw(); //DISPLAY THE TUTORIAL WHEN THE SCREEN IS CLEARED
void animateTutorial(); //SIMPLE ANIMATION FUNCTION TO ANIMATE TUTORIAL BOX 
void keyAssignment(); //KEY ASSIGNMENT IS WHERE THE USER ASSIGN KEYS TO THE 9 CIRCLE IN MEMORY GAME

void paused(); //DOES NOT ACTUALLY PAUSE THE GAME BUT DISPLAY THE PAUSE BAR.
void createTimer(int dly); //LINE THAT GOES UP
void timerFixer(); //WHENEVER THE SCREEN IS CLEARED THIS FUNCTION FILLS THE REMOVED TIMER DISPLAY


void createCircle(int clicked, int radius); //CREATES THE 9 CIRCLES IN GAMEPLAY
void music(int pitch); //PRODUCES SOUND
void randomColor(int anongKulay); //WHENEVER THE BOT COLORS A CIRCLE IN MEMORY GAME THIS FUNCTIONS FILL THE CIRCLE WITH RANDOM COLOR
void bot(int level); //GIVES RANDOM NUMBER FROM 0 - 8 AND USES RANDOM COLOR, TO FILL CIRCLES WITH COLORS.
int getchConverter(int input, int rtrn); //GETCH CONVERTER CONVERTS INTEGER RETURN, FROM GETCH FUNCTION. WHENEVER THE USER PRESS SOMETHING WHEN PLAYING GETCH CONVERTER IS USED.
void score(int rawScore); //SCORE FUNCTION FOR MEMORY GAME WHERE LOOP IS MULTIPLIED TO THE RAW SCORE OR THE RIGHT ANSWER OF THE USER.

///// DATABASE FUNCTIONS FOR MEMORY
void retrieveScore(); //USE TO RETRIEVE SCORE FROM THE TEXT DATABASE
void insertScore(int data, int i); //INSERTS THE RETRIEVED SCORES INTO AN ARRAY
void saveScore(); //THE SCORES ARRAY IS SAVED INTO THE TEXT DATABASE
void sort(); //CHECKS IF THE FINAL SCORE OF THE USER IS GREATER THAN ANY SCORE IN THE SCORES ARRAY AND SORTS IT FROM HIGHEST TO LOWEST
void retrieveTopPlayers();
void insertName();
void saveTopPlayers();
void retrieveTime();
void insertTime(float data, int i);
void saveTime();

///// DATABASE FUNCTIONS FOR DODGE

void retrieveHighScore();
void compare();
void saveHighScore();
void saveName();
void retrieveName();

///// TRANSITION EFFECTS FOR MEMORY
void menuTransition();
void loading();
void clearTransition();
void circleTransition();
void gameOverTransition(int num);



///// TRANSITION EFFECTS FOR DODGE
void dodgeTransition();
void dodgeLoading();
void dodgeStarting();
void dodgeGameOverTransition();

void main(){

	int gd = DETECT, gm;
	int button, x, y, inputPause, btn, ex, way;
	int i = 0, j, input, start = 0, restart = 0, rawScore = 0, dly = 14, pause = 0, viewTutorial = -1, note , exitGame = 0, game, go = 0;
  //int n = 100;
  clrscr();
	initgraph(&gd,&gm,"c:\\TURBOC3\\\BGI");
  srand(time(NULL));


  while(exitGame == 0){
    chooseGame(1);
    game = 1;  
    restart = 0;
    note = 0;

    while(1){
      i = getch();

      if (i == 72){
        sound(800);
        delay(50);
        sound(1000);
        delay(100);
        nosound();
        chooseGame(1);
        game = 1;
      }
      else if (i == 80){
        sound(800);
        delay(50);
        sound(1000);
        delay(100);
        nosound();
        chooseGame(2);
        game = 2;
      }
        
      else if (i == 13){
        sound(1000);
        delay(50);
        sound(1800);
        delay(100);
        nosound();
        break;
      }
      else if (i == 27){
        exitGame = 1;
        break;
      }

    }

    cleardevice();
    delay(500);

    if(game == 2 && exitGame == 0){
      dodgeTransition();
      while(!kbhit()){
          sound(gamePlayNotes[note]);
          delay(100);
          nosound();
          note++;
          if(note == 32)
            note = 0;
      }
      getch();
      note = 0;

      closegraph();
      
      while(1){
        gotoxy(21,8);
        printf("Enter your name (maximum of 10 letters no space");
        _setcursortype(_SOLIDCURSOR);
        gotoxy(32,10);
        scanf("%s",&name);

        nameLength = strlen(name);

        if (nameLength <= 10){
           break;
        }
        else
          clrscr();
      }

      initgraph(&gd,&gm,"c:\\TURBOC3\\\BGI");

      cleardevice();

      dodgeLoading();

      cleardevice();
      
      while(kbhit()){ // This loop catches excess key pressed
          getch();
      }

      while(!kbhit()){
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(20,240,"P R E S S  A N Y  K E Y...");
      }
      getch();

      cleardevice();

      showmouseptr();

      getmousepos(&btn,&ex,&way);
      while(1){
        while(kbhit()){ // This loop catches excess key pressed
          getch();
        }
        dodgeStarting();
        while(kbhit()){ // This loop catches excess key pressed
          getch();
        }
        while(go != 1){
   
          randomPosition();
          getmousepos(&btn,&ex,&way);
          if(attackOn == 1 && (((ex >= barHX[0] && ex <= barHX[1]) && (way >= barHY[0] && way <= barHY[1])) || ((ex >= barVX[0] && ex <= barVX[1]) && (way >= barVY[0] && way <= barVY[1])))){
            go = 1;
          }
          else
            dodge++;
          delay(redDelay - 50);
          cleardevice();
        }

        retrieveHighScore();
        retrieveName();
        compare();
        saveHighScore();
        saveName();
        dodgeGameOverTransition();
        j = getch();
        if (j == 27){
          go = 0;
          greenDelay = 500;
          redDelay = 200;
          dodge = 0;
          barVY[0] = -500;
          barVY[1] = -500;
          break;
        }
        go = 0;
        greenDelay = 500;
        redDelay = 200;
        dodge = 0;
        barVY[0] = -500;
        barVY[1] = -500;
        cleardevice();
      }
    }

    if(game == 1 && exitGame == 0){
      transitionX[0] = -450;
      transitionX[1] = 0;
      transitionX[2] = 640;
      transitionX[3] = 1090;
      i = 0;
      menuTransition();

      while(!kbhit()){
          sound(introNotes[i]);
          delay(introNotesDelay[i]);
          nosound();
          delay(noteInterval[i]);
          i++;
          if (i == 18)
            i = 0;
      }
      getch();

      start = 1;  

      for (i = 637; i > 0; i--){
        delay(1);
        line(i,1,i,479);
        sound(i);
      }

      nosound();

      cleardevice();

      setbkcolor(BLACK);

      tutorialBox();

      showmouseptr();
  

  
      while(!kbhit() || viewTutorial == -1){
        getmousepos(&btn,&ex,&way);
        if( btn == 1 && (ex >= 160 && ex <= 290) && (way >= 210 && way <= 280)){
          btn = 0;
          viewTutorial = 1;
          break;
        }

        else if( btn == 1 && (ex >= 365 && ex <= 495) && (way >= 210 && way <= 280)){
          btn = 0;
          viewTutorial = 0;
          break;
        }
      }

      cleardevice();

      while(kbhit()){ // This loop catches excess key pressed
        getch();
      }

      if (viewTutorial == 1)
          tutorial();


      if(viewTutorial == 0)
        keyAssignment();

      while(kbhit()){ // This loop catches excess key pressed
          getch();
      }

      viewTutorial = -1;

       closegraph();
      
      while(1){
        gotoxy(21,8);
        printf("Enter your name (maximum of 10 letters no space");
        _setcursortype(_SOLIDCURSOR);
        gotoxy(32,10);
        scanf("%s",&name);

        nameLength = strlen(name);

        if (nameLength <= 10){
           break;
        }
        else
          clrscr();
      }

      initgraph(&gd,&gm,"c:\\TURBOC3\\\BGI");

      loading();

      cleardevice();
    
  


      if(start == 1){

        while(restart == 0){
      
          delay(1000);
      
          circleTransition();

          cleardevice();

          while(1){
        
        
            createCircle(0,0);
            bot(loop);

            while(kbhit()){ // This loop catches excess key pressed
              getch();
            }



            for (i = 0; i < loop; i++){
              while(!kbhit()){
                createTimer(dly);
                if (yValue == 90) //yValue of 90 means times-out.
                  break;
                sound(gamePlayNotes[note]);
                delay(100);
                nosound();
                timeG += 100;
                note++;
                if(note == 32)
                  note = 0;
              }

              if(yValue > 90){
                input = getch();
                inputPause = input;
                i = getchConverter(input,i); //mag sesend ako ng i sa getch converter para sa else statement maging negative 1 value ni i kung pumindot ng ibang key
                timeG += 100;
                timerFixer();
                userMoves[i] = value;        //else statement meaning pag pumindot ako ng ibang key.
              }
          
              // sprintf(array,"%d", i);   //pag di pumasok sa else ganon parin value ni i 
              // outtextxy(100,100,array);
              // sprintf(array,"%d", userMoves[i]);
              // outtextxy(n,200,array);
              // n += 100;


              //PAUSE TRAP
              if (inputPause == 112){
                music(500);
                while(pause != 13){
                  paused();
                  pause = getch();
                }
                music(500);
                cleardevice();
                createCircle(0,0);
                pause = 0;
                inputPause = 0;
              }


              if (i >= 0){ 
                if (userMoves[i] != botMoves[i] || yValue == 90){
              

              
                  gameOverTransition(0);

                  score(rawScore);
                  retrieveScore();
                  retrieveTopPlayers();
                  retrieveTime();
                  sort();
                  saveScore();
                  saveTopPlayers();
                  saveTime();
                  setcolor(15);

                  for (i = 0; i <= finalScore; i++){
                    delay(5);
                    cleardevice();
                    gameOverTransition(1);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                    outtextxy(50,20,"F I N A L  S C O R E");
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,10);
                    sprintf(array,"%d", i);
                    if (finalScore < 10)
                      outtextxy(170,60,array);
                    else if (finalScore >= 10 && finalScore < 100)
                      outtextxy(125,60,array);
                    else if (finalScore > 99)
                      outtextxy(90,60,array);
                  }



                  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
                  outtextxy(50,240,"T O P  T E N  S C O R E:");
              
                  j = 260;

                  for (i = 0; i < 10; i++){
                    sprintf(array,"%d", topScores[i]);
                    outtextxy(50,j,array);
                    j += 20;
                  }

                  j = 260;

                  for (i = 0; i < 10; i++){
                    sprintf(array,"%s", mtopPlayers[i]);
                    outtextxy(120,j,array);
                    j += 20;
                  }    

                  j = 260;

                  for (i = 0; i < 10; i++){
                    sprintf(array,"%.2f", topTime[i]);
                    outtextxy(250,j,array);
                    outtextxy(300,j,"Seconds");
                    j += 20;
                  }      

                  stop = 1; // value of 1 means game over 
                  break;
                }
                else
                  rawScore++; 
              }
            }


            note = 0;
            timeG = 0;
            yValue = 390; // reset timer 
       
            if (stop == 0){

              clearTransition();
              circleTransition();
      
              for (i = 0; i < loop; i++){
                userMoves[i] = 0;
                botMoves[i] = 0;
              }

              loop += 2;
              if(dly >= 2)
                dly -= 2;
            }

            else if (stop == 1){

              while(kbhit()){ // This loop catches excess key pressed after game over
                getch();
              }


              restart = -1;
              while(restart == -1){
            
                showmouseptr();
 
                getmousepos(&btn,&ex,&way);

                while(!kbhit() || btn != 1){
                  getmousepos(&btn,&ex,&way);

            
                  if( btn == 1 && (ex >= 426 && ex <= 640) && (way >= 0 && way <= 240)){
                    btn = -1;
                    rawScore = 0;
                    cleardevice();
                    setbkcolor(0);
                    delay(1000);
                    restart = 0; //Restart 0 means the loop is still going
                    stop = 0;
                    loop = 3;
                    dly = 14;
                    break; //Breaks this mouse loop
                  }
                  else if (btn == 1 && (ex >= 426 && ex <= 640) && (way >= 241 && way <= 480)){
                    btn = -1;
                    restart = 1; //Restart 1 will make the loop false
                    rawScore = 0; /////////////// yeet
                    stop = 0;
                    loop = 3;
                    dly = 14;
                    for (i = 0; i < 9; i++){  //RESETS EVERY VALUE OF keyCheck ARRAY TO 112
                      keyCheck[i] = 112;
                    }
                    break; //Breaks this mouse loop
                  }

                }
              }
              break;
            }

            cleardevice();
          }
        }
      }
    }

    cleardevice();
  }
  

	
	closegraph();

  //printf("LOOP: %d CORRECT ANSWERS: %d FINAL SCORE: %d\n",loop,rawScore,finalScore);
  // retrieveScore();
  // sort();
  // saveScore();
  gotoxy(11,3);
  textcolor(14);
  cprintf("T E C H N O L O G I C A L  U N I V E R S I T Y  O F  T H E");
  gotoxy(23,5);
  cprintf("P H I L I P P I N E S  M A N I L A");
  gotoxy(26,8);
  printf("S . Y .  2 0 1 9  -  2 0 2 0");
  gotoxy(19,11);
  cprintf("T H A N K  Y O U  F O R  P L A Y I N G ^_^");
  gotoxy(24,14);
  printf("M A R V I N  R A Y  D A L I D A");
  gotoxy(24,16);
  printf("V I N C E  B R Y A N  P I N O N");
  gotoxy(22,18);
  printf("S E B A S T I A N  B A C H  P I L I");
  gotoxy(30,20);
  printf("K I A N  L E J A N O");


  getch();
}


////////////////////////////////////////////// FOR MEMORY TEXT DATABASE ///////////////////////////////////////////////////

void retrieveScore(){
  int dataHandler, i = 0;
  FILE* fp;

  fp = fopen("c:\db1.dbf","r");
  if(fp == NULL){
    printf("retreive score File ERROR!");
    getch();
  }
  else{
    
    while(!feof(fp)){

      fscanf(fp,"%d\n",&dataHandler);
        insertScore(dataHandler, i);  
        i++;
    }
    printf("\n");
    fclose(fp);
  }
}

void retrieveTopPlayers(){
  int i = 0;
  char dataHandler[15];
  FILE* fp;

  fp = fopen("c:\db1name.dbf","r");
  if(fp == NULL){
    printf("retreive name File ERROR!");
    getch();
  }
  else{
    
    while(!feof(fp)){

      fscanf(fp,"%s\n",&dataHandler);
        insertName(dataHandler, i);  
        i++;
    }
    printf("\n");
    fclose(fp);
  }
}

void retrieveTime(){
  float dataHandler, i = 0;
  FILE* fp;

  fp = fopen("c:\db1time.dbf","r");
  if(fp == NULL){
    printf("retreive score File ERROR!");
    getch();
  }
  else{
    
    while(!feof(fp)){

      fscanf(fp,"%f\n",&dataHandler);
        insertTime(dataHandler, i);  
        i++;
    }
    printf("\n");
    fclose(fp);
  }
}

void insertTime(float data, int i){
  topTime[i] = data;
}

void insertName(char data[15], int i){
  strcpy(mtopPlayers[i],data);
}

void insertScore(int data, int i){
  topScores[i] = data;
}

void saveScore(){
  int i;
  FILE* fp;
  fp = fopen("c:\db1.dbf","w");


  if(fp == NULL){
    printf("save score File ERROR!");
    getch();
  }
  else{
    
    for (i = 0; i < 10; i++){
      fprintf(fp, "%d\n", topScores[i]);
    }
    
    fclose(fp);
  }
}

void saveTopPlayers(){
  int i;
  FILE* fp;
  fp = fopen("c:\db1name.dbf","w");


  if(fp == NULL){
    printf("save name File ERROR!");
    getch();
  }
  else{
    
    for (i = 0; i < 10; i++){
      fprintf(fp, "%s\n", mtopPlayers[i]);
    }
    
    fclose(fp);
  }
}

void saveTime(){
  int i;
  FILE* fp;
  fp = fopen("c:\db1time.dbf","w");


  if(fp == NULL){
    printf("save time File ERROR!");
    getch();
  }
  else{
    
    for (i = 0; i < 10; i++){
      fprintf(fp, "%f\n", topTime[i]);
    }
    
    fclose(fp);
  }
}


void sort(){
  int i, temp, fnl;
  float timeFnl, tTime;
  char tName[15], fnlName[15];
  fnl = finalScore;
  strcpy(fnlName, name);
  timeFnl = (float) timeG/1000;
  for (i = 0; i < 10; i++){
    if (finalScore > topScores[i]){
    
      temp = topScores[i];
      topScores[i] = fnl;
      fnl = temp;

      strcpy(tName, mtopPlayers[i]);
      strcpy(mtopPlayers[i],fnlName);
      strcpy(fnlName,tName);

      tTime = topTime[i];
      topTime[i] = timeFnl;
      timeFnl = tTime;
    }
  }

  for (i = 0; i < 10; i++){
    if (topScores[i] == topScores[i + 1] && topTime[i + 1] < topTime[i]){
      temp = topScores[i];
      topScores[i] = topScores[i + 1];
      topScores[i + 1] = temp;

      strcpy(tName, mtopPlayers[i]);
      strcpy(mtopPlayers[i],mtopPlayers[i + 1]);
      strcpy(mtopPlayers[i + 1],tName);

      tTime = topTime[i];
      topTime[i] = topTime[i + 1];
      topTime[i + 1] = tTime;
    }
  }
}


////////////////////////////////////////////// FOR DODGE TEXT DATABASE ///////////////////////////////////////////////////

void retrieveHighScore(){
  
  FILE* fp;

  fp = fopen("c:\db2.dbf","r");
  if(fp == NULL){
    printf("retreive score File ERROR!");
    getch();
  }
  else{
    
    while(!feof(fp)){

      fscanf(fp,"%d\n",&dodgeHighScore);

    }
    fclose(fp);
  }
}

void compare(){
  if (dodge > dodgeHighScore){
    dodgeHighScore = dodge;
    strcpy(topPlayer,name);
  }
}

void saveHighScore(){

  FILE* fp;
  fp = fopen("c:\db2.dbf","w");


  if(fp == NULL){
    printf("save score File ERROR!");
    getch();
  }
  else{
    
    fprintf(fp, "%d\n", dodgeHighScore);
    
    fclose(fp);
  }
}

void retrieveName(){
  
  FILE* fp;

  fp = fopen("c:\db2name.dbf","r");
  if(fp == NULL){
    printf("retreive name File ERROR!");
    getch();
  }
  else{
    
    while(!feof(fp)){

      fscanf(fp,"%s\n",&topPlayer);

    }
    fclose(fp);
  }
}

void saveName(){
  FILE* fp;
  fp = fopen("c:\db2name.dbf","w");
  if(fp == NULL){
    printf("save name File ERROR!");
    getch();
  }
   else{
    
    fprintf(fp, "%s\n", topPlayer);
    
    fclose(fp);
  }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dodgeGameOverTransition(){
  cleardevice();
  settextstyle(0,HORIZ_DIR,4);
  setcolor(4);
  outtextxy(50,83,"D O D G E D: ");
  setcolor(15);
  outtextxy(50,80,"D O D G E D: ");
  sprintf(array,"%d", dodge);
  setcolor(4);
  outtextxy(480,83,array);
  setcolor(15);
  outtextxy(480,80,array);
  settextstyle(0,HORIZ_DIR,2);
  setcolor(4);
  outtextxy(40,415,"[ANY] R E S T A R T   [ESC] Q U I T");
  setcolor(15);
  outtextxy(40,412,"[ANY] R E S T A R T   [ESC] Q U I T");
  setcolor(4);
  settextstyle(0,HORIZ_DIR,3);
  outtextxy(190,170,"HIGH SCORE");
  setcolor(15);
  outtextxy(190,167,"HIGH SCORE");
  sprintf(array,"%d", dodgeHighScore);
  settextstyle(0,HORIZ_DIR,15);
  setcolor(4);
  outtextxy(200,220, array);
  setcolor(15);
  outtextxy(200,225, array);

  settextstyle(0,HORIZ_DIR,3);
  setcolor(4);
  sprintf(array,"%s", topPlayer);
  outtextxy(187,360, array);
  setcolor(15);
  outtextxy(187,357, array);
}

void randomBar(int barPositionH, int barPositionV, int mode){
  if(mode == 0){
    setfillstyle(SOLID_FILL,10);
    attackOn = 0;
    sound(500);
    delay(50);
    nosound();
  }
  else{
    setfillstyle(SOLID_FILL,4);
    attackOn = 1;
    sound(1000);
    delay(50);
    nosound();

  }
  
  if(barPositionH == 0){
    bar(0,0,80,480);
    barHX[0] = 0;
    barHX[1] = 80;
    barHY[0] = 0;
    barHY[1] = 480;
  }
  else if(barPositionH == 1){
    bar(80,0,160,480);
    barHX[0] = 80;
    barHX[1] = 160;
    barHY[0] = 0;
    barHY[1] = 480;
  }
    
  else if(barPositionH == 2){
    bar(160,0,240,480);
    barHX[0] = 160;
    barHX[1] = 240;
    barHY[0] = 0;
    barHY[1] = 480;
  }
    
  else if(barPositionH == 3){
    bar(240,0,320,480);
    barHX[0] = 240;
    barHX[1] = 320;
    barHY[0] = 0;
    barHY[1] = 480;
  }
    
  else if(barPositionH == 4){
    bar(320,0,400,480);
    barHX[0] = 320;
    barHX[1] = 400;
    barHY[0] = 0;
    barHY[1] = 480;
  }
    
  else if(barPositionH == 5){
    bar(400,0,480,480);
    barHX[0] = 400;
    barHX[1] = 480;
    barHY[0] = 0;
    barHY[1] = 480;
  }
    
  else if(barPositionH == 6){
    bar(480,0,560,480);
    barHX[0] = 480;
    barHX[1] = 560;
    barHY[0] = 0;
    barHY[1] = 480;
  }
    
  else if(barPositionH == 7){
    bar(560,0,640,480);
    barHX[0] = 560;
    barHX[1] = 640;
    barHY[0] = 0;
    barHY[1] = 480;
  }

  if(barPositionV == 0){
    bar(0,0,640,80);
    barVX[0] = 0;
    barVX[1] = 640;
    barVY[0] = 0;
    barVY[1] = 80;
  }
  
  else if(barPositionV == 1){
    bar(0,80,640,160);
    barVX[0] = 0;
    barVX[1] = 640;
    barVY[0] = 80;
    barVY[1] = 160;
  } 
  
  else if(barPositionV == 2){
    bar(0,160,640,240);
    barVX[0] = 0;
    barVX[1] = 640;
    barVY[0] = 160;
    barVY[1] = 240;
  }

  else if(barPositionV == 3){
    bar(0,240,640,320);
    barVX[0] = 0;
    barVX[1] = 640;
    barVY[0] = 240;
    barVY[1] = 320;
  }

  else if(barPositionV == 4){
    bar(0,320,640,400);
    barVX[0] = 0;
    barVX[1] = 640;
    barVY[0] = 320;
    barVY[1] = 400;
  }

  else if(barPositionV == 5){
    bar(0,400,640,480);
    barVX[0] = 0;
    barVX[1] = 640;
    barVY[0] = 400;
    barVY[1] = 480;
  }

}

void randomPosition(){

  int r1, r2 = -1; // ,i,interval = 500;
  r1 = rand() % 8;
  
  if(dodge == 10){
    greenDelay -= 100;
    redDelay -= 50;
  }

  if (dodge == 15){
    greenDelay -= 50;
    redDelay -= 20;    
  } 

  if (dodge == 20){
    greenDelay -= 25;
    redDelay -= 15;    
  }

  if (dodge == 30){
    greenDelay -= 25;
    redDelay -= 15;    
  }

  if (dodge == 40){
    greenDelay -= 25;
    redDelay -= 15;    
  }

  if (dodge == 45){
    greenDelay -= 25;
    redDelay -= 15;    
  }

  if (dodge == 50){
    greenDelay -= 25;
    redDelay -= 15;    
  }

  if (dodge == 55){
    greenDelay -= 25;
    redDelay -= 15;    
  }

  if (dodge >= 10)
    r2 = rand() % 6;

  randomBar(r1,r2,0);
  delay(greenDelay - 50);
  randomBar(r1,r2,1);

}

void dodgeStarting(){
  
  settextstyle(0,HORIZ_DIR,15);
  setcolor(4);
  outtextxy(270,160,"3");
  setcolor(15);
  outtextxy(265,155,"3");
  sound(600);
  delay(100);
  nosound();
  delay(900);
  cleardevice();
  setcolor(6);
  outtextxy(270,160,"2");
  setcolor(15);
  outtextxy(265,155,"2");
  sound(1200);
  delay(100);
  nosound();
  delay(900);
  cleardevice();
  setcolor(2);
  outtextxy(270,160,"1");
  setcolor(15);
  outtextxy(265,155,"1");
  sound(1800);
  delay(100);
  nosound();
  delay(900);
  cleardevice();
  setfillstyle(1,4);
  bar(0,140,640,220);
  setcolor(0);
  settextstyle(0,HORIZ_DIR,5);
  outtextxy(100,160,"D O D G E !");
  setcolor(15);
  outtextxy(95,155,"D O D G E !");
  sound(2400);
  delay(100);
  nosound();
  delay(900);
  nosound();
  cleardevice();
  setbkcolor(0);

}

void chooseGame(int choice){
  cleardevice();
  if (choice == 1){
    settextstyle(0,HORIZ_DIR,1);
    outtextxy(20,20,"[UP] [DOWN] - CHOOSE GAME    [ENTER] - SELECT GAME    [ESC] - QUIT");
    setfillstyle(11, 6);
    bar(80,70,530,220);
    setfillstyle(1, 14);
    bar(100,50,550,200);
    setfillstyle(1, 6);
    circle(110,60,5);
    floodfill(110,60,15);
    circle(110,190,5);
    floodfill(110,190,15);
    circle(540,60,5);
    floodfill(540,60,15);
    circle(540,190,5);
    floodfill(540,190,15);
    setcolor(6);
    settextstyle(0,HORIZ_DIR,4);
    outtextxy(150,110,"M E M O R Y");


    setfillstyle(SOLID_FILL,4);
    bar(160,240,240,480);
    bar(0,300,640,380);

    setcolor(0);
    settextstyle(0,HORIZ_DIR,4);
    outtextxy(140,326,"D O D G E ++");
    setcolor(15);
    settextstyle(0,HORIZ_DIR,4);
    outtextxy(143,323,"D O D G E ++");

    setfillstyle(1, 14);
    bar(0,0,5,240);
    bar(635,0,640,240);
    bar(0,0,640,5);
    bar(0,235,640,240);
  }
  else if (choice == 2){
    settextstyle(0,HORIZ_DIR,1);
    outtextxy(20,20,"[UP] [DOWN] - CHOOSE GAME    [ENTER] - SELECT GAME    [ESC] - QUIT");
    setfillstyle(11, 6);
    bar(80,70,530,220);
    setfillstyle(1, 14);
    bar(100,50,550,200);
    setfillstyle(1, 6);
    circle(110,60,5);
    floodfill(110,60,15);
    circle(110,190,5);
    floodfill(110,190,15);
    circle(540,60,5);
    floodfill(540,60,15);
    circle(540,190,5);
    floodfill(540,190,15);
    setcolor(6);
    settextstyle(0,HORIZ_DIR,4);
    outtextxy(150,110,"M E M O R Y");


    setfillstyle(SOLID_FILL,4);
    bar(160,240,240,480);
    bar(0,300,640,380);

    setcolor(0);
    settextstyle(0,HORIZ_DIR,4);
    outtextxy(140,326,"D O D G E ++");
    setcolor(15);
    settextstyle(0,HORIZ_DIR,4);
    outtextxy(143,323,"D O D G E ++");

    setfillstyle(1, 14);
    bar(0,240,5,640);
    bar(635,240,640,640);
    bar(0,240,640,245);
    bar(0,475,640,480);
  }
}

void dodgeTransition(){
  delay(500);
  setfillstyle(SOLID_FILL,10);
  bar(160,0,240,480);
  delay(300);
  setfillstyle(SOLID_FILL,4);
  bar(160,0,240,480);
  delay(300);
  setfillstyle(SOLID_FILL,10);
  bar(0,160,640,240);
  delay(300);
  setfillstyle(SOLID_FILL,4);
  bar(0,160,640,240);
  delay(300);
  setcolor(0);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(140,186,"D O D G E ++");
  setcolor(15);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(143,183,"D O D G E ++");
  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
  outtextxy(225,350,"P R E S S  A N Y  K E Y");
}

void tutorial(){
  int i,j = 0, frame;
  settextstyle(0,HORIZ_DIR,1);
  for(frame = 0; frame < 12; frame++){
    switch(frame){
      case 0:
        draw();
        setcolor(15);
        outtextxy(180,380,"Hello! I'm Tutorial Box, and I'm going to introduce you");
        outtextxy(180,395,"to this game.");
      break;
      case 1:
        animateTutorial();
        cleardevice();
        draw();
        outtextxy(180,380,"The title speak for itself, as this game focuses on");
        outtextxy(180,395,"memorizing patterns.");
      break;
      case 2:
        animateTutorial();
        cleardevice();
        draw();
        outtextxy(180,380,"Before starting... set a specific key, from your");
        outtextxy(180,395,"keyboard, to each circle.");
      break;
      case 3:
        cleardevice();
        keyAssignment();
      break;
      case 4:
        animateTutorial();
        cleardevice();
        draw();
        outtextxy(180,380,"Once the game starts, a bot will randomly fill a circle");
        outtextxy(180,395,"with a color, creating a unique pattern.");
        delay(1500);
        randomColor(i);
        floodfill(circleExes[4],circleWays[4], WHITE);
        delay(350);
        cleardevice();
        draw();
        outtextxy(180,380,"Once the game starts, a bot will randomly fill a circle");
        outtextxy(180,395,"with a color, creating a unique pattern.");
        randomColor(i);
        floodfill(circleExes[0],circleWays[0], WHITE);
        delay(350);
        cleardevice();
        draw();
        outtextxy(180,380,"Once the game starts, a bot will randomly fill a circle");
        outtextxy(180,395,"with a color, creating a unique pattern.");
        randomColor(i);
        floodfill(circleExes[2],circleWays[2], WHITE);
        delay(350);
        cleardevice();
        draw();
        outtextxy(180,380,"Once the game starts, a bot will randomly fill a circle");
        outtextxy(180,395,"with a color, creating a unique pattern.");
      break;
      case 5:
        animateTutorial();
        cleardevice();
        draw();
        outtextxy(180,380,"After the bot is finished, it's now your turn to copy");
        outtextxy(180,395,"the pattern, that the bot showed.");
      break;
      case 6:
        animateTutorial();
        cleardevice();
        draw();
        outtextxy(180,380,"Use the specific keys you assigned, earlier, to each");
        outtextxy(180,395,"circle to copy the bot's pattern.");
      break;
      case 7:
        animateTutorial();
        cleardevice();
        for (i = 140; i > 90; i--){
          bar(35,i,65,390);
          draw();
          outtextxy(180,380,"Take note! you can only copy the bot's pattern under");
          outtextxy(180,395,"a period of time.");
        }
      break;
      case 8:
        animateTutorial();
        cleardevice();
        draw();
        outtextxy(180,380,"If you fail to copy the bot's pattern the game will");
        outtextxy(180,395,"automatically end.");
      break;
      case 9:
        animateTutorial();
        cleardevice();
        draw();
        outtextxy(180,380,"GOODLUCK!");
      break;
      case 10:
        animateTutorial();
        cleardevice();
        draw();
        paused();
        outtextxy(180,380,"Oh wait! I almost forgot hahaha... after the bot finished");
        outtextxy(180,395,"it's turn, you can pause the game by pressing \"P\"");
      break;
      case 11:
        animateTutorial();
        cleardevice();
        draw();
        outtextxy(180,380,"GOODLUCK THEN HA HA HA...");
      break;
    }
    while(!kbhit() && frame != 3){
      sound(TutorialNotes[j]);
      delay(150);
      nosound();
      delay(50);
      j++;
      if(j == 32)
        j = 0;
    }
    if(frame != 3)
      getch();
  }
}

void draw(){
  createCircle(0,0);
  setfillstyle(1,4);
  bar(0,340,640,480);
  setfillstyle(1,14);
  bar(10,290,170,470);
  setfillstyle(1,6);
  bar(50,360,65,400);
  bar(120,360,135,400);
  bar(60,420,125,430);
  bar(70,430,115,440);

  setfillstyle(1,15);
  bar(55,370,65,390);
  bar(125,370,135,390);
  outtextxy(400,460,"Press any key to continue >");

}

void animateTutorial(){
  int i;
  for (i = 360; i <= 400; i++){
    delay(2);
    setfillstyle(1,4);
    bar(0,340,640,480);
    setfillstyle(1,14);
    bar(10,290,170,470);
    setfillstyle(1,6);
    bar(50,i,65,400);
    bar(120,i,135,400);
    bar(60,420,125,430);
    bar(70,430,115,440);
  }
  for (i = 400; i >= 360; i--){
    delay(2);
    setfillstyle(1,4);
    bar(0,340,640,480);
    setfillstyle(1,14);
    bar(10,290,170,470);
    setfillstyle(1,6);
    bar(50,i,65,400);
    bar(120,i,135,400);
    bar(60,420,125,430);
    bar(70,430,115,440);
  }
}


void menuTransition(){
  while(1){
    setfillstyle(11, 6);
    bar(transitionX[0],120,transitionX[1],270);
    setfillstyle(1, 14);
    bar(transitionX[2],100,transitionX[3],250);
    
    if (transitionX[0] != 80 && transitionX[1] != 530 && transitionX[2] != 100 && transitionX[3] != 550){
      transitionX[0] += 2;
      transitionX[1] += 2;
      transitionX[2] -= 2;
      transitionX[3] -= 2;
    }
    else
      break;
  }

  cleardevice();

  setfillstyle(11, 6);
  bar(80,120,530,270);
  setfillstyle(1, 14);
  bar(100,100,550,250);
  setfillstyle(1, 6);
  circle(110,110,5);
  floodfill(110,110,15);
  circle(110,240,5);
  floodfill(110,240,15);
  circle(540,110,5);
  floodfill(540,110,15);
  circle(540,240,5);
  floodfill(540,240,15);


  setcolor(6);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(150,160,"M E M O R Y");
  setcolor(15);
  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
  outtextxy(225,350,"P R E S S  A N Y  K E Y");
}

void circleTransition(){
  int i;
  
  createCircle(0,0);

  for (i = 640; i >= 0; i--){
    setfillstyle(1,14);
    bar(i,180,640,330);
  }

  setcolor(0);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(147,243,"R E A D Y ?");
  setcolor(6);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(150,240,"R E A D Y ?");
  delay(1000);

  for (i = 640; i >= 0; i--){
    setfillstyle(1,4);
    bar(i,180,640,330);
  }

  setcolor(0);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(147,243,"S T A R T !");
  setcolor(15);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(150,240,"S T A R T !");
  delay(500);
}

void clearTransition(){
  int i;

  for (i = 640; i >= 0; i--){
    setfillstyle(1,10);
    bar(i,180,640,330);
    sound(i);
  }



  setcolor(0);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(97,243,"C L E A R E D !");

  setcolor(15);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(100,240,"C L E A R E D !");
  
  sound(1000);
  delay(70);
  sound(1600);
  delay(250);
  
  nosound();

  delay(500);

  cleardevice();
  setcolor(15);

}

void keyAssignment(){
  int i, j;
  createCircle(0,0);
  for (i = 0; i < 9; i++){
    setfillstyle(1,14);
    floodfill(circleExes[i],circleWays[i], WHITE);
    key[i] = getch();
    for (j = 0; j < 9; j++){
      if (key[i] == keyCheck[j] || key[i] == 13){
        i--;
        break;
      }
    }
    keyCheck[i] = key[i];
    music(introNotes[i]);
    cleardevice();
    createCircle(0,0);
  }
}

void createTimer(int dly){
  int i;
  if(yValue > 260)
    setfillstyle(SOLID_FILL, WHITE);
  else if(yValue <= 260 && yValue > 130)
    setfillstyle(SOLID_FILL, LIGHTRED);
  else if(yValue <= 130 && yValue > 90)
    setfillstyle(SOLID_FILL, RED);
  delay(dly);
  bar(35,yValue,65,390);
  yValue -= 1;
}

void timerFixer(){

  if(yValue > 260)
    setfillstyle(SOLID_FILL, WHITE);
  else if(yValue <= 260 && yValue > 130)
    setfillstyle(SOLID_FILL, LIGHTRED);
  else if(yValue <= 130 && yValue > 90)
    setfillstyle(SOLID_FILL, RED);
  bar(35,yValue,65,390);
}

void paused(){
  setfillstyle(1,3);
  bar(0,180,640,330);

  setfillstyle(1,0);
  bar(97,243,107,273);
  bar(127,243,137,273);

  setfillstyle(1,15);
  bar(100,240,110,270);
  bar(130,240,140,270);

  setcolor(0);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(167,245,"P A U S E D");
  setcolor(15);
  settextstyle(0,HORIZ_DIR,4);
  outtextxy(170,242,"P A U S E D");
  settextstyle(0,HORIZ_DIR,1);
  outtextxy(145,300,"P R E S S  E N T E R  T O  C O N T I N U E");
}

void gameOverTransition(int num){
  int i, j = 640;

  if (num == 0){
    for (i = 0; i <= 640; i++){
      setfillstyle(1,4);
      bar(0,0,320,i);
      sound(j);
      j--;
    }

    nosound();

    for (i = 480; i >= 0; i--){
      setfillstyle(1,14);
      bar(320,480,640,i);
    }

    // setcolor(14);
    // settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    // outtextxy(70,100,"G A M E");

    // setcolor(4);
    // settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    // outtextxy(350,100,"O V E R");

    settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
    setcolor(14);
    for (i = 0; i < 8; i++){
      switch(i){
        case 0:
          outtextxy(70,100,"G");
          sound(490);
          delay(150);
        break;
        case 1:
          outtextxy(70,100,"  A");
          sound(415);
          delay(150);
        break;
        case 2:
          outtextxy(70,100,"    M");
          sound(470); 
          delay(150);
        break;
        case 3:
          outtextxy(70,100,"      E");
          sound(390); 
          delay(150);
        break;
        case 4:
          setcolor(4);
          outtextxy(350,100,"O");
          sound(440); 
          delay(150);
        break;
         case 5:
      
          outtextxy(350,100,"  V");
          sound(370); 
          delay(100);
        break;
        case 6:
          outtextxy(350,100,"    E");
          sound(415); 
          delay(150);
        break;
        case 7:
          outtextxy(350,100,"      R");
          sound(350); 
          delay(300);
        break;
      }
    }

    nosound();
    delay(1000);

    for (i = 640; i >= 0; i--){
      setfillstyle(1,0);
      bar(i,0,680,480);
    }

    cleardevice();

    for (i = 640; i >= 426; i--){
      setfillstyle(1,10);
      bar(i,0,650,240);
    }

    for (i = 640; i >= 426; i--){
      setfillstyle(1,4);
      bar(i,240,650,480);
    }

    setcolor(15);
    setfillstyle(1,15);
    line(500,80,500,160);
    line(500,80,570,120);
    line(500,160,570,120);
    floodfill(540,120,15);

    setcolor(15);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    outtextxy(475,350,"Q U I T");

  }
  else if (num == 1){
    setbkcolor(0);
    setfillstyle(1,10);
    bar(426,0,640,240);
    setfillstyle(1,4);
    bar(426,240,640,480);
    setcolor(15);
    
    setfillstyle(1,15);
    line(500,80,500,160);
    line(500,80,570,120);
    line(500,160,570,120);
    floodfill(540,120,15);

    setcolor(15);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    outtextxy(475,350,"Q U I T");

  }

}

void loading(){
  int i, j;
  settextstyle(0,HORIZ_DIR,1);
  for (j = 0; j < 3; j++){

    for (i = 0; i < 10; i++){
      delay(25);
      cleardevice();
      circle(270,250, 10 + i);
      circle(310,250, 10);
      circle(350,250, 10);
      outtextxy(250,290,"L O A D I N G . . .");
    }
    for (i = 10; i > 0; i--){
      delay(25);
      cleardevice();
      circle(270,250, 10 + i);
      circle(310,250, 10);
      circle(350,250, 10);
      outtextxy(250,290,"L O A D I N G . . .");
    }

    for (i = 0; i < 10; i++){
      delay(25);
      cleardevice();
      circle(270,250, 10);
      circle(310,250, 10 + i);
      circle(350,250, 10);
      outtextxy(250,290,"L O A D I N G . . .");
    }
    for (i = 10; i > 0; i--){
      delay(25);
      cleardevice();
      circle(270,250, 10);
      circle(310,250, 10 + i);
      circle(350,250, 10);
      outtextxy(250,290,"L O A D I N G . . .");
    }
    for (i = 0; i < 10; i++){
      delay(25);
      cleardevice();
      circle(270,250, 10);
      circle(310,250, 10);
      circle(350,250, 10 + i);
      outtextxy(250,290,"L O A D I N G . . .");
    }
    for (i = 10; i > 0; i--){
      delay(25);
      cleardevice();
      circle(270,250, 10);
      circle(310,250, 10);
      circle(350,250, 10 + i);
      outtextxy(250,290,"L O A D I N G . . .");
    }
  }
}

void dodgeLoading(){
  int i, j;
  settextstyle(0,HORIZ_DIR,1);
  for (j = 0; j < 3; j++){

    for (i = 400; i >= 250; i--){
      delay(5);
      cleardevice();
      line(i,250,400,250);
      outtextxy(250,290,"L O A D I N G . . .");
      outtextxy(300,140,"T I P : ");
      setcolor(2);
      outtextxy(230,190,"G R E E N");
      setcolor(15);
      outtextxy(315,190,"I S  S A F E,");
      setcolor(4);
      outtextxy(230,220,"R E D ");
      setcolor(15);
      outtextxy(285,220,"I S  D A N G E R .");
    }
    setcolor(15);
    for (i = 400; i > 250; i--){
      delay(5);
      cleardevice();
      line(250,250,i,250);
      outtextxy(250,290,"L O A D I N G . . .");
      outtextxy(300,140,"T I P : ");
      setcolor(2);
      outtextxy(230,190,"G R E E N");
      setcolor(15);
      outtextxy(315,190,"I S  S A F E,");
      setcolor(4);
      outtextxy(230,220,"R E D ");
      setcolor(15);
      outtextxy(285,220,"I S  D A N G E R .");
    }
  }

}

void tutorialBox(){
  setfillstyle(11, 6);
  bar(80,90,530,370);
  setfillstyle(1, 14);
  bar(100,70,550,350);
  setcolor(6);
  settextstyle(0,HORIZ_DIR,2);
  outtextxy(135,110,"S E E  T U T O R I A L ?");

  setfillstyle(1, 0);
  bar(155,215,285,285);
  setfillstyle(1, 10);
  bar(160,210,290,280);


  setfillstyle(1, 0);
  bar(360,215,490,285);
  setfillstyle(1, 4);
  bar(365,210, 495,280);
  setcolor(15);
  settextstyle(0,HORIZ_DIR,2);
  outtextxy(185,240,"Y E S");
  settextstyle(0,HORIZ_DIR,2);
  outtextxy(405,240,"N O");
}

void createCircle(int clicked, int radius){
  int i, circleX = 148, circleY = 90;

    line(20,90,80,90);
    setfillstyle(10,14);
    bar(148,90,468,390);

    if (clicked == 0){
   
      for (i = 1; i <= 9; i++){

          if (i == 4 || i == 7){
            circleY += 150;
            circleX = 148; 
          }

          circle(circleX,circleY,50);
          circleX += 160;
        }
   }

   else if (clicked == 1){
      circleX += 160;
      circle(148,90,radius);
      for (i = 2; i <= 9; i++){

          if (i == 4 || i == 7){
            circleY += 150;
            circleX = 148; 
          }

          circle(circleX,circleY,50);
          circleX += 160;
        }
   }

    else if (clicked == 2){
      circle(148,90,50);
      circle(308,90,radius);
      circle(468,90,50);
      circle(148,240,50);
      circle(308,240,50);
      circle(468,240,50);
      circle(148,390,50);
      circle(308,390,50);
      circle(468,390,50);
   }

   else if (clicked == 3){
      circle(148,90,50);
      circle(308,90,50);
      circle(468,90,radius);
      circle(148,240,50);
      circle(308,240,50);
      circle(468,240,50);
      circle(148,390,50);
      circle(308,390,50);
      circle(468,390,50);
   }

   else if (clicked == 4){
      circle(148,90,50);
      circle(308,90,50);
      circle(468,90,50);
      circle(148,240,radius);
      circle(308,240,50);
      circle(468,240,50);
      circle(148,390,50);
      circle(308,390,50);
      circle(468,390,50);
   }

    else if (clicked == 5){
      circle(148,90,50);
      circle(308,90,50);
      circle(468,90,50);
      circle(148,240,50);
      circle(308,240,radius);
      circle(468,240,50);
      circle(148,390,50);
      circle(308,390,50);
      circle(468,390,50);
   }

   else if (clicked == 6){
      circle(148,90,50);
      circle(308,90,50);
      circle(468,90,50);
      circle(148,240,50);
      circle(308,240,50);
      circle(468,240,radius);
      circle(148,390,50);
      circle(308,390,50);
      circle(468,390,50);
   }

   else if (clicked == 7){
      circle(148,90,50);
      circle(308,90,50);
      circle(468,90,50);
      circle(148,240,50);
      circle(308,240,50);
      circle(468,240,50);
      circle(148,390,radius);
      circle(308,390,50);
      circle(468,390,50);
   }

   else if (clicked == 8){
      circle(148,90,50);
      circle(308,90,50);
      circle(468,90,50);
      circle(148,240,50);
      circle(308,240,50);
      circle(468,240,50);
      circle(148,390,50);
      circle(308,390,radius);
      circle(468,390,50);
   }

   else if (clicked == 9){
      circle(148,90,50);
      circle(308,90,50);
      circle(468,90,50);
      circle(148,240,50);
      circle(308,240,50);
      circle(468,240,50);
      circle(148,390,50);
      circle(308,390,50);
      circle(468,390,radius);
   }
   
}


void music(int pitch){
   sound(pitch);
   delay(175);
   nosound();
}

void randomColor(int anongKulay){
  if (anongKulay == 0){
    setfillstyle(SOLID_FILL, YELLOW);
    music(155);
  }
  else if (anongKulay == 1){
    setfillstyle(SOLID_FILL, RED);
    music(176);
  }
  else if (anongKulay == 2){
    setfillstyle(SOLID_FILL, BLUE);
    music(195);
  }
  else if (anongKulay == 3){
    setfillstyle(SOLID_FILL, CYAN);
    music(207);
  }
  else if (anongKulay == 4){
    setfillstyle(SOLID_FILL, MAGENTA);
    music(235);
  }
  else if (anongKulay == 5){
    setfillstyle(SOLID_FILL, GREEN);
    music(130);
  }
  else if (anongKulay == 6){
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    music(145);
  }
  else if (anongKulay == 7){
    setfillstyle(SOLID_FILL, YELLOW);
    music(176);
  }
  else if (anongKulay == 8){
    setfillstyle(SOLID_FILL, WHITE);
    music(195);
  }
}

void bot(int level){
  int r, i, interval = 500;

    if (loop >= 15 && loop < 20)
      interval = 450;
    if(loop >= 19 && loop < 30)
      interval = 425;
    if(loop >= 30 && loop < 100)
      interval = 400;

    for (i = 0; i < loop; i++){
      r = rand() % 9;
      botMoves[i] = r;
      randomColor(r);
      floodfill(circleExes[r],circleWays[r], WHITE);
      delay(interval);
      cleardevice();
      createCircle(0,0);
    }

}

int getchConverter(int input, int rtrn){
  setfillstyle(SOLID_FILL, YELLOW);
  if (input == key[0]){
    value = 0;
  }
  else if (input == key[1]){
    value = 1;
  }
  else if (input == key[2]){
    value = 2;
  }
  else if (input == key[3]){
    value = 3;
  }
  else if (input == key[4]){
    value = 4;
  }
  else if (input == key[5]){
    value = 5;
  }
  else if (input == key[6]){
    value = 6;
  }
  else if (input == key[7]){
    value = 7;
  }
  else if (input == key[8]){
    value = 8;
  }
  else{
    if (rtrn == 0)
      rtrn = - 1;
    else
      rtrn--;
  }
    

  if (rtrn != -1){
    floodfill(circleExes[value],circleWays[value], WHITE);
    delay(100);
    cleardevice();
    createCircle(0,0);
  }

  return rtrn;
}

void score(int rawScore){
  
    finalScore = loop * rawScore;

}

//////////////////////////////////////////////////////////////////////////////////////////

void showmouseptr(){
   i.x.ax = 1;
   int86(0X33, &i, &o);
}
 
void getmousepos(int *button, int *x, int *y){
   i.x.ax = 3;
   int86(0X33, &i, &o);
 
   *button = o.x.bx;
   *x = o.x.cx;
   *y = o.x.dx;
}