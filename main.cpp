#include <iostream>
#include <vector>

using namespace std;

// y'' + c/m y' + k/m y = F(external) = 0
// m = mass
// k = spring constant
// c = damping force


class SpringMass
{
public:
    float x; // position 
    float m; // mass on spring
    float k; // spring constant
    float c; // damping force
    float F; // external force

};




int main()
{
    cout << "hello" << endl;
    return 0;
}
