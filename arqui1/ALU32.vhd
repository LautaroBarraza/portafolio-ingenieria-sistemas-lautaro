-- Code your design here
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;

ENTITY ALU32 is 
	port(a,b: in std_logic_vector(31 downto 0);ctrl: in std_logic_vector(2 downto 0);z: out std_logic; rst: out std_logic_vector(31 downto 0));
END ALU32;

architecture concurrent of ALU32 is

begin
	alu:process(a,b,ctrl)
	begin
		case ctrl is
			when "000"=> 
				rst<=(a and b);
			when "001"=> 
				rst<=(a or b);
			when "010"=> 
				rst<= (a+b);
			when "100"=> 
				rst<= b(15 downto 0)&x"0000";
			when "110"=> 
				rst<= (a-b);
			when "111"=> 
				if(a<b) then
					rst<=x"00000001";
				else
					rst<=x"00000000";
				end if;
			when others =>
				rst<=x"00000000";
		end case;
	end process;

	z<= '1' when rst=x"00000000" else '0';

end concurrent;
