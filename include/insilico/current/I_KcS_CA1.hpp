/*
 current/I_KdS_CA1.hpp - Current flowing across neuronal membrane due to
                          Potassium (K-c) conductance. (Ferguson et al., 2009)

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

 Current that flows through Potassium (K) channel due to the potential difference
 caused by Potassium (K) conductance across neuronal membrane. (Ferguson et al., 2009)
*/

#ifndef INCLUDED_I_KcS_CA1_HPP
#define INCLUDED_I_KcS_CA1_HPP

#include "insilico/core/engine.hpp"
#include "vtrap.cpp"

namespace insilico {


class I_KcS_CA1 {

 public:
  static void current(state_type &variables, state_type &dxdt, const double t, unsigned index) {
    double gk = 15.0, ek = -15;
                                                            // Declaring Constants
    unsigned v_soma_index = engine::neuron_index(index, "v_soma");
    unsigned c_soma_index = engine::neuron_index(index, "c_KcS");
    unsigned Ca_soma_index = engine::neuron_index(index, "CaS");

    double v = variables[v_soma_index];
    double c = variables[c_soma_index];
    double Ca = variables[Ca_soma_index];

    // Calculating time constants
    double alpha_c=0, beta_c=0;
    if(v > 50){                                                        
        
        alpha_c = 2*exp((6.5 - v)/27);
        beta_c = 0;
    }
    else{
        
        alpha_c = exp(((v - 10)/11) - ((v - 6.5)/27))/18.975;
        beta_c = 2*exp((6.5 - v)/27) - alpha_c;

    }

    double c_inf=alpha_c/(alpha_c+beta_c);
    double tau_c=1/(alpha_c + beta_c);

    if (c>1) variables[c_soma_index]=1;
    else if(c<0) c=0;
    
    
                                                            // ODE set
    dxdt[c_soma_index] = (c_inf - c)/tau_c;


                                                            // Current
    engine::neuron_value(index,"I_KcS",(-1*(gk * c * std::min(1.00,Ca/250)*(v - ek))));

  } // function current
    

 


}; // class I_potassium_RE





} // insilico



#endif
