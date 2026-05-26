//=========================================================
// File Projectile.cpp
// Shooting a projectile near the earth surface.
// No air resistance.
// Starts at (0,0), set (v0,theta).
//---------------------------------------------------------
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#define PI 3.1415926535897932
#define g 9.81

int main() {
  //-----------------------------------------------------
  // Declaration of variables
  double x0, y0, R, x, y, vx, vy, t, tf, dt;
  double theta, v0x, v0y, v0;
  string buf;
  //-----------------------------------------------------
  // Ask user fo input:
  cout << "# Enter v0, theta (in degrees):\n";
  cin >> v0 >> theta;
  getline(cin, buf);
  cout << "# Enter tf, dt:\n";
  cin >> tf >> dt;
  getline(cin, buf);
  cout << "# v0= " << v0 << " theta= " << theta << "o (degrees)" << endl;
  cout << "# t0= " << 0.0 << " tf= " << tf << " dt= " << dt << endl;
  //-----------------------------------------------------
  // Initialize
  if (v0 <= 0.0) {
    cerr << "Illegal value of v0 <=0\n";
    exit(1);
  }
  if (theta <= 0.0) {
    cerr << "Illegal value of theta <=0\n";
    exit(1);
  }
  if (theta >= 90.0) {
    cerr << "Illegal value of theta >=90\n";
    exit(1);
  }
  theta = (PI / 180) * theta; // convert to radians
  v0x = v0 * cos(theta);
  v0y = v0 * sin(theta);
  cout << "# v0x= " << v0x << " v0y= " << v0y << endl;
  ofstream myfile("Projectile.dat");
  myfile.precision(17);
  //-----------------------------------------------------
  // Compute:
  t = 0.0;
  while (t <= tf) {
    x = v0x * t;
    y = v0y * t - 0.5 * g * t * t;
    vx = v0x;
    vy = v0y - g * t;
    myfile << t << " " << x << " " << y << " " << vx << " " << vy << endl;
    t = t + dt;
  }
} // main()
