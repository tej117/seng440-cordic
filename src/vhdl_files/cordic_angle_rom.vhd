library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity cordic_angle_rom is
    port (
        addr     : in  std_logic_vector(3 downto 0); -- 4-bit address: 0-14
        angle_out: out std_logic_vector(15 downto 0) -- 16-bit input: Q2.13 fixed-point
    );
end entity;

-- Assign constants to each element of the table
-- Note that std_logic_vector casts a logic signal for hardware to use
-- Note that to_signed ensures a 16 bit signed number

architecture Behavioral of cordic_angle_rom is
    type rom_array is array (0 to 14) of std_logic_vector(15 downto 0);
    constant angle_table : rom_array := ( 
        0  => std_logic_vector(to_signed(6433, 16)), 
        1  => std_logic_vector(to_signed(3218, 16)),
        2  => std_logic_vector(to_signed(1634, 16)),
        3  => std_logic_vector(to_signed(820,  16)),
        4  => std_logic_vector(to_signed(410,  16)),
        5  => std_logic_vector(to_signed(205,  16)),
        6  => std_logic_vector(to_signed(102,  16)),
        7  => std_logic_vector(to_signed(51,   16)),
        8  => std_logic_vector(to_signed(26,   16)),
        9  => std_logic_vector(to_signed(13,   16)),
        10 => std_logic_vector(to_signed(6,    16)),
        11 => std_logic_vector(to_signed(3,    16)),
        12 => std_logic_vector(to_signed(1,    16)),
        13 => std_logic_vector(to_signed(1,    16)),
        14 => std_logic_vector(to_signed(0,    16))
    );

-- The process of retrieving and outputed the corresponding table value based on addr
begin
    process(addr)
    begin
        angle_out <= angle_table(to_integer(unsigned(addr)));
    end process;
end architecture;