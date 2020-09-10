onerror {quit -f}
vlib work
vlog -work work Lab4BABY.vo
vlog -work work Lab4BABY.vt
vsim -novopt -c -t 1ps -L max7000s_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate work.Lab4BABY_vlg_vec_tst
vcd file -direction Lab4BABY.msim.vcd
vcd add -internal Lab4BABY_vlg_vec_tst/*
vcd add -internal Lab4BABY_vlg_vec_tst/i1/*
add wave /*
run -all
