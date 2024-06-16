/***   ***   ***   ***
 Author: Joshua Maldonado
 ***   ***   ***   ***/

// imports
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;


// this is just the numpy function since I guess that's not built into c++?
void linspace(double x_initial, double x_final, int n, double x_array[]){
    const double dx = (x_final - x_initial) / (n - 1);

    for (int i = 0; i < n; i++){
        x_array[i] = i * dx + x_initial;
        }
    }


template <typename callable>
void rk4_for_first_order_ODE(int n, double x[], double y[], double y0, double y0_pr, callable ode_func){
    /***   ***   ***   ***   ***   ***   ***   ***
    C++ implementation of first_order_rk4()
    function in python. This function will
    populate the given y array.

    Parameters
    ----------
    n : int
        The length of the x and y arrays
    x : pointer to array of doubles
        The mesh for the ode
    y : pointer to array of doubles
        The to-be-populated array for the
        solution to the ODE
    y0 : double
        The initial value of the ODE.
    y0_pr : double
        The initial value of the derivative of
        the ODE.
    ode_func : callable
        The function for which the ODE will be
        solved. Should be of the form:
        d/dx y = ode_func(x, y)
     ***   ***   ***   ***   ***   ***   ***   ***/
    const double dx = x[1] - x[0];  // THIS ASSUMES A UNIFORM ARRAY !!
    const double half_dx = dx / 2;

    // initialize y value(s)
    y[0] = y0;
    y[1] = y0_pr;


    double F_1;
    double F_2;
    double F_3;
    double F_4;
    // solve the ode given the ode_func
    for (int i = 1; i < n; i++){
        F_1 = dx * ode_func(x[i], y[i]);
        F_2 = dx * ode_func(x[i] + half_dx, y[i] + F_1 / 2);
        F_3 = dx * ode_func(x[i] + half_dx, F_2 / 2);
        F_4 = dx * ode_func(x[i+1], y[i] + F_3);

        y[i + 1] = ode_func(x[i], y[i]) + ((1 / 6) * (F_1 + 2 * F_2 + 3 * F_3 + F_4));
        }
    }

double test_ode_func(double x, double y){
    return sin(x);
    }


int array_to_file(double str_array[], int array_len, string file_name)
{
	ofstream my_out_stream;
	my_out_stream.open(file_name);

	int tot = 0;
	for (int i = 0; i < array_len; i++)
	{
		my_out_stream << str_array[i] << endl;
		tot = i + 1;
	}

	return tot;
}

int main(){
    const int n = 500;
    const double x_initial = 0.;
    const double x_final = 10.;
    const double dx = (x_final - x_initial) / (n - 1);
    double x[n];
    const double y0 = 0.;
    const double y0_pr = dx;
    double y[n];

    linspace(x_initial, x_final, n, x);  // make sure that x is actually useable
    rk4_for_first_order_ODE(n, x, y, y0, y0_pr, test_ode_func);

    // now that we've populated y, lets write it to a file
    array_to_file(y, n, "test_file.txt");


    return EXIT_SUCCESS;
    }
