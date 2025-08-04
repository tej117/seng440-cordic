library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity cordic_controller is
    Port (
        clk        : in  std_logic; -- Clock signal
        rst        : in  std_logic; -- Reset to initialize the FSM
        start_flag : in  std_logic; -- Start Signal that triggers CORDIC process
        done_flag  : out std_logic; -- Done Signal that goes high when CORDIC finishes
        i_en       : out std_logic; -- Index enable that allows for updating iteration counter
        load_en    : out std_logic; -- Load enable which is high during the cycle where inital values are loaded
        iter_en    : out std_logic; -- Iteratate enable that allows for computation step 
        i_val      : out integer range 0 to 14 -- Iteration index that tracks CORDIC iteration
    );
end cordic_controller;

-- Defines a control FSM (Finite State Machine) for the CORDIC cordic_datapath
-- Does loading, iterating, and finishing by setting the control signals.

architecture Behavioral of cordic_controller is

    type state_type is (IDLE, LOAD, ITERATE, DONE);
    signal state : state_type := IDLE;
    signal i     : integer range 0 to 14 := 0;

begin

    process(clk)
    begin
        if rising_edge(clk) then
            if rst = '1' then
                state <= IDLE;
                i <= 0;
            else
                case state is
                    when IDLE =>
                        if start_flag = '1' then
                            state <= LOAD;
                        end if;

                    when LOAD =>
                        state <= ITERATE;
                        i <= 0;

                    when ITERATE =>
                        if i = 14 then
                            state <= DONE;
                        else
                            i <= i + 1;
                        end if;

                    when DONE =>
                        if start_flag = '0' then
                            state <= IDLE;
                        end if;
                end case;
            end if;
        end if;
    end process;

    -- Control signals
    load_en <= '1' when state = LOAD else '0';
    iter_en <= '1' when state = ITERATE else '0';
    i_en    <= '1' when state = ITERATE else '0';
    done_flag    <= '1' when state = DONE else '0';
    i_val   <= i;

end Behavioral;
