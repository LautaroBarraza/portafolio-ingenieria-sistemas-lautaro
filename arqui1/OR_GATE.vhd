library IEEE;
use IEEE.std_logic_1164.all;
ENTITY OR_GATE is port(
	a: in std_logic;
	b: in std_logic;
	o: out std_logic);
end OR_GATE;

architecture logic_or of OR_GATE is
begin
	o<= (a or b);
end logic_or;
