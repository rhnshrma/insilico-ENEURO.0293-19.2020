/*
 current/I_KdS_CA1.hpp - Current flowing across neuronal membrane due to
                          Potassium direct (K-dr) conductance. (Ferguson et al., 2009)

 Copyright (C) 2017 Rohan Sharma, Suhita Nadkarni Lab, IISER, Pune <rohan.sharma@students.iiserpune.ac.in>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 Brief:

 Current that flows through Potassium (Kd) channel due to the potential difference
 caused by Potassium (Kd) conductance across neuronal membrane. (Ferguson, 2009)
*/

#ifndef INCLUDED_I_KdS_CA1_HPP
#define INCLUDED_I_KdS_CA1_HPP

#include "insilico/core/engine.hpp"
#include "vtrap.cpp"

namespace insilico {


class I_KdS_CA1 {

 public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index) {
    double gk = 15.0, ek = -15;
                                                            // Declaring Constants
    unsigned v_soma_index = engine::neuron_index(index, "v_soma");
    unsigned n_soma_index = engine::neuron_index(index, "n_KdS");

    double v = variables[v_soma_index];
    double n = variables[n_soma_index];


                                                            // Calculating time constants
    double alpha_n = 0.016*vtrap((35.1 -v),5.0);
    double beta_n = 0.25*exp(0.5 - 0.025*v);

    double n_inf=alpha_n/(alpha_n+beta_n);
    double tau_n=1/(alpha_n + beta_n);

    if (n>1) variables[n_soma_index]=1;
    else if(n<0) n=0;
    
    
                                                            // ODE set
    dxdt[n_soma_index] = (n_inf - n)/tau_n;


                                                            // Current
    engine::neuron_value(index,"I_KdS",(-1*(gk * pow(n,1) * (v - ek))));

  } // function current

 


}; // class I_potassium_RE





} // insilico



#endif
