#include "simpletools.h"                      // Include simple tools
#include "adcDCpropab.h"
#include "servo.h"
#include "boebot.h"
#include "JustinMN.h"

int main()
{
  pause(1000);
  adc_init(21, 20, 19, 18);                   // CS=21, SCL=20, DO=19, DI=18 
  while(1)
  {
     HappyState();
     SadState();
     ScaredState();
     AngerState();
     LoveState();
  }
  return 0;
}

///////////***EMOTION***///////////
void HappyState()
{
  pause(1000);
  high(1);
  high(2);
  high(3);
  freqout(0, QN, F4);
  low(1);
  low(2);
  low(3);
  while(1)
  {
    ///////SWITCH////////
    int button = input(11);
    print("button = %d\n", button);
    if (button == 1)
    {
      return;
    }
    ///////SWITCH////////  
    
    adc_init(21, 20, 19, 18);
    float v1;
    while(1){
      servo_speed(14,50);
      servo_speed(15,50);   
      //1 is red, 2 is green, 3 is blue
      high(2);
      high(1);
      pause(200);        
      low(2); 
      low(1); 
      v1 = adc_volts(0);
      print("Happy Flex = %f V\n", v1);
      if(v1>1.9 || v1<1.1)
      {
        InteractHappy();
      }      
      pause(100);                               // Wait 1/10 s
  return;    
}  

void InteractHappy()
{
  int *song1_cog = cog_run(song1,128); 
  int *song2_cog = cog_run(song2,128);
  int *dance_cog = cog_run(dance,128);
  pause(15000);
  cog_end(song1_cog);
  cog_end(song2_cog);
  cog_end(dance_cog);
  return;
}

void SadState()
{
  pause(1000);
  high(1);
  high(2);
  high(3);
  freqout(0, QN, F4);
  low(1);
  low(2);
  low(3);
  int count = 0;
  while(1)
  {
    ///////SWITCH////////
    int button = input(11);
    print("button = %d\n", button);
    if (button == 1)
    {
      return;
    }
    ///////SWITCH//////// 
    
    high(3);
    pause(100);
    low(3);
    if(count > 15)
    {
      count = 0;
  
      freqout(0, QNj, B3j); 
      freqout(0, HNj, G3j); 
    }      
    
      //Slow circle
      servo_speed(14, -80);
      servo_speed(15, 0);
          
    float flex = adc_volts(0);
    print("Sad Flex = %f V\n", flex);
    if(flex>1.9 || flex<1.1)
    {
      InteractSad();
    }      
    pause(100);                        // Wait 1/10 s
    count++;
  } 
  return;
}  

void InteractSad()
{
  int count = 0;
  
  while(count < 50)
  {
    high(3);
    high(2);
    pause(100);
    low(3);
    low(2);
    ////////PING/////////
    float i = -1;
    i = Ping(12,13);           
    i = i / 148;
    print("Ping Sad %f\n", i);                      //divide the ping by 148 to get inches, or by 54 to get centimeters
    if(i < 10)
    {
      count = 20;
      int *game_cog1 = cog_run(gameover1,128);
      int *game_cog2 = cog_run(gameover2,128);
      int *game_cog3 = cog_run(gameover3,128);  
  
      //Turning the Robot 180 degrees
      servo_speed(14, 200);
      servo_speed(15, 200);
      pause(1900);
    
      servo_speed(14, 0);
      servo_speed(15, 0);
      pause(100);
  
      servo_speed(14, -200);
      servo_speed(15, 200);
      pause(5000);
      
      servo_speed(14, 0);
      servo_speed(15, 0);
      pause(2000);
      
      cog_end(game_cog1);
      cog_end(game_cog2);
      cog_end(game_cog3);
    }  
    ////////PING///////// 
    count++;
  }   
  return;
}

void ScaredState()
{
  pause(1000);
  high(1);
  high(2);
  high(3);
  freqout(0, QN, F4);
  low(1);
  low(2);
  low(3);
  while(1)
  {
    ///////SWITCH////////
    int button = input(11); 
    print("button = %d\n", button);                   
    if (button == 1)
    {
      return;
    }
    ///////SWITCH////////
    
    float LDRVoltageValue;      
                   
    LDRVoltageValue = adc_volts(1);            // Check A/D 0
    print("LDR Value = %f \n", LDRVoltageValue); // Display LDR voltage value
    Jitter();                                 // Calling Jitter Function
    
    if (LDRVoltageValue < 2.8)                  // Checking to see LDR Value
    {
      InteractScared();
    }
  }
  return;
}

void InteractScared()
{
  LetsGetIt();
  
  //Turning the Robot 180 degrees
  servo_speed(14, 200);
  pause(3000);
  
  servo_speed(14, 0);                     // Move pin 14 motor by speed 0
  servo_speed(15, 0);                     // Move pin 15 motor by speed 0
  pause(1000);                            // Pause for 4 seconds
  return;
}

void AngerState()
{
  pause(1000);
  servo_speed(14,0);
  servo_speed(15,0);
  high(1);
  high(2);
  high(3);
  freqout(0, QN, F4);
  low(1);
  low(2);
  low(3);
  int *mobamba_cog = cog_run(mobamba, 128);
  int *mobamba1_cog = cog_run(mobamba1, 128);
  int *mobamba2_cog = cog_run(mobamba2, 128);
  int *mobamba3_cog = cog_run(mobamba3, 128);
  int *lightshow_cog = cog_run(lightshow, 128);
  while(1)
  {
    ///////SWITCH////////
    int button = input(11);
    if (button == 1)
    {
      print("button = %d\n", button);
      cog_end(mobamba_cog);
      cog_end(mobamba1_cog);
      cog_end(lightshow_cog);
      cog_end(mobamba2_cog);
      cog_end(mobamba3_cog);
      return;
    }   
    ///////SWITCH////////
    
    high(1);
    pause(100);
    low(1);
    
    float flex = adc_volts(0);
    print("Mad Flex = %f V\n", flex);
    if(flex>1.9 || flex<1.1)
    {
      cog_end(lightshow_cog);
      cog_end(mobamba_cog);
      cog_end(mobamba1_cog);
      cog_end(mobamba2_cog);
      cog_end(mobamba3_cog);
      InteractAnger();
      mobamba_cog = cog_run(mobamba, 128);
      mobamba1_cog = cog_run(mobamba1, 128);
      mobamba2_cog = cog_run(mobamba2, 128);
      mobamba3_cog = cog_run(mobamba3, 128);
      lightshow_cog = cog_run(lightshow, 128);
      pause(2000);
    }
  }
  cog_end(lightshow_cog);
  cog_end(mobamba_cog);
  cog_end(mobamba1_cog);
  cog_end(mobamba2_cog);
  cog_end(mobamba3_cog);
  return;
}

void InteractAnger()
{
int counter = 0;
  int *lightshowf_cog = cog_run(lightshowf, 128);
  int *backup_cog = cog_run(backup, 128);
  while(counter<100){
    float distance = distance_cm();
    if (distance < 10){
      counter=0;
      cog_end(lightshowf_cog);
      cog_end(backup_cog);
      attack();
      lightshowf_cog = cog_run(lightshowf, 128);
      backup_cog = cog_run(backup, 128);
      pause(2000);
    }
    counter++;
  }
  cog_end(lightshowf_cog);
  cog_end(backup_cog);
  servo_speed(14,0);
  servo_speed(15,0);
  return;
}
///////////***EMOTION***///////////

////////***BONUSEMOTIONS***////////
void LoveState()
{
  pause(1000);
  high(1);
  high(2);
  high(3);
  freqout(0, QN, F4);
  low(1);
  low(2);
  low(3);
  servo_speed(14, 0);
  servo_speed(15, 0);
  while(1)
  {
    ///////SWITCH////////
    int button = input(11);
    print("button = %d\n", button);
    if (button == 1)
    {
      return;
    }
    ///////SWITCH//////// 
    
    high(1);
    pause(100);
    low(1);
    
    float flex = adc_volts(0);
    print("Love Flex = %f V\n", flex);
    if(flex>1.9 || flex<1.1)
    {
      InteractLove();
    }      
    pause(100);                        // Wait 1/10 s
  } 
  return;
}  

void InteractLove()
{
  int count = 0;
  
  while(count < 100)
  {
    high(3);
    high(2);
    pause(100);
    low(3);
    low(2);
    
    
    
    ////////PING/////////
    float i = -1;
    i = Ping(12,13);           
    i = i / 148;
    print("Ping Love Where? %f\n", i);                      //divide the ping by 148 to get inches, or by 54 to get centimeters
    if(i < 70 && i > 20)
    {
      servo_speed(14, -200);
      servo_speed(15, 200);
      pause(100);
    }
    if(i <= 20)
    {
      servo_speed(14, 0);
      servo_speed(15, 0);
      pause(100);
    }
    else 
    {
      //Slow circle
      servo_speed(14, 50);
      servo_speed(15, 50);
      pause(100);
    }
          
          
      
   
    ////////PING/////////   
    
    count++;
  }   
  return;
}
////////***BONUSEMOTIONS***////////

///////////***MISC***//////////////
void LetsGetIt()
{
  int LightTime = 100;
  int FrequencyTime = 200;
  int FrequencyLevel = 500;
  
  int count = 0;              // Count value          
  int x = 100;
  
  while(x < 2000)
  {
    freqout(0,20,x);
    x = x + 10;
  }
                            
  while(count < 6)
  {
    freqout(0, FrequencyTime, FrequencyLevel);
    high(26);
    low(27);
    pause(LightTime);
    high(27);
    low(26);
    pause(LightTime);
    count++;
    LightTime = 75 + LightTime;
    FrequencyLevel = FrequencyLevel + 100;
    FrequencyTime = FrequencyTime + 100;
  }
  return;
}  
  
void Jitter()
{
  servo_speed(14, 100);                      // Move pin 14 motor by speed 100
  servo_speed(15, -100);                     // Move pin 15 motor by speed -100
  pause(200);                               // Pause for 0.2 seconds
  servo_speed(14, -100);                      // Move pin 14 motor by speed 100
  servo_speed(15, 100);                     // Move pin 15 motor by speed -100
  pause(200);                               // Pause for 0.2 seconds
  return;
}   

int Ping(int trig, int echo)//trig is trigger pin, echo is echo pin
{
  low(trig);//set trig low for start pulse
  low(echo);//set echo low to be safe
  pulse_out(trig, 10);//send the minimum 10 ms pulse on trig to start a ping
  return pulse_in(echo, 1);//get the pulse duration back on echo pin
}

float distance_cm(){
  float i = -1;
  float distancecm;
  i = Ping(12,13);
  distancecm = i/54;
  print("Distance %f\n", distancecm); //divide the ping by 148 to get inches, or by 54 to get centimeters
  return distancecm;
}

void attack(){
  int *lightshowff_cog = cog_run(lightshowff, 128);
  servo_speed(14,-200);
  servo_speed(15,200);
  pause(500);
  servo_speed(14,0);
  servo_speed(15,0);
  cog_end(lightshowff_cog);
  return;
}

void backup(){
  while(1){
    servo_speed(14,25);
    servo_speed(15,-10);
    pause(500);
    servo_speed(14,0);
    servo_speed(15,0);
    pause(500);
    servo_speed(14,10);
    servo_speed(15,-25);
    pause(500);
    servo_speed(14,0);
    servo_speed(15,0);
    pause(500);
  }
  return; 
}

void lightshow(){
 while(1){
   high(26);
   low(27);
   pause(500);  
   low(26);
   high(27);
   pause(500);    
 }
 return;
}

void lightshowf(){
 while(1){
   high(26);
   low(27);
   pause(200);
   low(26);
   high(27);
   pause(200);
 }  
 return;
}

void lightshowff(){
 while(1){
   high(26);
   low(27);
   pause(50);
   low(26);
   high(27);
   pause(50);
 }
 return; 
}
///////////***MISC***//////////////


///////////***MUSIC***/////////////
int gameover1() //RIGHT HAND
{
   int pin = 0;
   
   freqout(pin,QNj,C5j);
   pause(QNj);
   freqout(pin,QNj,G4j);
   
   pause(QNj);
   freqout(pin,HNj,E4j);
   
   freqout(pin,HNj,B4j);
   freqout(pin,HNj,A4j);
   
   //////////
   
   freqout(pin, FNj+HNj, F4j);
   freqout(pin, HNj, A4Sj);
   freqout(pin, HNj, G4Sj);
   
   freqout(pin, HNj, G4j);
   freqout(pin, QNj, D4j);
   freqout(pin, FNj, E4j); 
  
} 

int gameover2() //LEFT HAND
{
   int pin = 6;
   
   freqout(pin,QNj,G3j);
   pause(QNj);
   freqout(pin,QNj,E3j);
   
   pause(QNj);
   freqout(pin,HNj,C3j);
   
   freqout(pin,FNj,F3j);

   ///////
  
   freqout(pin, HNj, C4Sj);
   freqout(pin, HNj, C4j);
}

int gameover3()  //EXTRA RIGHT HAND
{
    int pin = 7;
    
    freqout(pin,QNj,E4j);
    pause(QNj);
    freqout(pin,QNj,C4j);
    
    pause(QNj);
    freqout(pin,HNj,G3j);
    
    freqout(pin,FNj,A4j);
   
   /////////
   
    pause(FNj);
    freqout(pin, HNj, G4Sj);
    pause(HNj);
    pause(HNj);
    
    freqout(pin, FNj+HNj, E3j);    
}  

void mobamba(){
  int pin = 6;
  while(1){
  //1
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  //2
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,QN,E6);
  //3
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  //4
  freqout(pin,EN,E6);
  pause(EN);
  pause(QN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  //5
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  //6
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  //7
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  //8
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  //9
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  //10
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  //11
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  //12
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  //13
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  //14
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  //15
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  //16
  freqout(pin,EN,E6);
  pause(EN);
  freqout(pin,EN,D6);
  pause(EN);
  freqout(pin,EN,G6);
  freqout(pin,EN,F6);
  freqout(pin,EN,E6);
  pause(EN);
  }  
}

void mobamba1(){
  int pin = 0;
  while(1){
  pause(3*FN);//123
  //4
  pause(HN);
  pause(QN);
  freqout(pin,EN,B2);
  freqout(pin,EN,B2);
  //5
  freqout(pin,FN+QN,E3);//6
  pause(QN);
  freqout(pin,QN,E3);
  pause(QN);
  //7
  freqout(pin,HN,F3);
  pause(QN);
  freqout(pin,QN+QN,B2);//8
  pause(QN);
  freqout(pin,EN,B2);
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  //9
  freqout(pin,FN+QN,E3);//10
  pause(QN+QN);
  freqout(pin,EN,E3);
  pause(EN);
  //11
  freqout(pin,HN,F3);
  pause(QN);
  freqout(pin,QN+EN,B2);//12
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  //13
  freqout(pin,FN+HN,E3);//14
  pause(QN);
  freqout(pin,EN,E3);
  pause(EN);
  //15
  freqout(pin,HN,F3);
  pause(QN);
  freqout(pin,QN+EN,B2);//16
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,EN,B2);
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  }  
}

void mobamba2(){
  int pin = 7;
  while(1){
    pause(3*FN);//123
  //4
  pause(HN);
  pause(QN);
  freqout(pin,EN,B2);
  freqout(pin,EN,B2);
  //5
  freqout(pin,FN+QN,E3);//6
  pause(QN);
  freqout(pin,QN,E3);
  pause(QN);
  //7
  freqout(pin,HN,F3);
  pause(QN);
  freqout(pin,QN+QN,B2);//8
  pause(QN);
  freqout(pin,EN,B2);
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  //9
  freqout(pin,FN+QN,E3);//10
  pause(QN+QN);
  freqout(pin,EN,E3);
  pause(EN);
  //11
  freqout(pin,HN,F3);
  pause(QN);
  freqout(pin,QN+EN,B2);//12
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  //13
  freqout(pin,FN+HN,E3);//14
  pause(QN);
  freqout(pin,EN,E3);
  pause(EN);
  //15
  freqout(pin,HN,F3);
  pause(QN);
  freqout(pin,QN+EN,B2);//16
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,EN,B2);
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  }  
}

