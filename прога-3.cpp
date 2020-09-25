#include "TXLib.h"
#include <math.h>
#include <string>


struct Vector2i
 {
   int x;
   int y;
 };

struct Color3j
 {
   int Red;
   int Green;
   int Blue;
 };

struct Sphere
 {
   Vector2i position;
   Vector2i velocity;
   int R;
   Color3j color;
   Vector2i refractaire;
 };

void drawSphere(Sphere sphere)
 {
   txBegin();

   txSetColor(RGB(sphere.color.Red, sphere.color.Green, sphere.color.Blue));
   txSetFillColor(RGB(sphere.color.Red, sphere.color.Green, sphere.color.Blue));
   txCircle(sphere.position.x, sphere.position.y, sphere.R);

   txEnd();

   txSetFillColor(RGB(0, 0, 0));

 };

 void moveSphere(Sphere *sphere, float t)
 {
   (*sphere).position.x += (*sphere).velocity.x*t;
   (*sphere).position.y += (*sphere).velocity.y*t;
 };

 void checkCollision(Sphere *sphere)
  {
    (*sphere).refractaire.x -= 1;
    (*sphere).refractaire.y -= 1;

    if((*sphere).refractaire.x < 0 and (*sphere).refractaire.y < 0)
      {


        if((*sphere).position.x > (900 - (*sphere).R) or (*sphere).position.x < (*sphere).R)
          {
            (*sphere).velocity.x = -(*sphere).velocity.x;
            (*sphere).refractaire.x = 3;
          };

        if((*sphere).position.y > (900 - (*sphere).R)  or (*sphere).position.y < (*sphere).R)
          {
            (*sphere).velocity.y = -(*sphere).velocity.y;
            (*sphere).refractaire.y = 3;
          };
      };
  };

void CheckCollisionTwoSpheres(Sphere *OneSphere, Sphere *TwoSphere)
  {
    if(pow(((*OneSphere).position.x - (*TwoSphere).position.x), 2) + pow(((*OneSphere).position.y - (*TwoSphere).position.y), 2) < ((*OneSphere).R + 20) * ((*TwoSphere).R + 20))
      {
        (*OneSphere).velocity.x, (*TwoSphere).velocity.x = -(*TwoSphere).velocity.x, -(*OneSphere).velocity.x;
        (*OneSphere).velocity.y, (*TwoSphere).velocity.y = -(*TwoSphere).velocity.y, -(*OneSphere).velocity.y;
      };
  };


bool CheckEndOfTheGame(Sphere *OneSphere, Sphere *TwoSphere)
  {
    if(pow(((*OneSphere).position.x - (*TwoSphere).position.x), 2) + pow(((*OneSphere).position.y - (*TwoSphere).position.y), 2) < ((*OneSphere).R + 20) * ((*TwoSphere).R + 20))
      {
        return true;
      };
  };




int main()
  {
    txCreateWindow(900, 900);
    txSetFillColor(RGB(0, 0, 0));

    float t = 1;


    Sphere sp1 = {{200, 300},{24,63}, 50, {0, 100, 10}, {0, 0}};
    Sphere sp2 = {{200, 300},{45,18}, 50, {100, 10, 0}, {0, 0}};



    while (true)
      {
        txClear();

        Sphere gamer = {{txMouseX(), txMouseY()}, {0, 0}, 50, {100, 100, 100}, {0, 0}};

        drawSphere(gamer);

        moveSphere(&sp1, t);
        drawSphere(sp1);
        checkCollision(&sp1);

        moveSphere(&sp2, t);
        drawSphere(sp2);
        checkCollision(&sp2);

        CheckCollisionTwoSpheres(&sp1, &sp2);

        if(CheckEndOfTheGame(&gamer, &sp1))
          {
            std::cout << "You win" << std::endl;
            break;
          };

        if(CheckEndOfTheGame(&gamer, &sp2))
          {
            std::cout << "You lose" << std::endl;
            break;
          };



      };



 return 0;
}

