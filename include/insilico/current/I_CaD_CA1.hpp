/*
 current/I_KdS_CA1.hpp - Current flowing across neuronal membrane due to
                          Calcium (Ca-S) conductance. (Ferguson et al., 2009)

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

 Current that flows through Calcium dend (CaS) channel due to the potential difference
 caused by Calcium dend (CaS) conductance across neuronal membrane. (Ferguson et al., 2009)
*/

#ifndef INCLUDED_I_CaD_CA1_HPP
#define INCLUDED_I_CaD_CA1_HPP

#include "insilico/core/engine.hpp"
#include "vtrap.cpp"

namespace insilico {


class I_CaD_CA1 {

 public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index) {
    double gCa = 5.0, eCa = 140, beta_Ca = 0.075, phi = engine::neuron_value(index,"phi_D");
                                                            // Declaring Constants
    unsigned v_dend_index = engine::neuron_index(index, "v_dend");
    unsigned s_dend_index = engine::neuron_index(index, "s_CaD");
    unsigned Ca_dend_index = engine::neuron_index(index, "CaD");

    double v = variables[v_dend_index];
    double s = variables[s_dend_index];
    double Ca = variables[Ca_dend_index];

    // Calculating time constants
   
    double alpha_s = 1.6/(1 + exp(-0.72*(v - 65)));
    double beta_s = 0.02*vtrap((v - 51.1),5.0);
 

    double s_inf=alpha_s/(alpha_s+beta_s);
    double tau_s=1/(alpha_s + beta_s);

    if (s>1) variables[s_dend_index]=1;
    else if(s<0) s=0;
    
    


                                                            // Current
    double I_CaD = -1*gCa*pow(s,2)*(v - eCa);
    engine::neuron_value(index,"I_CaD",I_CaD);

                                                            // ODE set
    dxdt[s_dend_index] = (s_inf - s)/tau_s;
    dxdt[Ca_dend_index] = phi*I_CaD - Ca*beta_Ca;
  } // function current


 


}; // class I_potassium_RE





} // insilico



#endif
