library ieee;
use ieee.std_logic_1164;

architecture ripple_adder of adder is
    component full_adder
        port(
            a,b: in std_logic;
            cin: in std_logic;
            s: out std_logic;
            cout: out std_logic
        );
    end component full_adder;
    signal c: std_logic_vector(3 downto 1); --carry in the process
begin
    full_adder_0: full_adder port map(a(0), b(0), cin, s(0), c(1));
    full_adder_1: full_adder port map(a(1), b(1), c(1), s(1), c(2));
    full_adder_2: full_adder port map(a(2), b(2), c(2), s(2), c(3));
    full_adder_3: full_adder port map(a(3), b(3), c(3), s(3), cout);
end architecture ripple_adder;
    