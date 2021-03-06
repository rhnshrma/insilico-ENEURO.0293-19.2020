/*
 neuron/N_LTS.hpp - Hodgkin-Huxley Squid Axon experiment (Hodgkin-Huxley, 1952)

 Copyright (C) 2014 Pranav Kulkarni, Collins Assisi Lab, IISER, Pune <pranavcode@gmail.com>

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

#ifndef INCLUDED_N_LTS_HPP
#define INCLUDED_N_LTS_HPP

#include "core/engine.hpp"

#include "current/I_Na_PY.hpp"
#include "current/I_K_PY.hpp"
#include "current/I_Leak_PY.hpp"
#include "current/I_M_LTS.hpp"

namespace insilico {

class N_LTS{
 public:
   void operator()(const state_type &variables, state_type &dxdt, const double t, int index) {
    int v_index = engine::neuron_index(index, "v");
    

    double v = variables[v_index];
    vector<int> g1_indices = engine::get_pre_neuron_indices(index, "g1");
    vector<double> gsyn = engine::get_pre_neuron_values(index, "gsyn");
    float I_Syn = 0;
    vector<double> esyn = engine::get_pre_neuron_values(index, "esyn");
    

    for(vector<int>::size_type iterator = 0; iterator < g1_indices.size(); ++iterator) {
      I_Syn = I_Syn + variables[g1_indices.at(iterator)]*gsyn.at(iterator)*(v - esyn.at(iterator)); 
    }

    float I_Na = I_Na_PY::current(variables, dxdt, t, index);
    float I_K = I_K_PY::current(variables, dxdt, t, index);
    float I_Leak = I_Leak_PY::current(variables, dxdt, t, index);
    float I_Ext = engine::neuron_value(index, "iext");
    float I_m = I_M_LTS::current(variables, dxdt, t, index);

    // ODE
    dxdt[v_index] = I_m + I_Na + I_K + I_Leak + I_Ext - I_Syn;
  }
};

} // insilico

#endif
