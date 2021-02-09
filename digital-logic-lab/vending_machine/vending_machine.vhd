library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity vending_machine is
    port (
        clk : in std_logic; --输入
        rst : in std_logic; --输入复位
        coin_in : in std_logic_vector (1 downto 0);
        --投币输入，11、10、11分别代表1元、5角、1角
        item_select: in std_logic_vector (1 downto 0);
        --商品选择输入，11、10、01三种商品 
        item_out : out std_logic_vector (1 downto 0) := "00"; 
        --售卖商品输出
        coin_out : out std_logic_vector (1 downto 0)  := "00"
        --退币输出
    );
end entity vending_machine;


architecture behavior of vending_machine is
    type state_type is (
        idle,   --初态
        wait_money, --接受投币状态
        return_money    --退币状态
    );
    type prices is array (3 downto 1) of integer;
    signal current_state: state_type := idle;
    signal money: integer range 0 to 30 := 0;
    --售货机在本轮交易中持有的金额
    signal which_item: integer range 0 to 3;
    --选中商品的十进制编号
    constant item_price: prices := (25, 14, 7);
    --三种商品价格，分别为11、10、01

begin
    process (clk, rst)
    begin
        --复位，若本轮交易有剩余金额则退币
        if (rst = '1') then
            if (money > 0) then
                current_state <= return_money;
            else
                current_state <= idle;
            end if;
        --时钟上升沿，进行下一步行动
        elsif (clk'event and clk = '1') then
            case current_state is
                when idle =>
                    --接受商品选择输入
                    if (item_select /= "00") then
                        which_item <= conv_integer(item_select);
                        current_state <= wait_money;
                    end if;
                when wait_money =>
                    --接受投币，金额增加
                    if (coin_in = "01") then
                        money <= money + 1;
                    elsif (coin_in = "10") then
                        money <= money + 5;
                    elsif (coin_in = "11") then
                        money <= money + 10;
                    end if;
                    --投入金额达到商品价格，售出商品
                    if (money > item_price(which_item)) then
                        money <= money - item_price(which_item);
                        current_state <= return_money;
                        item_out <= std_logic_vector(to_unsigned(which_item, item_out'length));
                    end if;
                when return_money =>
                    item_out <= "00";   --还原商品输出
                    --面值由大到小，依次退币
                    if (money > 9) then
                        coin_out <= "11";
                        money <= money - 10;
                    elsif (money > 4) then
                        coin_out <= "10";
                        money <= money - 5;
                    elsif (money > 0) then
                        coin_out <= "01";
                        money <= money - 1;
                    --退币完成，返回初态
                    else
                        coin_out <= "00";
                        current_state <= idle;
                    end if;
            end case;
        end if;
    end process;

end architecture behavior;