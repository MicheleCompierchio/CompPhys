//==============================================================
// File Circle.cpp
// Constant angular velocity motion
// Set (x0,y0) center of circle, its radius R and omega.
// At t=t0, the particle is at theta=0
//--------------------------------------------------------------
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#define PI 3.1415926535897932

int main() {
  //--------------------------------------------------------------
  // Declaration of variables
  double x0, y0, R, x, y, vx, vy, t, t0, tf, dt;
  double theta, omega;
  string buf;
  //--------------------------------------------------------------
  // Ask user for input:
  cout << "# Enter omega:\n";
  cin >> omega;
  getline(cin, buf);

  cout << "# Enter center of circle (x0,y0) and radius R:\n";
  cin >> x0 >> y0 >> R;
  getline(cin, buf);

  cout << "# Enter t0,tf,dt:\n";
  cin >> t0 >> tf >> dt;
  getline(cin, buf);

  cout << "# omega= " << omega << endl;
  cout << "# x0= " << x0 << " y0= " << y0 << " R= " << R << endl;
  cout << "# t0= " << t0 << " tf= " << tf << " dt= " << dt << endl;
  //--------------------------------------------------------------
  // Initialize
  if (R <= 0.0) {
    cerr << "Illegal value of R \n";
    exit(1);
  }

  if (omega <= 0.0) {
    cerr << "Illegal value of omega \n";
    exit(1);
  }
  cout << "# T= " << 2.0 * PI / omega << endl;
  ofstream myfile("Circle.dat");
  //--------------------------------------------------------------
  // Compute
  t = t0;
  while (t <= tf) {
    theta = omega * (t - t0);
    x = x0 + R * cos(theta);
    y = y0 + R * sin(theta);
    vx = -omega * R * sin(theta);
    vy = omega * R * cos(theta);
    myfile << t << " " << x << " " << y << " " << vx << " " << vy << endl;
    t = t + dt;
  }
} // main()
