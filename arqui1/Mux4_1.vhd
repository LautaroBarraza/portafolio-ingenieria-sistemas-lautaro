library IEEE;
use IEEE.std_logic_1164.all;

ENTITY Mux4_1 is port(
	a,b,c,d: in std_logic;
	sel: in std_logic_vector(1 downto 0);
	o: out std_logic);
end Mux4_1;

architecture structural of Mux4_1 is
	--declaracion de componentes
	component mux2_1 
		port(a,b,s: in std_logic; o: out std_logic);
	end component;
	--declaracion de se�ales
	signal m1,m2:std_logic;
begin
	s1: mux2_1 port map(a=>a,b=>b,s=>sel(0),o=>m1);
	s2: mux2_1 port map(a=>c,b=>d,s=>sel(0),o=>m2);
	s3: mux2_1 port map(a=>m1,b=>m2,s=>sel(1),o=>o);
	--nota salio error si pongo como variable de componente M1,M2,M3;
end structural;
