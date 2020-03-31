


#gkleak_array1=['0.0130','0.0131','0.0132','0.0133','0.0134','0.0135','0.0136','0.0137','0.0138','0.0139','0.0140','0.0141','0.0142','0.0143','0.0144','0.0145','0.0146','0.0147','0.0148','0.0149','0.0150','0.0151','0.0152','0.0153','0.0154','0.0155','0.0156','0.0157','0.0158','0.0159','0.0160','0.0161','0.0162','0.0163','0.0164','0.0165','0.0166','0.0167','0.0168','0.0169','0.0170']
#gkleak_array2=['130','131','132','133','134','135','136','137','138','139','140','141','142','143','144','145','146','147','148','149','150','151','152','153','154','155','156','157','158','159','160','161','162','163','164','165','166','167','168','169','170']

gkleak_array1=[]
gkleak_array2=[]
rleak1 = []
rleak2 = []

gs_array1=['1.0']
#gs_array2=['70','80','90','100','110','120','130','140','150','160','170','180','190','200','210','220','230','240','250','260','270','280','290']

t_array1=['5','10']

gh_array1=[]
gh_array2=[]

for g in xrange(30,150,2):
	gkleak_array1.append(format(g/10000.000000000,'.6f'))
	gkleak_array2.append(str(g))

	k_RE = 800*(1 - (g - 100)/g)

	rleak1.append(format(k_RE/10000.000000000,'.6f'))
	rleak2.append(str(g))

for g in xrange(4,50,4):
	gh_array1.append(format(g/100.000000000,'.6f'))
	gh_array2.append(str(g))
tauarray = ['0.625','1.25','2.5','5','10','20','40']
Ca = ['0.00024']
#calciumshift = ['0.50','0.55','0.60','0.65','0.70','0.75','0.80','0.85','0.90','0.95','1.00','1.05','1.10','1.15','1.20','1.25','1.30','1.35','1.40','1.50','1.55','1.60','1.65','1.70','1.75','1.80','1.85','1.90','1.95']

#for c in xrange(50,150,2):
#	calciumshift.append(format(c/100.000000000,'.2f'))
calciumshift = ['1.00']
#for cs in calciumshift:
for c in calciumshift:
	for rl in xrange(0,len(rleak1)):

		for t in xrange(0,len(t_array1)):

			for k in xrange(0,len(gh_array1)):

				for j in xrange(0,len(gkleak_array1)):

					NSETS_CONF="/storage/rohan/ISF_Files/calciumshift/nsets_network_mAch_Ca0.00024_gh"+gh_array2[k]+"_leak"+gkleak_array2[j]+"_cashift"+c+".isf"
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
						#NEURON+="calcium_shift:1,"
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









