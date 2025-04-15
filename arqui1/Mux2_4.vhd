library IEEE;
use IEEE.std_logic_1164.all;
ENTITY Mux2_4 IS PORT(
	a: in std_logic_vector(3 downto 0);
    b: in std_logic_vector(3 downto 0);
    s: in std_logic;
    o: out std_logic_vector(3 downto 0));
END Mux2_4;
architecture structural of Mux2_4 is
	component mux2_1 
		port(a,b,s:in std_logic;o: out std_logic);
	end component;

begin
	gen: for i in 0 to 3 generate
		M: mux2_1 port map(a=>a(i),b=>b(i),s=>s,o=>o(i));
	end generate;
end structural;


