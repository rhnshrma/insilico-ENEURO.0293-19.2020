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

#ifndef INCLUDED_N_HTC_HPP
#define INCLUDED_N_HTC_HPP

#include "insilico/core/engine.hpp"

#include "insilico/current/I_Na_TC.hpp"
#include "insilico/current/I_K_TC.hpp"
#include "insilico/current/I_Leak_HTC.hpp"
#include "insilico/current/I_T_TC.hpp"
#include "insilico/current/I_THT_HTC.hpp"
#include "insilico/current/I_AHP_HTC.hpp"
#include "insilico/current/I_H_HTC.hpp"

namespace insilico {
    class random2 {
 public:
  template<class T>
  static T rand() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dist(0,1);
    return dist(gen);
  }
};
class N_HTC_mAch: public Neuron{
 public:
  void ode_set(state_type &variables, state_type &dxdt, const double t,const unsigned index) {
	unsigned v_index = engine::neuron_index(index, "v");
		
		double v = variables[v_index];
	std::vector<unsigned> v_pre_indices = engine::get_pre_neuron_indices(index, "v_pre");

	double I_Syn = 0;
	std::vector<unsigned> g1_indices = engine::get_pre_neuron_indices(index, "g1");

	for(std::vector<unsigned>::size_type iterator = 0; iterator < g1_indices.size(); ++iterator) {
	  I_Syn = I_Syn + variables[g1_indices.at(iterator)]*(v -variables[v_pre_indices.at(iterator)]); 
	  engine::neuron_value(index, "I_Syn",I_Syn);
		  // constants from file
	}


	//if (t>10){ engine::neuron_value(index,"iext",0);}

	 I_Na_TC::current(variables, dxdt, t, index);
	 I_K_TC::current(variables, dxdt, t, index);
	 I_THT_HTC::current(variables, dxdt, t, index);
	 I_AHP_HTC::current(variables, dxdt, t, index);
	 I_H_HTC::current(variables, dxdt, t, index);
	 I_T_TC::current(variables, dxdt, t, index);
	 I_Leak_HTC::current(variables, dxdt, t, index);

	 double thresh = 0, dead_time=1;
	 double last_spike = engine::neuron_value(index,"last_spike");
	 
	// associated delay for next spikes
	if((v > thresh) && (t - last_spike) > dead_time){
	  engine::neuron_value(index, "last_spike", t);
	}



	double I_Na = engine::neuron_value(index,"I_Na_TC");
	double I_K = engine::neuron_value(index,"I_K_TC");
	double I_HTC_Leak = engine::neuron_value(index,"I_Leak_HTC");
	double I_TLT = engine::neuron_value(index,"I_T_TC");
	double I_H = engine::neuron_value(index,"I_H_HTC"); 
	double I_THT =  engine::neuron_value(index,"I_THT_HTC");
	double I_AHP = engine::neuron_value(index,"I_AHP_HTC");
	double I_Ext = 0.0;
 	if(t > 7000.0)
 	{
	I_Ext = engine::neuron_value(index, "iext");
	}


	double T_last_epsp_index = engine::neuron_index(index,"T_last_epsp");
	double T_next_epsp_index = engine::neuron_index(index,"T_next_epsp");
	double T_next_epsp = variables[T_next_epsp_index];
	double T_last_epsp = variables[T_last_epsp_index];
	double gs = engine::neuron_value(index,"gs");
	double fq = engine::neuron_value(index,"fq");
    double next_T_epsp = 0.0;
    if((t-T_next_epsp) > 0.0)
    {
        double z = random2::rand<double>();
        double next_T_epsp = -1*(log(1-z)/fq);
	 //       engine::neuron_value(index,"T_last_epsp",T_next_epsp);
	//        engine::neuron_value(index,"T_next_epsp",(T_next_epsp+next_T_epsp));
	    variables[T_last_epsp_index] = T_next_epsp;
	    variables[T_next_epsp_index] = T_next_epsp+next_T_epsp;
        //cout<<next_T_epsp<<endl;
     }
	std::vector<double> I_pulse = injector::external_current(index,t);
    double pulse = 0;

    if (!I_pulse.empty()){
      pulse = I_pulse[0];
    }
    double I_epsp = 0.0;


	// ODE
	dxdt[v_index] = I_TLT + pulse + I_HTC_Leak + I_H + I_THT +I_Na+I_K  +  I_AHP  +I_Ext - I_Syn - I_epsp; // 
  }
};

} // insilico

#endif
