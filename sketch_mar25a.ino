
#include <Servo.h>
#include <math.h>

Servo swiper,bobber;
float x,y, bob, swi;

void setup() {
  swiper.attach(6);
  bobber.attach(9);

  // laser
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

float h = 0.5;
float pi = 3.141592;

// bobber should go from 0(in front) to 90 (its base)
int getBob(float x, float y){
  float r = sqrt(x*x+y*y);
  float s = atan(r/h);
  return (90*(pi/2-s)/(pi/2));
}
// swiper should go from 90 (in front) to 180 (its left)
int getSwipe(float x, float y){
  float s = atan(x/y);
  return floor(90 + 90 * s / (pi/2));
}

bool isOk(float x, float y){
  if(x < 0 && y > 2.5){
    return false;
  }
  if (x< -0.8){
    return false;
  }
  return true;
};

float getX(){
  return (random(400)-100)/100;
}
float getY(){
  return (random(300))/100;
}

// x in [-3;3], y in [0;3]
void go(float x, float y){
  y+= 0.3;
  bob = getBob(x, y);
  swi = getSwipe(x, y);
  bobber.write(bob);
  swiper.write(swi);
}

float wait(){
  delay(1500+random(10000));
}

void teleport(){
  x = getX();
  y = getY();
  if (isOk(x,y)){
    go(x, y);
  }
}
void goRand(){
  float newx = getX();
  float newy = getY();
  float steps = 10 + random(1000);

  if (isOk(newx,newy)){
    go(newx, newy);
    float stepx = (newx - x)/steps;
    float stepy = (newy - y)/steps;
    for(int i = 0; i < steps; i++){
      go(x+ stepx*i, y+ stepy*i);
      delay(10);
    }

    x = newx;
    y = newy;
  }
}

void shake(){
  for(int j = 0 ; j < 2+random(10); j++){
    for(float i = 0;i <= 10; i ++){
      bobber.write(bob+i);
      delay(10);
    }
    for(float i = 10;i >= 0; i --){
      bobber.write(bob+i);
      delay(10);
    }
  }
}

void blink(){
  for(int j = 0 ; j < 2+random(10); j++){
    digitalWrite(13, LOW);
    delay(200);
    digitalWrite(13, HIGH);
    delay(200);
  }
}

void loop() {
  switch(random(6)){
    case(0):
      teleport();
      break;
    case(1):
      goRand();
      break;
    case(2):
      blink();
      break;
    default:
      shake();
      break;

  }
  wait();
}
