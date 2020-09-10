library verilog;
use verilog.vl_types.all;
entity Lab3_vlg_sample_tst is
    port(
        Clock           : in     vl_logic;
        ResetLow        : in     vl_logic;
        sampler_tx      : out    vl_logic
    );
end Lab3_vlg_sample_tst;
