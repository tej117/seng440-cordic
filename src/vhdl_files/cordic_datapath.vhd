library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity cordic_datapath is
    Port (
        clk         : in  std_logic;
        rst         : in  std_logic;

        -- control signals
        load_en     : in std_logic;                 -- Loads x_in, y_in into internal registers
        iter_en     : in std_logic;                 -- Enables iteration for one CORDIC step
        i_val       : in integer range 0 to 14;     -- Iteration index for shift and angle lookup

        -- inputs
        x_in        : in  signed(31 downto 0);      -- Initial x vector value
        y_in        : in  signed(31 downto 0);      -- Initial y vector value

        -- outputs
        x_out       : out signed(31 downto 0);      -- Final x value after rotation
        y_out       : out signed(31 downto 0);      -- Final y value after rotation
        z_out       : out signed(31 downto 0)       -- Accumulated angle output
    );
end cordic_datapath;

architecture Behavioral of cordic_datapath is

    -- Internal state of the datapath across clock cycles

    signal x, y, z : signed(31 downto 0);   -- register values for CORDIC vector
    signal table_val : signed(15 downto 0); -- Value from ROM table
    signal angle_out_slv : std_logic_vector(15 downto 0); -- Temporary value to read from table_rom
    signal rom_addr : std_logic_vector(3 downto 0); -- cordic_angle_rom expects 4-bit address

    component cordic_angle_rom
        Port (
            addr : in  std_logic_vector(3 downto 0);
            angle_out : out std_logic_vector(15 downto 0)
        );
    end component;
begin

    rom_addr <= std_logic_vector(to_unsigned(i_val, 4)); -- Convert integer to std_logic_vector

    rom_inst : entity work.cordic_angle_rom
        port map (
            addr => rom_addr, -- Note: 4 bit wide address for ROM
            angle_out => angle_out_slv 
        );

    table_val <= signed(angle_out_slv); -- angle_out gets saved in table_val

    process(clk)
        variable x_shift, y_shift : signed(31 downto 0);
    begin
        if rising_edge(clk) then
            if rst = '1' then   -- reset registers
                x <= (others => '0'); 
                y <= (others => '0');
                z <= (others => '0');

            elsif load_en = '1' then
                x <= x_in;
                y <= y_in;
                z <= (others => '0');   -- Reset angle accumulator

            elsif iter_en = '1' then
                x_shift := shift_right(x, i_val);
                y_shift := shift_right(y, i_val);

                -- Perform one CORDIC rotation step
                if y > 0 then
                    x <= x + y_shift;
                    y <= y - x_shift;
                    z <= z + resize(table_val, 16);
                else
                    x <= x - y_shift;
                    y <= y + x_shift;
                    z <= z - resize(table_val, 16);
                end if;

                -- TEMP: Debugging the differences between software
                report "x: " & integer'image(to_integer(x));
                report "y: " & integer'image(to_integer(y));
                report "z: " & integer'image(to_integer(z));
            end if;
        end if;
    end process;

    -- Output the x,y,z values after the clock cycle
    x_out <= x; 
    y_out <= y;
    z_out <= z;
end Behavioral;
