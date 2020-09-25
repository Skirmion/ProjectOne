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
   int radius;
   Color3j color;
   Vector2i refractaire;
 };

void drawSphere(Sphere sphere)
 {
   txBegin();

   for(int i = 0; i < 100; i += 1)
     {
       txSetColor(RGB(sphere.color.Red*i/60, sphere.color.Green*i/60, sphere.color.Blue*i/60));
       txSetFillColor(RGB(sphere.color.Red*i/60, sphere.color.Green*i/60, sphere.color.Blue*i/60));
       txCircle(sphere.position.x + sphere.velocity.x * i/200 , sphere.position.y + sphere.velocity.y *i/200, sphere.radius - sphere.radius*i/100 );
     };
   txEnd();

   txSetFillColor(RGB(0, 0, 0));

 };

 void moveSphere(Sphere *sphere, float t)
 {
   (*sphere).position.x += (*sphere).velocity.x * t;
   (*sphere).position.y += (*sphere).velocity.y * t;
 };

 void checkCollision(Sphere *sphere)
  {
    (*sphere).refractaire.x -= 1;
    (*sphere).refractaire.y -= 1;

    if((*sphere).refractaire.x < 0 and (*sphere).refractaire.y < 0)
      {


        if((*sphere).position.x > (900 - (*sphere).radius) or (*sphere).position.x < (*sphere).radius)
          {
            (*sphere).velocity.x = -(*sphere).velocity.x;
            (*sphere).refractaire.x = 3;
          };

        if((*sphere).position.y > (900 - (*sphere).radius)  or (*sphere).position.y < (*sphere).radius)
          {
            (*sphere).velocity.y = -(*sphere).velocity.y;
            (*sphere).refractaire.y = 3;
          };
      };
  };

bool ballsDangerouslyClose(Sphere onesphere, Sphere twosphere)
  {
    if(pow(((onesphere).position.x - (twosphere).position.x), 2) + pow(((onesphere).position.y - (twosphere).position.y), 2) < ((onesphere).radius + 20) * ((twosphere).radius + 20))
      {
        return true;
      };
    return false;
  };

void checkCollisionTwoSpheres(Sphere *onesphere, Sphere *twosphere)
  {
    if(ballsDangerouslyClose(*onesphere, *twosphere))
      {
        (*onesphere).velocity.x, (*twosphere).velocity.x = -(*twosphere).velocity.x, -(*onesphere).velocity.x;
        (*onesphere).velocity.y, (*twosphere).velocity.y = -(*twosphere).velocity.y, -(*onesphere).velocity.y;
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

        checkCollisionTwoSpheres(&sp1, &sp2);

        if(ballsDangerouslyClose(gamer, sp1))
          {
            std::cout << "You win" << std::endl;
            break;
          };

        if(ballsDangerouslyClose(gamer, sp2))
          {
            std::cout << "You lose" << std::endl;
            break;
          };



      };



 return 0;
}

