library IEEE;
use IEEE.std_logic_1164.all;
ENTITY NOT_GATE is port(
	a: in std_logic;
	o: out std_logic);
end NOT_GATE;

architecture logic_not of NOT_GATE is
begin
	o<= (not a);
end logic_not;
