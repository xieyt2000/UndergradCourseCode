library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_std.all;
entity mux4_1 is
	port(
	D0 : in Std_logic_vector(3 downto 0);
	D1 : in Std_logic_vector(3 downto 0);
	D2 : in Std_logic_vector(3 downto 0);
	D3 : in std_logic_vector(3 downto 0);
	select0 : in bit;
	select1 : in bit;
	Y : out Std_logic_vector(3 downto 0)
	);
end mux4_1;
architecture mux4_1 of mux4_1 is
	begin
		Y<=D0 when select0='0' and select1='0'
		else D1 when select0='1' and select1='0'
		else D2 when select0='0' and select1='1'
		else D3 when select0='1' and select1='1';
end mux4_1;