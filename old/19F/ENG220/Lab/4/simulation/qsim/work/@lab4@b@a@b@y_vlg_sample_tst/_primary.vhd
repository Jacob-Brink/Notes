library verilog;
use verilog.vl_types.all;
entity Lab4BABY_vlg_sample_tst is
    port(
        CLEAR           : in     vl_logic;
        In0             : in     vl_logic;
        In1             : in     vl_logic;
        TICKTOCGOETHCLOCk: in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end Lab4BABY_vlg_sample_tst;
