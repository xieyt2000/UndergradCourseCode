library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity nixieTube_tb is
end;

architecture bench of nixieTube_tb is

  component nixieTube
      port(
          clk: in std_logic;
          rst: in std_logic;
          displayN: out std_logic_vector(6 downto 0);
          display4O: out std_logic_vector(3 downto 0);
          display4E: out std_logic_vector(3 downto 0)
      );
  end component;

  signal clk: std_logic;
  signal rst: std_logic;
  signal displayN: std_logic_vector(6 downto 0);
  signal display4O: std_logic_vector(3 downto 0);
  signal display4E: std_logic_vector(3 downto 0) ;

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  uut: nixieTube port map ( clk       => clk,
                            rst       => rst,
                            displayN  => displayN,
                            display4O => display4O,
                            display4E => display4E );

  stimulus: process
  begin
    stop_the_clock <= false;
	 rst <= '0';
	 wait for 100ns;
		rst <= '1';
    wait;
  end process;

  clocking: process
  begin
    while not stop_the_clock loop
      clk <= '0', '1' after clock_period / 2;
      wait for clock_period;
    end loop;
    wait;
  end process;

end;
  