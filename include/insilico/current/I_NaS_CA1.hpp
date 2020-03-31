/*
 current/I_NAS_CA1.hpp - Current flowing across neuronal membrane due to
                          Sodium (Na) conductance. (Ferguson et al., 2009)

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

 Current that flows through Sodium (Na) channel due to the potential difference
 caused by Sodium (Na) conductance across neuronal membrane. (Pinsky Rinzel, 1994)
*/

#ifndef INCLUDED_I_NA_CA1_HPP
#define INCLUDED_I_NA_CA1_HPP

#include "insilico/core/engine.hpp"
#include "vtrap.cpp"


namespace insilico {

class I_NaS_CA1 {
 public:
   static void current(state_type &variables, state_type &dxdt, const double t, unsigned index) {
    double gna = 30.0, ena = 120.0;
                                                            // Declaring Constants
    unsigned v_soma_index = engine::neuron_index(index, "v_soma");
    unsigned h_soma_index = engine::neuron_index(index, "h_NaS");
    unsigned m_soma_index = engine::neuron_index(index, "m_NaS");

    double v = variables[v_soma_index];
    double h = variables[h_soma_index];
    double m = variables[m_soma_index];

                                                            // Calculating Time Constants

    double alpha_m = 0.32*vtrap((13.1-v),4.0);
    double beta_m  = 0.28*vtrap((v-40.1),5.0);

    double alpha_h = 0.128*exp((17-v)/18.0);
    double beta_h  = 4.0/(1.0 +exp((40-v)/5.0));



    double h_inf = alpha_h/(alpha_h+beta_h);
    double tau_h = 1/(alpha_h + beta_h);

    double m_inf = alpha_m/(alpha_m+beta_m);
    double tau_m = 1/(alpha_m + beta_m);

    if (m<0) variables[m_soma_index] = 0;  
    else if (m>1) variables[m_soma_index] = 1;  
    if (h<0) variables[h_soma_index] = 0;
    else if (h>1) variables[h_soma_index] = 1;  
                                                            // ODE set
    dxdt[m_soma_index] = (m_inf - m)/tau_m;
    dxdt[h_soma_index] = (h_inf - h)/tau_h;


     // Current
    engine::neuron_value(index, "I_NaS", (-1*(gna*pow(m_inf,2)*h*(v-ena))));

  } // function current
}; // class I_T-current_RE cells

} // insilico

#endif


