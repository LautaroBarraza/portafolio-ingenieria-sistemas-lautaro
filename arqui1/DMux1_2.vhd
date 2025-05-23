library IEEE;
use IEEE.std_logic_1164.all;
ENTITY DMux1_2 is port(
	a: in std_logic;
	s: in std_logic;
	o1: out std_logic;
	o2: out std_logic
);
end DMux1_2;

architecture structural of DMux1_2 is
	--declaracion componentes
	component and_gate
	port (a,b: in std_logic; o: out std_logic);
	end component;
	component not_gate
	port (a:in std_logic; o:out std_logic);
	end component;
	--declaracion se�ales
	signal sn: std_logic;
begin
	G0: not_gate port map(a=>s, o=>sn);
	G1: and_gate port map(a=>a, b=>sn, o=>o1);
	G2: and_gate port map(a=>a, b=>s, o=>o2);

end structural;
