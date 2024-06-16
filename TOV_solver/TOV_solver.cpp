/***   ***   ***   ***
 Author: Joshua Maldonado
 ***   ***   ***   ***/

// imports
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool oddQ(int value){
	if (value%2 == 0){
		return false;
	}
	else{
		return true;
	}
}


void rk4_for_first_order_ODE(double x*, double y*, double *ypr){

}


int main(){
    cout << boolalpha;
    //cout << "" << endl;

	cout << "enter desired value: ";
	int current_value;
	cin >> current_value;
	while (current_value != 1){
		current_value = collatz(current_value);
		cout << "current_value = " << current_value << endl;
	}

    return EXIT_SUCCESS;
}
