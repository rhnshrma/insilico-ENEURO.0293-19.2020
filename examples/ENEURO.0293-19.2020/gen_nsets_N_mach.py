

gkleak_array1=[]
gkleak_array2=[]
rleak1 = []
rleak2 = []


gh_array1=[]
gh_array2=[]

for g in xrange(30,150,2):
	gkleak_array1.append(format(g/10000.000000000,'.6f'))
	gkleak_array2.append(str(g))

	# k_RE = 800*(1 - (g - 100)/g)

	# rleak1.append(format(k_RE/10000.000000000,'.6f'))
	# rleak2.append(str(g))
rleak1 = ['0.08']
for g in xrange(4,50,4):
	gh_array1.append(format(g/100.000000000,'.6f'))
	gh_array2.append(str(g))

Ca = ['0.00024']

calciumshift = ['1.00']

for c in calciumshift:
	for rl in xrange(0,len(rleak1)):

		for t in xrange(0,len(t_array1)):

			for k in xrange(0,len(gh_array1)):

				for j in xrange(0,len(gkleak_array1)):

					NSETS_CONF="./nsets_network_mAch_Ca0.00024_gh"+gh_array2[k]+"_leak"+gkleak_array2[j]+"_cashift"+c+".isf"
					strtofile = ""


					for i in range(0,2):

						NEURON="\" HTC_cell_"+str(i)+" \" \n dxdt:9 ,"
						NEURON+="m_Na_TC:0.2,"
						NEURON+="h_Na_TC:0.6,"
						NEURON+="n_K_TC:0.4,"
						NEURON+="h_t_TC:0.024,"
						NEURON+="m_ahp_HTC:0.05,"
						NEURON+="r_H_HTC:0.5,"
						NEURON+="h_tht_HTC:0.40,"
						NEURON+="v:-60.0,"
						NEURON+="Ca_conc:0.00024,"
						NEURON+="m_Na_TC_stoch:-1,"
						NEURON+="I_Na_RE:0,"
						NEURON+="I_K_RE:0,"
						NEURON+="Ca_slow_switch:0,"
						NEURON+="I_T_RE:0,"
						NEURON+="v_mag:0.01,"
						NEURON+="I_AHP_HTC:0,"
						NEURON+="m_Na_RE:0.0,"
						NEURON+="n_K_RE:0.0,"
						NEURON+="h_Na_RE:0.0,"
						NEURON+="m_t_RE:0.0,"
						NEURON+="h_t_RE:0.0,"
						NEURON+="I_T_TC:0,"
						NEURON+="eq_Ca_fast:0.00024,"
						NEURON+="eq_Ca_slow:0.00024,"
						NEURON+="tau_fast:3,"
						NEURON+="tau_slow:9999999999999999999999,"
						NEURON+="gkleak:"+gkleak_array1[j]+","
						NEURON+="h_Na_TC_stoch:-1,"
						NEURON+="n_K_TC_stoch:-1,"
						NEURON+="eq_Ca:0.00024,"
						NEURON+="tau_Ca:99999999,"
						NEURON+="h_t_TC_stoch:-1,"
						NEURON+="I_THT_HTC:0,"
						NEURON+="Ca_conc_stoch:-1,"
						NEURON+="calcium_shift:"+c+","
						NEURON+="m_ahp_HTC_stoch:-1,"
						NEURON+="r_H_HTC_stoch:-1,"
						NEURON+="h_tht_HTC_stoch:-1,"
						NEURON+="v_stoch:1,"
						NEURON+="I_Syn:0,"
						NEURON+="I_Syn_I:0,"
						NEURON+="I_Syn_E:0,"
						NEURON+="T:0,"
						NEURON+="last_spike:-999999999,"
						NEURON+="g_THT:12,"
						NEURON+="I_Syn_GJ:0,"
						NEURON+="gh:"+gh_array1[k]+","
						NEURON+="g_gj:0.005,"
						NEURON+="iext:0; \n"
						strtofile+=NEURON



					for i in range(2,10):
						NEURON="\" TC_cell_"+str(i)+" \" \n	dxdt:9,"
						NEURON+="m_Na_TC:0.1,"
						NEURON+="n_K_TC:0.4,"
						NEURON+="h_Na_TC:0.6,"
						NEURON+="h_t_TC:0.2,"
						NEURON+="o_h_TC:0.2,"
						NEURON+="c_h_TC:0.8,"
						NEURON+="Ca_conc:0.00024,"
						NEURON+="p_h_TC:0.5,"
						NEURON+="v:-56,"
						NEURON+="I_T_TC:0,"
						NEURON+="I_Syn:0,"
						NEURON+="I_Syn_I:0,"
						NEURON+="I_Syn_E:0,"
						NEURON+="I_Na_RE:0,"
						NEURON+="I_K_RE:0,"
						NEURON+="I_T_RE:0,"
						NEURON+="T_next_epsp:4,"
						NEURON+="m_Na_RE:0.0,"
						NEURON+="n_K_RE:0.0,"
						NEURON+="h_Na_RE:0.0,"
						NEURON+="m_t_RE:0.0,"
						NEURON+="h_t_RE:0.0,"
						NEURON+="v_mag:0.01,"
						NEURON+="T_last_epsp:-999999999.0,"
						NEURON+="T_last_ipsp:-999999999.0,"
						NEURON+="T_next_ipsp:99999999.0,"
						NEURON+="T_next_epsp:100,"
						NEURON+="Ca_slow_switch:0,"
						NEURON+="eq_Ca_fast:0.00024,"
						NEURON+="t_ipsp:9999999,"
						NEURON+="t_epsp:"+t_array1[t]+","
						NEURON+="eq_Ca_slow:0.00024,"
						NEURON+="tau_fast:3,"
						NEURON+="tau_slow:9999999999,"
						NEURON+="m_Na_TC_stoch:-1,"
						NEURON+="n_K_TC_stoch:-1,"
						NEURON+="h_Na_TC_stoch:-1,"
						NEURON+="h_t_TC_stoch:-1,"
						NEURON+="eq_Ca:0.00024,"
						NEURON+="tau_Ca:5,"
						NEURON+="r_H_HTC:0.7777777,"
						NEURON+="o_h_TC_stoch:-1,"
						NEURON+="c_h_TC_stoch:-1,"
						NEURON+="I_THT_HTC:0,"
						NEURON+="Ca_conc_stoch:-1,"
						NEURON+="p_h_TC_stoch:-1,"
						NEURON+="calcium_shift:"+c+","
						NEURON+="calcium_shift:1,"
						NEURON+="last_spike:-999999999,"
						NEURON+="v_stoch:1,"
						NEURON+="T:0,"
						NEURON+="gs:1.0,"
						NEURON+="iext:0.0; \n"
						strtofile+=NEURON





					for i in range(10,20):
						NEURON="\" RE_cell_"+str(i)+" \" \n dxdt:7,"
						NEURON+="m_Na_RE:0.1,"
						NEURON+="n_K_RE:0.4,"
						NEURON+="h_Na_RE:0.6,"
						NEURON+="Ca_conc:0.00024,"
						NEURON+="m_t_RE:0.5,"
						NEURON+="h_t_RE:0.5,"
						NEURON+="v:-60.0,"
						NEURON+="I_T_TC:0,"
						NEURON+="I_Na_RE:0,"
						NEURON+="I_K_RE:0,"
						NEURON+="I_Syn:0,"
						NEURON+="I_Syn_I:0,"
						NEURON+="I_Syn_E:0,"
						NEURON+="gs:1.0,"
						NEURON+="I_T_RE:0,"
						NEURON+="v_mag:0.01,"
						NEURON+="T_last_epsp:-999999999.0,"
						NEURON+="T_next_epsp:1.0,"
						NEURON+="T_last_ipsp:-999999999.0,"
						NEURON+="T_next_ipsp:3.0,"
						NEURON+="I_AHP_HTC:0,"
						NEURON+="m_Na_RE_stoch:-1,"
						NEURON+="t_ipsp:10,"
						NEURON+="t_epsp:10,"
						NEURON+="eq_Ca_fast:0.00024,"
						NEURON+="eq_Ca_slow:0.00024,"
						NEURON+="r_H_HTC:0.7777777,"
						NEURON+="tau_fast:3,"
						NEURON+="tau_slow:9999999999999,"
						NEURON+="n_K_RE_stoch:-1,"
						NEURON+="Ca_conc_stoch:-1,"
						NEURON+="h_Na_RE_stoch:-1,"
						NEURON+="m_t_RE_stoch:-1,"
						NEURON+="h_t_RE_stoch:-1,"
						NEURON+="calcium_shift:"+c+","
						NEURON+="calcium_shift:1,"
						NEURON+="T:0,"
						NEURON+="last_spike:-999999999,"
						NEURON+="v_stoch:1,"
						NEURON+="gkleak:"+rleak2[j] +","
						NEURON+="iext:0.0; \n"
						strtofile+=NEURON


					outfile = open(NSETS_CONF,"w")

					outfile.write(strtofile)
					outfile.close()









