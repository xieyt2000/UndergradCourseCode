library ieee;
use ieee.std_logic_1164.all;

architecture lookahead_adder of adder is
    component half_adder --calculate p and g
        port(
            a,b: in std_logic;
            s,c: out std_logic
        );
    end component half_adder;
    component full_adder
        port(
            a,b: in std_logic;
            cin: in std_logic;
            s: out std_logic;
            cout: out std_logic
        );
    end component full_adder;
    signal p, g: std_logic_vector(3 downto 0); -- see textbook. p = a xor b  g = a and b
    signal c: std_logic_vector(3 downto 1); --carry

begin
    -- get p and g
    half_adder_0: half_adder port map(a(0), b(0), p(0), g(0));
    half_adder_1: half_adder port map(a(1), b(1), p(1), g(1));
    half_adder_2: half_adder port map(a(2), b(2), p(2), g(2));
    half_adder_3: half_adder port map(a(3), b(3), p(3), g(3));
    -- full adder for each digit. ignore the output carry
    full_adder_0: full_adder port map(a(0), b(0), cin, s(0), cout => open);
    full_adder_1: full_adder port map(a(1), b(1), c(1), s(1), cout => open);
    full_adder_2: full_adder port map(a(2), b(2), c(2), s(2), cout => open);
    full_adder_3: full_adder port map(a(3), b(3), c(3), s(3), cout => open);

    --calculate c. method from textbook.
    process(cin, p, g)
    begin
        c(1) <= g(0) or (p(0) and cin);
        c(2) <= g(1) or (p(1) and g(0)) or (p(1) and p(0) and cin);
        c(3) <= g(2) or (p(2) and (g(1))) or (p(2) and p(1) and g(0)) or 
		  (p(2) and p(1) and p(0) and cin);
        cout <= g(3) or (p(3) and g(2)) or (p(3) and p(2) and g(1)) or 
		  (p(3) and p(2) and p(1) and g(0)) or (p(3) and p(2) and p(1) and p(0) and cin);
    end process;
end architecture lookahead_adder;