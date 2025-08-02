library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity cordic_angle_rom_tb is
end cordic_angle_rom_tb;

architecture sim of cordic_angle_rom_tb is

    -- Testbench signals
    signal addr_tb : std_logic_vector(3 downto 0) := (others => '0');
    signal angle_out_tb : std_logic_vector(15 downto 0);
    

    -- Component declaration
    component cordic_angle_rom
        Port (
            addr : in  std_logic_vector(3 downto 0);
            angle_out : out std_logic_vector(15 downto 0)
        );
    end component;

begin

    -- Instantiate the Unit Under Test (UUT)
    uut: cordic_angle_rom
        port map (
            addr => addr_tb,
            angle_out => angle_out_tb
        );

    -- Stimulus process
    stimulus: process
    begin
        for i in 0 to 14 loop  -- Test 0 through 14, 15 is out-of-bounds
            addr_tb <= std_logic_vector(to_unsigned(i, 4));
            wait for 10 ns;
        end loop;

        wait;  -- Wait forever after finishing simulation
    end process;

end sim;
