library ieee;
use ieee.std_logic_1164.all;

entity full_adder is
    port(
        a,b: in std_logic; --digit input
        cin: in std_logic; --input carry
        s: out std_logic; --sum
        cout: out std_logic --output carry
    );
end entity full_adder;

architecture add of full_adder is
    component half_adder
        port(
            a,b: in std_logic;
            s,c: out std_logic
        );
    end component half_adder;
    signal hadder1_s, hadder1_c, hadder2_c: std_logic;
begin
    half_adder_1: half_adder port map 
     (a, b, hadder1_s, hadder1_c);
    half_adder_2: half_adder port map
     (hadder1_s, cin, s, hadder2_c);
    process(hadder1_c, hadder2_c)
    begin
        cout <= hadder1_c or hadder2_c;
    end process;
end architecture add;