library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity mux4_1_tb is
end;

architecture bench of mux4_1_tb is

  component mux4_1
  	port(
  	D0 : in Std_logic_vector(3 downto 0);
  	D1 : in Std_logic_vector(3 downto 0);
  	D2 : in Std_logic_vector(3 downto 0);
  	D3 : in std_logic_vector(3 downto 0);
  	select0 : in bit;
  	select1 : in bit;
  	Y : out Std_logic_vector(3 downto 0)
  	);
  end component;

  signal D0: Std_logic_vector(3 downto 0);
  signal D1: Std_logic_vector(3 downto 0);
  signal D2: Std_logic_vector(3 downto 0);
  signal D3: std_logic_vector(3 downto 0);
  signal select0: bit;
  signal select1: bit;
  signal Y: Std_logic_vector(3 downto 0) ;

begin

  uut: mux4_1 port map ( D0      => D0,
                         D1      => D1,
                         D2      => D2,
                         D3      => D3,
                         select0 => select0,
                         select1 => select1,
                         Y       => Y );

  stimulus: process
  begin
  
    -- Put initialisation code here
	D0<="0001";
	D1<="0010";
	D2<="0011";
	D3<="0100";
	select0<='0';
	select1<='0';
wait for 10ns;
	D0<="0001";
	D1<="0010";
	D2<="0011";
	D3<="0100";
	select0<='1';
	select1<='0';
wait for 10ns;
	D0<="0001";
	D1<="0010";
	D2<="0011";
	D3<="0100";
	select0<='0';
	select1<='1';
wait for 10ns;
	D0<="0001";
	D1<="0010";
	D2<="0011";
	D3<="0100";
	select0<='1';
	select1<='1';
    -- Put test bench stimulus code here

    wait;
  end process;


end;