#include <iostream>

using namespace std;

int main() {
    int user_inputs;
    cout << "Enter number of sensor readings: ";
    cin >> user_inputs;
    cout << endl;
    float smallest_dist;

    vector<float> inputs(user_inputs, 0);

    for (int i = 0; i < user_inputs; i++)
    {
        int input;
        cout << "Enter distance reading " << i+1 << " (cm) ";
        cin >> input;
        if (i == 0) {
            smallest_dist = input;
        } else {
            if (input < smallest_dist) {
                smallest_dist = input;
            }
        }
        inputs[i] = input;
        cout << endl;
    }

    cout << "Distance readings:";
    for (int i = 0; i < user_inputs; i++)
    {
        int input;
        cout << " " << inputs[i];
    }
    cout << endl;
    cout << "Closest obstacle (min): " << smallest_dist << " cm";
}