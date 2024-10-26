

build_src_dbg:
	$(MAKE) -C led_matrix/Debug/ all
	
build_libs:
	$(MAKE) -C led_matrix_bsp/ all

run_on_device:
	xsdk -batch "run_program.tcl"

program_fpga:
	vivado  -mode tcl -nolog -nojournal -source program_fpga.tcl 
run_all: build_src_dbg program_fpga run_on_device
