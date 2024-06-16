import numpy as np
from numba import njit


c = 299792458  # m/s
hbar_joules_per_second = 1.054571817 * 1e-34  # J/s
hbar_eV_per_second = 6.582119569 * 1e-16  # eV/s

hbarc = 197.326  # MeV fm
neutron_mass = 939.565  # MeV

G = 6.67430 * 1e-11  # N m^2 / kg^2


@njit(fastmath=True)
def first_order_rk4(x: np.array, y0: float, y0_pr: float, ode_func, *ode_func_args):
    """
    rk4 solver using the equations that I
    shamelessly ripped from:
    https://www.intmath.com/differential-equations/12-runge-kutta-rk4-des.php
    
    Parameters
    ----------
    x : numpy array
        Mesh for solver
    y0 : number
        Initial point for y
    y0_pr : number
        Initial value for derivative
    ode_func : function
        The function that will be solved.
        The form should be:
        d^2/dx^2 y = ode_func(x, y, *ode_func_args)
    ode_func_args : tuple (optional)
        Args for ode_func
    
    Returns
    -------
    y_pr : numpy array
        The solution to the given ODE as given by
        rk4.
    """
    n = len(x)
    dx = x[1] - x[0]  # THIS ASSUMES A LINEAR MESH !!
    half_dx = dx / 2
    # initialize return array & set initial value(s)
    y = np.empty(n)
    y[0] = y0
    y[1] = y0_pr
    
    for i in np.arange(1, n-1):
        F_1 = dx * ode_func(x[i], y[i], *ode_func_args)
        F_2 = dx * ode_func(x[i] + half_dx, y[i] + F_1 / 2, *ode_func_args)
        F_3 = dx * ode_func(x[i] + half_dx, F_2 / 2, *ode_func_args)
        F_4 = dx * ode_func(x[i+1], y[i] + F_3, *ode_func_args)
        
        y[i + 1] = ode_func(x[i], y[i], *ode_func_args) + ((1 / 6) * (F_1 + 2 * F_2 + 3 * F_3 + F_4))
    
    return y