void mobamba3(){
  int pin = 4;
  while(1){
    pause(3*FN);//123
  //4
  pause(HN);
  pause(QN);
  freqout(pin,EN,B2);
  freqout(pin,EN,B2);
  //5
  freqout(pin,FN+QN,E3);//6
  pause(QN);
  freqout(pin,QN,E3);
  pause(QN);
  //7
  freqout(pin,HN,F3);
  pause(QN);
  freqout(pin,QN+QN,B2);//8
  pause(QN);
  freqout(pin,EN,B2);
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  //9
  freqout(pin,FN+QN,E3);//10
  pause(QN+QN);
  freqout(pin,EN,E3);
  pause(EN);
  //11
  freqout(pin,HN,F3);
  pause(QN);
  freqout(pin,QN+EN,B2);//12
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  //13
  freqout(pin,FN+HN,E3);//14
  pause(QN);
  freqout(pin,EN,E3);
  pause(EN);
  //15
  freqout(pin,HN,F3);
  pause(QN);
  freqout(pin,QN+EN,B2);//16
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,EN,B2);
  pause(EN);
  freqout(pin,SN,B2);
  pause(SN);
  freqout(pin,SN,B2);
  pause(SN);
  }  
}
int dance()
{
  pause(QUARTER_NOTE);
  pause(EIGHTH_NOTE);
  servo_speed(14,200);
  servo_speed(15,200);
  pause(QUARTER_NOTE);
  servo_speed(14,0);
  servo_speed(15,0);
  pause(QUARTER_NOTE);
  pause(EIGHTH_NOTE);
  servo_speed(14,-200);
  servo_speed(15,-200);
  pause(SIXTEENTH_NOTE);
  pause(SIXTEENTH_NOTE);
  pause(SIXTEENTH_NOTE);
  pause(EIGHTH_NOTE);
  pause(SIXTEENTH_NOTE);
  pause(SIXTEENTH_NOTE);
  pause(SIXTEENTH_NOTE);
  servo_speed(14,0);
  servo_speed(15,0);
  pause(EN);
  servo_speed(14,200);
  servo_speed(15,200);
  pause(EN);
  pause(EN);
  pause(EN);
  pause(EN);
  servo_speed(14,0);
  servo_speed(15,0);
  pause(EN);
  pause(EN);
  servo_speed(14,200);
  servo_speed(15,-200);
  pause(QN);
   pause(QUARTER_NOTE);
   servo_speed(14,0);
   servo_speed(15,0);
   pause(EIGHTH_NOTE);
   pause(QUARTER_NOTE);
   servo_speed(14,-200);
   servo_speed(15,200);
   pause(QUARTER_NOTE);
  //slur
   pause(EIGHTH_NOTE);
   pause(EIGHTH_NOTE);
   servo_speed(14,0);
   servo_speed(15,0);   
   pause(QUARTER_NOTE);
   servo_speed(14,-200);
   servo_speed(15,200);
   pause(QUARTER_NOTE);
   servo_speed(14,200);
   servo_speed(15,-200);
   pause(SIXTEENTH_NOTE);
   pause(QN);
   servo_speed(14,0);
   servo_speed(15,0);
   pause(SIXTEENTH_NOTE);
   pause(QUARTER_NOTE);//rest
   servo_speed(14,200);
   servo_speed(15,200);
   pause(QN);
   servo_speed(14,0);
   servo_speed(15,0);
   pause(QN);
   servo_speed(14,-200);
   servo_speed(15,-200);
   pause(QN);
   servo_speed(14,0);
   servo_speed(15,0);
   pause(SIXTEENTH_NOTE);
   pause(SIXTEENTH_NOTE);
   servo_speed(14,200);
   servo_speed(15,200);
   pause(QN);
   servo_speed(14,0);
   servo_speed(15,0);
   servo_speed(14,-200);
   servo_speed(15,-200);
   pause(QN);
   servo_speed(14,0);
   servo_speed(15,0);
   servo_speed(14,200);
   servo_speed(15,200);
   pause(QN);
   servo_speed(14,0);
   servo_speed(15,0);
   servo_speed(14,-200);
   servo_speed(15,-200);
   pause(QN);
   servo_speed(14,0);
   servo_speed(15,0);
}
  
