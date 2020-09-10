library verilog;
use verilog.vl_types.all;
entity Lab4BABY is
    port(
        Unit1LED        : out    vl_logic;
        CLEAR           : in     vl_logic;
        TICKTOCGOETHCLOCk: in     vl_logic;
        In1             : in     vl_logic;
        In0             : in     vl_logic;
        Unit0LED        : out    vl_logic
    );
end Lab4BABY;
