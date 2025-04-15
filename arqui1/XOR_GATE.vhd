library IEEE;
use IEEE.std_logic_1164.all;
ENTITY XOR_GATE is port(
	a: in std_logic;
	b: in std_logic;
	o: out std_logic);
end XOR_GATE;

architecture logic_xor of XOR_GATE is
begin
	o<= (a xor b);
end logic_xor;
