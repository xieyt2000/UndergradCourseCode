library ieee;
use ieee.std_logic_1164.all;

entity adder is
    port(
        a, b: in std_logic_vector(3 downto 0); --input number
        cin: in std_logic; --input carry
        s: out std_logic_vector(3 downto 0); --output sum
        cout: out std_logic --output carry
    );
end entity adder;

configuration add of adder is
    for lookahead_adder
    end for;
end configuration add;
