library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity num_lock is
    port (
        clk, rst: in std_logic;
        code: in std_logic_vector (3 downto 0); --输入密码
        mode: in std_logic_vector (1 downto 0); --00设置 01输验证
        unlock: out std_logic;  --解锁
        err: out std_logic; --错误
        alarm: out std_logic    --报警（三次错误）
    );
end entity num_lock;

architecture bhv of num_lock is
    type password is array (3 downto 0) of integer;
    signal set_password: password;  --用户设置密码
    signal state: integer := 100;
    signal err_count: integer := 0; --错误次数
    constant ADMIN_PASSWORD: password := (9, 8, 7, 6);  --管理员密码
    signal admin_input_count: integer := 0; --管理员密码计数（避免使用状态机）
    signal alarm_signal: std_logic := '0';
    signal err_signal: std_logic := '0';
    
begin

    process (clk, rst)
    begin
        if (rst = '1') then
            unlock <= '0';
            err_signal <= '0';
            state <= 0;
        elsif (clk'event and clk = '1') then
            if (alarm_signal = '1') then    --报警状态，必须输入管理员密码恢复
                if (conv_integer(code) = ADMIN_PASSWORD(admin_input_count)) then
                    if (admin_input_count > 2) then
                        err_count <= 0;
                        alarm_signal <= '0';
                        state <= 100;
						admin_input_count <= 0;
						err_signal <= '0';
                    else
                        admin_input_count <= admin_input_count + 1;
                    end if;
                else
                    admin_input_count <= 0;
                end if;
            elsif (mode = "00") then    --设置密码
                case state is
                    when 0 => state <= 1;
                        set_password(0) <= conv_integer(code);
                    when 1 => state <= 2;
                        set_password(1) <= conv_integer(code);
                    when 2 => state <= 3;
                        set_password(2) <= conv_integer(code);
                    when 3 => state <= 100;
                        set_password(3) <= conv_integer(code);
                    when others => NULL;
                end case;
            elsif (mode = "01") then    --验证密码
                case state is
                    when 0 =>
                        if (conv_integer(code) = set_password(0)) then  --0位正确
                            state <= 1;
                            err_signal <= '0';
                        else    --0位错误
                            err_signal <= '1';
									 state <= 100;
									 if (err_count > 1) then
                                alarm_signal <= '1';
									 else 
										  err_count <= err_count + 1;
									 end if;
                        end if;
                    when 1 =>
                        if (conv_integer(code) = set_password(1)) then
                            state <= 2;
                        else
                            err_signal <= '1';
									 state <= 100;
									 if (err_count > 1) then
                                alarm_signal <= '1';
									 else 
										  err_count <= err_count + 1;
									 end if;
                        end if;
                    when 2 =>
                        if (conv_integer(code) = set_password(2)) then
                            state <= 3;
                        else
                            err_signal <= '1';
									 state <= 100;
									 if (err_count > 1) then
                                alarm_signal <= '1';
									 else 
										  err_count <= err_count + 1;
									 end if;
                        end if;
                    when 3 =>
                        if (conv_integer(code) = set_password(3)) then
                            state <= 100;
									 unlock <= '1';
                        else
                            err_signal <= '1';
									 state <= 100;
									 if (err_count > 1) then
                                alarm_signal <= '1';
									 else 
										  err_count <= err_count + 1;
									 end if;
                        end if;
                    when others => NULL;
                end case;
            end if;
        end if;
    end process;

    process (err_signal)
    begin
        err <= err_signal;
    end process;
	 
    process (alarm_signal)
    begin
        alarm <= alarm_signal;
    end process;
    
end architecture bhv;

