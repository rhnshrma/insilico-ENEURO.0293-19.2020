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

#ifndef INCLUDED_I_KahpS_CA1_HPP
#define INCLUDED_I_KahpS_CA1_HPP

#include "insilico/core/engine.hpp"
#include "vtrap.cpp"

namespace insilico {


class I_KahpS_CA1 {

 public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index) {
    double gk = 0.8, ek = -15;
                                                            // Declaring Constants
    unsigned v_soma_index = engine::neuron_index(index, "v_soma");
    unsigned q_soma_index = engine::neuron_index(index, "q_KahpS");
    unsigned Ca_soma_index = engine::neuron_index(index, "CaS");

    double v = variables[v_soma_index];
    double q = variables[q_soma_index];
    double Ca = variables[Ca_soma_index];


                                                            // Calculating time constants
    double alpha_q = std::min(0.00002*Ca,0.01);
    double beta_q = 0.001;

    double q_inf=alpha_q/(alpha_q+beta_q);
    double tau_q=1/(alpha_q + beta_q);

    if (q>1) variables[q_soma_index]=1;
    else if(q<0) q=0;
    
    
                                                            // ODE set
    dxdt[q_soma_index] = (q_inf - q)/tau_q;


                                                            // Current
    engine::neuron_value(index,"I_KahpS",(-1*(gk*q* (v - ek))));

  } // function current

 


}; // class I_potassium_RE





} // insilico



#endif
