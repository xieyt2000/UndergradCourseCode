library ieee;
use ieee.std_logic_1164.all;

entity half_adder is
    port (
        a, b: in std_logic; --input
        s: out std_logic;   --sum
        c: out std_logic    --carry
    );
end entity half_adder;

architecture add of half_adder is
begin
    process(a, b)
    begin
        s <= a xor b;
        c <= a and b;
    end process;
end architecture add;