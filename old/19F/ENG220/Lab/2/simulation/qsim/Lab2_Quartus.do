onerror {quit -f}
vlib work
vlog -work work Lab2_Quartus.vo
vlog -work work Lab2_Quartus.vt
vsim -novopt -c -t 1ps -L max7000s_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.Lab2_Quartus_vlg_vec_tst
vcd file -direction Lab2_Quartus.msim.vcd
vcd add -internal Lab2_Quartus_vlg_vec_tst/*
vcd add -internal Lab2_Quartus_vlg_vec_tst/i1/*
add wave /*
run -all
