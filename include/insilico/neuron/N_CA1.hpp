/*
 neuron/N_rohan.hpp - Hodgkin-Huxley Squid Axon experiment (Hodgkin-Huxley, 1952)

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

#ifndef INCLUDED_N_CA1_HPP
#define INCLUDED_N_CA1_HPP

#include "insilico/core/engine.hpp"

#include "../current/I_NaS_CA1.hpp"
#include "../current/I_KdS_CA1.hpp"
#include "../current/I_KcS_CA1.hpp"
#include "../current/I_KahpS_CA1.hpp"
#include "../current/I_CaS_CA1.hpp"
#include "../current/I_Leak_S.hpp"

#include "../current/I_KcD_CA1.hpp"
#include "../current/I_KahpD_CA1.hpp"
#include "../current/I_CaD_CA1.hpp"
#include "../current/I_Leak_D.hpp"

namespace insilico {

class N_CA1: public Neuron{
 public:
  void ode_set(state_type &variables, state_type &dxdt, const double t,const unsigned index) {

    //Voltage
    unsigned v_soma_index = engine::neuron_index(index, "v_soma");
    unsigned v_dend_index = engine::neuron_index(index, "v_dend");
    double v_soma = variables[v_soma_index];
    double v_dend = variables[v_dend_index];

    //Other parameters
    double p = engine::neuron_value(index,"percentage_soma");
    double gc = engine::neuron_value(index,"g_coupling");
    double Cm = engine::neuron_value(index,"Cm");

    double I_Syn = 0;
    // note the spike
/*    double thresh = 0, dead_time=1;
    double last_spike = engine::neuron_value(index,"last_spike");*/

    // associated delay for next spikes
/*    if((v > thresh) && (t - last_spike) > dead_time){
      engine::neuron_value(index, "last_spike", t);
    }


    // incoming synaptic currents
    std::vector<unsigned> g1_indices = engine::get_pre_neuron_indices(index, "g1");
    std::vector<double> gsyn = engine::get_pre_neuron_values(index, "gsyn");
    std::vector<double> esyn = engine::get_pre_neuron_values(index, "esyn");
    double I_Syn = 0;
    for(unsigned iterator = 0; iterator < g1_indices.size(); ++iterator) {
      I_Syn = I_Syn + variables[g1_indices.at(iterator)]*gsyn.at(iterator)*(v - esyn.at(iterator));
    }*/


    I_NaS_CA1::current(variables, dxdt, t, index);
    I_KdS_CA1::current(variables, dxdt, t, index);
    I_KcS_CA1::current(variables, dxdt, t, index);
    I_KahpS_CA1::current(variables, dxdt, t, index);
    I_CaS_CA1::current(variables, dxdt, t, index);
    I_Leak_S::current(variables, dxdt, t, index);


    I_KcD_CA1::current(variables, dxdt, t, index);
    I_KahpD_CA1::current(variables, dxdt, t, index);
    I_CaD_CA1::current(variables, dxdt, t, index);
    I_Leak_D::current(variables, dxdt, t, index);

    //Soma Currents
    double I_NaS = 0;
    double I_KdS = 0;
    double I_KcS = 0;
    double I_KahpS = 0;
    double I_CaS = 0;
    double I_Ext_S = 0;
    double I_coupling_S = 0;
    double I_Leak_S = 0;

    I_NaS = engine::neuron_value(index, "I_NaS");
    I_KdS = engine::neuron_value(index, "I_KdS");
    I_KcS = engine::neuron_value(index, "I_KcS");
    I_KahpS = engine::neuron_value(index, "I_KahpS");
    I_CaS = engine::neuron_value(index, "I_CaS");
    I_Ext_S = engine::neuron_value(index, "I_Ext_S")/p;
    I_coupling_S = -1*gc*(v_soma - v_dend)/p;
    I_Leak_S = engine::neuron_value(index, "I_Leak_S");

    engine::neuron_value(index, "I_coupling_S",I_coupling_S);

    //Dendrite Currents
    double I_KcD = 0;
    double I_KahpD = 0;
    double I_CaD = 0;
    double I_Ext_D = 0;
    double I_coupling_D = 0;
    double I_Leak_D = 0;

 
    I_KcD = engine::neuron_value(index, "I_KcD");
    I_KahpD = engine::neuron_value(index, "I_KahpD");
    I_CaD = engine::neuron_value(index, "I_CaD");
    I_Ext_D = engine::neuron_value(index, "I_Ext_D")/(1-p);
    I_coupling_D = -1*gc*(v_dend - v_soma)/(1-p);
    I_Leak_D = engine::neuron_value(index, "I_Leak_D");


    // ODE
    dxdt[v_soma_index] = (I_NaS + I_KdS + I_KcS + I_KahpS + I_CaS + I_Ext_S + I_Leak_S + I_coupling_S)/Cm;
    dxdt[v_dend_index] = (I_KcD + I_KahpD + I_CaD + I_Ext_D + I_Leak_D + I_coupling_D - I_Syn)/Cm;

  }
};

} // insilico

#endif
