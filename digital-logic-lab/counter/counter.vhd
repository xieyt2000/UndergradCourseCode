library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity counter is
	port(
		clk, rst: in std_logic;
		mode: in std_logic; --1 is clock and 0 is counter
		tens_display, ones_display: out std_logic_vector(6 downto 0) 
	);
end entity counter;

architecture bhv of counter is
	signal tens, ones: std_logic_vector(3 downto 0);
	signal cnt: integer := 0;
	component nixie_tube
		port(
        	number: in std_logic_vector(3 downto 0);
        	display: out std_logic_vector(6 downto 0)
		);
	end component nixie_tube;

begin
	tens_tube: nixie_tube port map(tens, tens_display);
	ones_tube: nixie_tube port map(ones, ones_display);

	process(clk, rst)
	begin
		if rst = '1' then
			tens <= "0000";
			ones <= "0000";
			cnt <= 0;
		elsif(clk' event and clk = '1') then
			if (mode = '1') then
				if (cnt = 1000000) then
					cnt <= 0;
				else cnt <= cnt + 1;
				end if ;
			end if;
			if(mode = '0' or cnt = 1000000) then
				if(ones = "1001") then
					ones <= "0000";
					tens <= tens + 1;
					if(tens = "0101") then
						tens <= "0000";
					end if;
				else
					ones <= ones + 1;
				end if;
			end if;
		end if;
	end process;
end architecture bhv;