library verilog;
use verilog.vl_types.all;
entity Lab3 is
    port(
        L4              : out    vl_logic;
        ResetLow        : in     vl_logic;
        Clock           : in     vl_logic;
        L3              : out    vl_logic;
        L2              : out    vl_logic;
        L1              : out    vl_logic;
        M4              : out    vl_logic;
        M3              : out    vl_logic;
        M2              : out    vl_logic;
        M1              : out    vl_logic
    );
end Lab3;