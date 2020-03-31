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

#ifndef INCLUDED_N_RE_HPP
#define INCLUDED_N_RE_HPP

#include "insilico/core/engine.hpp"



namespace insilico {

        class random9 { //Uniform-Random generator for EPSPs and IPSPs (uniform is converted to Poisson)
 public:
  template<class T>
  static T rand() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dist(0,1);
    return dist(gen);
  }
};


class N_RE_mAch: public Neuron{
 public:
  void ode_set(state_type &variables, state_type &dxdt, const double t,const unsigned index) {
    std::vector<unsigned> g1_indices = engine::get_pre_neuron_indices(index, "g1");
    std::vector<double> gsyn = engine::get_pre_neuron_values(index, "gsyn");
    std::vector<double> T = engine::get_pre_neuron_values(index, "T");
    double I_Syn = 0;
    double I_Syn_I = 0;
    double I_Syn_E = 0;
    std::vector<double> esyn = engine::get_pre_neuron_values(index, "esyn");

    unsigned v_index = engine::neuron_index(index, "v");
    double v = variables[v_index];

    // note the spike
    double thresh = 0, dead_time=1;
    double last_spike = engine::neuron_value(index,"last_spike");

    // associated delay for next spikes
    if((v > thresh) && (t - last_spike) > dead_time){
      engine::neuron_value(index, "last_spike", t);
    }


    double T_sum = 0;
    for(std::vector<unsigned>::size_type iterator = 0; iterator < T.size(); ++iterator) {
       T_sum = T_sum + T[iterator];
     }
    double T_avg = T_sum/T.size();
    engine::neuron_value(index,"T",T_avg);


    // incoming synaptic currents



    for(unsigned iterator = 0; iterator < g1_indices.size(); ++iterator) {
      double I = variables[g1_indices.at(iterator)]*gsyn.at(iterator)*(v - esyn.at(iterator));
      I_Syn = I_Syn + I;
      if (I>0){I_Syn_I = I_Syn_I + I; }
      else {I_Syn_E = I_Syn_E + I; }  
    }

     I_Na_RE::current(variables, dxdt, t, index);
     I_K_RE::current(variables, dxdt, t, index);
     I_T_RE::current(variables, dxdt, t, index);
     I_Leak_RE_mAch::current(variables, dxdt, t, index);


    double I_Na = engine::neuron_value(index, "I_Na_RE");
    double I_K = engine::neuron_value(index, "I_K_RE");
    double I_RE_T = engine::neuron_value(index, "I_T_RE");
    double I_RE_Leak = engine::neuron_value(index, "I_Leak_RE");
    double I_Ext = engine::neuron_value(index, "iext");




    double T_last_epsp = engine::neuron_value(index,"T_last_epsp");
    double T_next_epsp = engine::neuron_value(index,"T_next_epsp");
    double T_last_ipsp = engine::neuron_value(index,"T_last_ipsp");
    double T_next_ipsp = engine::neuron_value(index,"T_next_ipsp");
    double gs = engine::neuron_value(index,"gs");

    if((t-T_next_epsp) > 0)
    {
        double z = random9::rand<double>();
        double next_T_epsp = -1*(log(1-z)*engine::neuron_value(index,"t_epsp")); //Converting Uniform Ditribution to Poisson(http://stackoverflow.com/questions/2106503/pseudorandom-number-generator-exponential-distribution)
        engine::neuron_value(index,"T_last_epsp",T_next_epsp);
        engine::neuron_value(index,"T_next_epsp",(T_next_epsp+next_T_epsp));

     }

    double I_epsp = ((t < (T_last_epsp + 5)) ? (0.02*gs*exp(T_last_epsp - t)*v):0 );

        if((t-T_next_ipsp) > 0)
    {
        double z = random9::rand<double>();
        double next_T_ipsp = -1*(log(1-z)*engine::neuron_value(index,"t_ipsp"));//Converting Uniform Ditribution to Poisson(http://stackoverflow.com/questions/2106503/pseudorandom-number-generator-exponential-distribution)
        engine::neuron_value(index,"T_last_ipsp",T_next_ipsp);
        engine::neuron_value(index,"T_next_ipsp",(T_next_ipsp+next_T_ipsp));

     }
    double I_ipsp = ((t < (T_last_ipsp + 5)) ? (1.5*0.01*gs*exp(T_last_ipsp - t)*(v+85)):0);
    

    engine::neuron_value(index,"I_Syn_I",I_Syn_I);
    engine::neuron_value(index,"I_Syn_E",I_Syn_E);

    // ODE
    dxdt[v_index] = I_Na + I_K + I_RE_Leak + I_RE_T + I_Ext - I_Syn - I_epsp - I_ipsp;
  }
};

} // insilico

#endif
