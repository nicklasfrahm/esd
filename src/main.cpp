#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>

using namespace std;

const int N = 40;
const int HAF = 10; // Hill Adjust Factor
//                  0   1   2   3   4   5   6   7   8   9
double hill[N] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 2, 2, 1, 0, 0, 0, 0, 0, 0,
    1, 2, 3, 4, 3, 2, 1, 0, 0, 0,
    0, -1, -2, -3, -4, -5, -3, 0, 0, 0
    // fill in more numbers, if you like, but remember to adjust N
};

class Car
{
public:
  static double get_speed(double fi)
  {
    static int i = 0;
    s = s + (fi                               // fuel injection 0..100
             - f * s * s                      // air friction
             - s * ff                         // wheel friction
             - HAF * (i++ < N ? hill[i] : 0)) // hill slope adjust
                / m;                          // car mass adjust
    if (s < 1)
      s = 0;        // to bring car to standstill
    return s * 3.6; // from m/s to km/h
  }

private:
  static double s;  // speed in m/s
  static double m;  // "mass of car"
  static double f;  // air friction
  static double ff; // wheel friction
                    //static double rpm;
};
double Car::s = 0;
double Car::m = 8;
double Car::f = 1.0 / 49.0;
double Car::ff = 0.1;

int main()
{
  int a = 0, i = 0;
  int fi = 0;
  char prev_ch = 'a';
  bool repeat = true;
  while (repeat)
  {
    cout << endl
         << "s: " << i
         << " fuelinjection: " << fi
         << " Hill: " << ((i < N) ? hill[i++] : 0)
         << " speed: " << Car::get_speed(fi);
    Sleep(1000); // one second

    if (_kbhit())
    {
      char ch = _getch();
      switch (ch)
      {
      case 27: // press ESC to exit
        repeat = false;
        break;
      case 32: // press SPACE to clear screen
        //clrscr();
        //clr_scr();
        break;
      case 'a': // accelerate
        //if (a == 0) a = 1;dddd
        if (prev_ch == 'a')
          a++;
        else
          a = 1;
        fi = fi + a;
        if (fi > 100)
          fi = 100;
        //cout << fi <<" ";
        break;
      case 'd': // decellerate
        if (prev_ch == 'd')
          a--;
        else
          a = -1;
        fi = fi + a;
        if (fi < 0)
          fi = 0;
        //cout << fi << " ";
        break;
      case 's': // hold speeder level

        break;
      case 'b': // brake
        fi = 0;
        break;
      case 'c': // clutch
        fi = 0;
        break;
      case 'g': // gear one down
        fi = 0;
        break;
      case 'h': // gear one up
        fi = 0;
        break;
      default:
        fi = 0;
      }
      prev_ch = ch;
    }
    else
    {
      prev_ch = '0';
      fi = 0;
    }
  }
  return 0;
}