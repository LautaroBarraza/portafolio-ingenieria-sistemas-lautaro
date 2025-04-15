-- Code your design here
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;

ENTITY TB_ALU32 is
END TB_ALU32;

architecture test of TB_ALU32 is
--instanciacion componentes
component ALU32 
	port(a,b: in std_logic_vector(31 downto 0);ctrl: in std_logic_vector(2 downto 0);z: out std_logic; rst: out std_logic_vector(31 downto 0)); 
end component;

--instanciacion señales
signal a,b,rst: std_logic_vector(31 downto 0);
signal ctrl: std_logic_vector(2 downto 0);
signal z: std_logic;


begin
	al: ALU32 port map(a=>a,b=>b,ctrl=>ctrl,z=>z,rst=>rst);
	process
   	begin
        	a <= x"00000001"; b <= x"00000002" ; ctrl <="010" ; wait for 10 ns;
        	a <= X"00101010"; b <= x"10201010"; ctrl <="000" ; wait for 10 ns;
        wait;
    end process;
end test;  
