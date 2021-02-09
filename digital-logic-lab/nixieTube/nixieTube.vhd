LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity nixieTube is
    port(
        clk: in std_logic;                               --输入时钟
        rst: in std_logic;                               --复位按钮
        displayN: out std_logic_vector(6 downto 0);     --带译码器自然数列
        display4O: out std_logic_vector(3 downto 0);    --不带译码器奇数列
        display4E: out std_logic_vector(3 downto 0)            --带译码器偶数列
    );
end nixieTube;


architecture bhv of nixieTube is
	signal displayNNum: std_logic_vector(3 downto 0) := "0000";     --自然数列
    signal display4ONum: std_logic_vector(3 downto 0) := "0001";    --偶数列
    signal display4ENum: std_logic_vector(3 downto 0) := "0000";    --奇数列
    signal clkCnt: integer := 0;    --时钟分频计数器
	 
begin  
    process(clk, rst)	--时钟信号（分频） 复位信号 rst为1时进行复位
    begin
        if(clk'event and clk = '1') then
				--if(clkCnt < 1000000) then	--分频时钟，实验平台上便于观察
				if(clkCnt < 0) then		--普通时钟，不分频，testbench便于观察
                --clkCnt <= clkCnt + 1;
            else
                clkCnt <= 0;
                if(displayNNum = "1001") then
                    displayNNum <= "0000";
                else
                    displayNNum <= displayNNum + 1;
			    end if;
			    if(display4ONum = "1001") then
                    display4ONum <= "0001";
                else
                    display4ONum <= display4ONum + 2;
                end if;
                if(display4ENum = "1000") then
                    display4ENum <= "0000";
                else
                    display4ENum <= display4ENum + 2;
                end if;
            end if;
        end if;
		if(rst = '1') then
				displayNNum <= "0000";
				display4ENum <= "0000";
				display4ONum <= "0001";
				clkCnt <= 0;
        end if;
    end process;
	 
	process(display4ONum)	--奇数输出
    begin
        display4O <= display4ONum;
    end process;
    
    process(display4ENum)   --偶数输出
    begin
        display4E <= display4ENum;
    end process;
	 
    process(displayNNum)	--自然数输出
    begin
        case displayNNum is --译码规则
            when "0000"=> displayN<="1111110";
            when "0001"=> displayN<="0110000";
            when "0010"=> displayN<="1101101";
            when "0011"=> displayN<="1111001";
            when "0100"=> displayN<="0110011";
            when "0101"=> displayN<="1011011";
            when "0110"=> displayN<="1011111";
            when "0111"=> displayN<="1110000";
            when "1000"=> displayN<="1110011";
            when "1001"=> displayN<="1110011";
            when "1010"=> displayN<="1110111";
            when "1011"=> displayN<="0011110";
            when "1100"=> displayN<="1001110";
            when "1101"=> displayN<="0111100";
            when "1110"=> displayN<="1001111";
            when "1111"=> displayN<="1000111";
            when others=> displayN<="0000000";
        end case;
    end process;
end bhv;