int song1()
{
  int counter=0;
  int pin=0;
  while(counter<1)
  {
   freqout(pin,100,F6);
   pause(QUARTER_NOTE);
   freqout(pin,100,A6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,C7);
   pause(QUARTER_NOTE);
   freqout(pin,100,A6);
   pause(QUARTER_NOTE);
   freqout(pin,100,F6);
   pause(EIGHTH_NOTE);
   
   freqout(pin,100,D6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,D6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,D6);
   pause(SIXTEENTH_NOTE);
   pause(EIGHTH_NOTE);//rest
   
   freqout(pin,100,F7); //F1
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,F7); 
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,F7); 
   pause(SIXTEENTH_NOTE);
   pause(EIGHTH_NOTE);//rest
   
   freqout(pin,250,C6);//slur
   freqout(pin,100,D6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,F6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,A6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,C7);
   pause(EIGHTH_NOTE);
   freqout(pin,100,A6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,F6);
   pause(EIGHTH_NOTE);
   
  //slur
   freqout(pin,500,E7);
   freqout(pin,250,Ds7Eb7);
   freqout(pin,250,D7);
   
   pause(QUARTER_NOTE);//rest
   
   freqout(pin,100,Gs6Ab6);
   pause(QUARTER_NOTE);
   freqout(pin,100,C7);
   pause(EIGHTH_NOTE);
   freqout(pin,100,F6);
   pause(QUARTER_NOTE);
   freqout(pin,100,C7);
   pause(QUARTER_NOTE);
   //try to slur
   freqout(pin,250,Gs6Ab6);
   freqout(pin,250,G6);
   freqout(pin,100,C7);
   pause(EIGHTH_NOTE);
   freqout(pin,100,G6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,F6);
   pause(QUARTER_NOTE);
   freqout(pin,100,E6);
   pause(QUARTER_NOTE);
   freqout(pin,100,E6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,E6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,E6);
   pause(QUARTER_NOTE);//rest
   freqout(pin,100,E6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,E6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,E6);
   pause(1000);
   counter++;
  }  
  return;
}  
int song2()
{
  int counter=0;
  int pin=6;
  while(counter<1)
  {
   freqout(pin,100,F6);
   pause(QUARTER_NOTE);
   freqout(pin,100,A6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,C7);
   pause(QUARTER_NOTE);
   freqout(pin,100,A6);
   pause(QUARTER_NOTE);
   freqout(pin,100,F6);
   pause(EIGHTH_NOTE);
   
   freqout(pin,100,D6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,D6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,D6);
   pause(SIXTEENTH_NOTE);
   pause(EIGHTH_NOTE);//rest
   
   freqout(pin,100,F7); //F1
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,F7); 
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,F7); 
   pause(SIXTEENTH_NOTE);
   pause(EIGHTH_NOTE);//rest
   
   freqout(pin,250,C6);//slur
   freqout(pin,100,D6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,F6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,A6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,C7);
   pause(EIGHTH_NOTE);
   freqout(pin,100,A6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,F6);
   pause(EIGHTH_NOTE);
   
  //slur
   freqout(pin,500,E7);
   freqout(pin,250,Ds7Eb7);
   freqout(pin,250,D7);
   
   pause(QUARTER_NOTE);//rest
   
   freqout(pin,100,Gs6Ab6);
   pause(QUARTER_NOTE);
   freqout(pin,100,C7);
   pause(EIGHTH_NOTE);
   freqout(pin,100,F6);
   pause(QUARTER_NOTE);
   freqout(pin,100,C7);
   pause(QUARTER_NOTE);
   //try to slur
   freqout(pin,250,Gs6Ab6);
   freqout(pin,250,G6);
   freqout(pin,100,C7);
   pause(EIGHTH_NOTE);
   freqout(pin,100,G6);
   pause(EIGHTH_NOTE);
   freqout(pin,100,F6);
   pause(QUARTER_NOTE);
   freqout(pin,100,E6);
   pause(QUARTER_NOTE);
   freqout(pin,100,E6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,E6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,E6);
   pause(QUARTER_NOTE);//rest
   freqout(pin,100,E6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,E6);
   pause(SIXTEENTH_NOTE);
   freqout(pin,100,E6);
   pause(1000);
   counter++;
  }  
  return;
}
///////////***MUSIC***/////////////
