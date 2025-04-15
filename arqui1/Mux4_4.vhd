library IEEE;
use IEEE.std_logic_1164.all;
ENTITY Mux4_4 IS PORT(
	a,b,c,d: in std_logic_vector(3 downto 0);
    	s: in std_logic_vector(1 downto 0);
    	o: out std_logic_vector(3 downto 0));
END Mux4_4;
architecture structural of Mux4_4 is
	component mux4_1 
		port(a,b,c,d:in std_logic;s:in std_logic_vector(1 downto 0);o: out std_logic);
	end component;

begin
	gen: for i in 0 to 3 generate
		M: mux4_1 port map(a=>a(i),b=>b(i),c=>c(i),d=>d(i),s=>s,o=>o(i));
	end generate;
end structural;
