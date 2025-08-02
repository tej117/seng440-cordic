library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity cordic_top is
    Port (
        clk     : in  std_logic;
        rst     : in  std_logic;
        start   : in  std_logic;

        -- Inputs for initial vector
        x_in    : in  signed(31 downto 0);
        y_in    : in  signed(31 downto 0);

        -- Outputs after rotation
        x_out   : out signed(31 downto 0);
        y_out   : out signed(31 downto 0);
        z_out   : out signed(31 downto 0);

        -- Done signal to indicate completion
        done    : out std_logic
    );
end cordic_top;

architecture Structural of cordic_top is

    -- Signals to connect controller and datapath
    signal load_en_sig : std_logic;
    signal iter_en_sig : std_logic;
    signal i_en_sig    : std_logic; 
    signal i_val_sig   : integer range 0 to 14;

begin

    -- Instantiate controller
    controller_inst : entity work.cordic_controller
        port map (
            clk          => clk,
            rst          => rst,
            start_flag   => start,
            done_flag    => done,
            i_en         => i_en_sig,  
            load_en      => load_en_sig,
            iter_en      => iter_en_sig,
            i_val        => i_val_sig
        );

    -- Instantiate datapath
    datapath_inst : entity work.cordic_datapath
        port map (
            clk     => clk,
            rst     => rst,
            load_en => load_en_sig,
            iter_en => iter_en_sig,
            i_val   => i_val_sig,
            x_in    => x_in,
            y_in    => y_in,
            x_out   => x_out,
            y_out   => y_out,
            z_out   => z_out
        );

end Structural;
