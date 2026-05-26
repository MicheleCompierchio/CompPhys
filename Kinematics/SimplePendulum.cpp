//=========================================================
// File SimplePendulum.cpp
// Set pendulum original position at theta0
// with no initial speed
//---------------------------------------------------------
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#define PI 3.141592653587932
#define g 9.81

int main() {
  //-----------------------------------------------------
  // Declaration of variables
  double l, x, y, vx, vy, t, t0, tf, dt;
  double theta, theta0, dtheta_dt, omega;
  string buf;
  //---------------------------------------------------------
  // Ask user for input
  cout << "# Enter l:\n";
  cin >> l;
  getline(cin, buf);
  cout << "# Enter theta0:\n";
  cin >> theta0;
  getline(cin, buf);
  cout << "# Enter t0, tf, dt:\n";
  cin >> t0 >> tf >> dt;
  getline(cin, buf);
  cout << "# l= " << l << " theta0= " << theta0 << endl;
  cout << "# t0= " << t0 << " tf= " << tf << "dt= " << dt << endl;
  //---------------------------------------------------------
  // Initialize
  omega = sqrt(g / l);
  cout << "# omega= " << omega << " T= " << 2.0 * PI / omega << endl;
  ofstream myfile("SimplePendulum.dat");
  myfile.precision(17);
  //---------------------------------------------------------
  // Compute:
  t = t0;
  while (t <= tf) {
    theta = theta0 * cos(omega * (t - t0));
    dtheta_dt = -omega * theta0 * sin(omega * (t - t0));
    x = l * sin(theta);
    y = -l * cos(theta);
    vx = l * dtheta_dt * cos(theta);
    vy = l * dtheta_dt * sin(theta);
    myfile << t << " " << x << " " << y << " " << vx << " " << vy << " "
           << theta << dtheta_dt << endl;
    t = t + dt;
  }

} // main()
