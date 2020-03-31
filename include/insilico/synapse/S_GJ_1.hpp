/*
 synapse/S_DefaultSynapse.hpp - Default non-specialized synapse with last spike logic

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

#ifndef INCLUDED_S_GJ_1_HPP
#define INCLUDED_S_GJ_1_HPP

#include "insilico/core/engine.hpp"
#include "vtrap.cpp"
#include <random>


namespace insilico {




class S_GJ_1: public Synapse {
 public:
  void ode_set(state_type& variables, state_type& dxdt, const double t, unsigned index) {
    
    unsigned g1_index = engine::synapse_index(index, "g1");
    unsigned pre_neuron_index = engine::synapse_value(index, "pre");





    double g1             =    variables[g1_index];
    unsigned neuron_index = engine::synapse_value(index, "pre");
    double v_pre = variables[engine::neuron_index(neuron_index,"v")];
    unsigned v_index = engine::neuron_index(neuron_index, "v");
    unsigned v_pre_index = engine::synapse_index(index,"v_pre");
    //engine::synapse_value(index, "v_pre",variables[v_index]);
    variables[v_pre_index] = v_pre;

 
 
    // constants from file


    // ODE set
    dxdt[g1_index] = 0.0;


  } // function ode_set
}; // class S_GJ_1

} // insilico

#endif


