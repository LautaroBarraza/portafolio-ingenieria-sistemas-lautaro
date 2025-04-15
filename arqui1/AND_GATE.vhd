library IEEE;
use IEEE.std_logic_1164.all;
ENTITY AND_GATE is port(
	a: in std_logic;
	b: in std_logic;
	o: out std_logic);
end AND_GATE;

architecture logic_and of AND_GATE is
begin
	o<= (a and b);
end logic_and;
