library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;

entity cordic_tb is
end cordic_tb;

architecture sim of cordic_tb is

    -- Component Declaration
    component cordic_top
        port (
            clk     : in  std_logic;
            rst     : in  std_logic;
            start   : in  std_logic;
            done    : out std_logic;
            x_in     : in  signed(31 downto 0);
            y_in     : in  signed(31 downto 0);
            x_out     : out signed(31 downto 0);
            y_out     : out signed(31 downto 0);
            z_out     : out signed(31 downto 0)
        );
    end component;

    -- Signal Declarations
    signal clk     : std_logic := '0';
    signal rst     : std_logic := '1';
    signal start   : std_logic := '0';
    signal done    : std_logic;

    signal x_in     : signed(31 downto 0);
    signal y_in     : signed(31 downto 0);
    signal z_in     : signed(31 downto 0);
    signal x_out     : signed(31 downto 0);
    signal y_out     : signed(31 downto 0);
    signal z_out     : signed(31 downto 0);

    -- Clock period
    constant clk_period : time := 10 ns;

begin

    -- Instantiate the Unit Under Test (UUT)
    uut: cordic_top
        port map (
            clk   => clk,
            rst   => rst,
            start => start,
            done  => done,
            x_in   => x_in,
            y_in   => y_in,
            x_out   => x_out,
            y_out   => y_out,
            z_out   => z_out
        );

    -- Clock generation
    clk_process :process
    begin
        clk <= '0';
        wait for clk_period/2;
        clk <= '1';
        wait for clk_period/2;
    end process;

    -- Stimulus process
    stim_proc: process
        -- Directly assign integer constants representing 0.85*8192 and 0.76*8192
        constant x_i_init_val : integer := 6963;  -- 0.85 * 8192 (Q2.13)
        constant y_i_init_val : integer := 6225;  -- 0.76 * 8192 (Q2.13)

        -- Calculate for Modulus
        variable x_real, y_real : real;
        variable modulus_init, modulus_out : real;
    begin
        -- Hold reset for a few cycles
        wait for 20 ns;
        rst <= '0';

        x_in <= to_signed(x_i_init_val, 32);
        y_in <= to_signed(y_i_init_val, 32);
        z_in <= to_signed(0, 32); -- Vectoring mode => z_i = 0

        -- Start the CORDIC operation
        wait for 20 ns;
        start <= '1';
        wait for clk_period;
        start <= '0';

        -- Wait until done
        wait until done = '1';

        x_real := real(to_integer(x_in)) / 8192.0;  -- 2^13 = 8192
        y_real := real(to_integer(y_in)) / 8192.0;
        modulus_init := sqrt(x_real*x_real + y_real*y_real);

        x_real := real(to_integer(x_out)) / 8192.0;
        y_real := real(to_integer(y_out)) / 8192.0;
        modulus_out := sqrt(x_real*x_real + y_real*y_real);

        -- Print results
        report "CORDIC Vectoring Completed.";
        report "Inputs: ";
        report "x_i_init = " & integer'image(to_integer(x_in));
        report "y_i_init = " & integer'image(to_integer(y_in));
        report "z_i_init = " & integer'image(to_integer(z_in));
        
        report "Outputs:";
        report "x_o = " & integer'image(to_integer(x_out));
        report "y_o = " & integer'image(to_integer(y_out));
        report "z_o = " & integer'image(to_integer(z_out));

        report "Modulus:";
        report "Input vector modulus (float) = " & real'image(modulus_init);
        report "Output vector modulus (float) = " & real'image(modulus_out);

        wait;
    end process;

end sim;
