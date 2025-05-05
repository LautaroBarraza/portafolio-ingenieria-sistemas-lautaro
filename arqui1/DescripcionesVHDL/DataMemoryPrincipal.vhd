-- ======================
-- ====    Autor Martín Vázquez 
-- ====    Arquitectura de Computadoras 1 - 2024
--
-- ====== Memoria Principal de Datos - escritura y lectura de una palabra (4 bytes)
-- ====== Memoria de Nivel Inferior
-- ======================

library STD;
use STD.textio.all;

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.std_logic_textio.all;


entity DataMemoryPrincipal is
    generic(
        C_ELF_FILENAME    : string := "data";
        C_MEM_SIZE        : integer := 1024
	 );
    Port ( Addr : in std_logic_vector(31 downto 0);
           DataIn : in std_logic_vector(31 downto 0);
           RdStb : in std_logic ;
           WrStb : in std_logic ;
           Clk : in std_logic ;						  
           Reset: in std_logic;
           Rdy: out std_logic;
	       DataOut : out std_logic_vector(31 downto 0));
end DataMemoryPrincipal;

architecture mem_arch of DataMemoryPrincipal is 
	
    type matriz is array(0 to C_MEM_SIZE-1) of std_logic_vector(7 downto 0);
    signal memo: matriz; -- señal que posee las celdas de la memoria 
    signal aux : std_logic_vector (31 downto 0):= (others=>'0'); -- utilizado para la lectura
    
            
    -- señales que describe los estados de la máquina de estados que consume el tiempo
    type type_state is (init_st, time_st1, time_st2, time_st3);
    signal curr_st, next_st: type_state;
    
    -- señales que describen los contadores de ciclos para consumo de tiempo
    signal count_time, next_count_time: std_logic_vector(2 downto 0);

    -- señales de lectura y escritura de la memoria manejadas por la máquina de control que modela consumo de tiempo
    signal rd_memory, wr_memory: std_logic; 
    
    
begin
    -- ==== proceso que modela inicialización de la memoria y acceso a las celdas
    process (clk)
            variable init_memory : boolean := true;
            variable datum : STD_LOGIC_VECTOR(31 downto 0);
            file bin_file : text is C_ELF_FILENAME;
            variable  current_line : line;
            variable address : integer;
    begin
        
        if init_memory then
        -- esta rama del if se ejecuta por única vez al principio 
            -- primero iniciamos la memoria con ceros
                for i in 0 to C_MEM_SIZE-1 loop
                    memo(i) <= (others => '0');
                end loop; 
            
            -- luego cargamos el archivo en la misma
                address := 0;
                while (not endfile (bin_file)) loop
                    
                    readline (bin_file, current_line);					
                    
                    hread(current_line, datum);
                    assert address<C_MEM_SIZE 
                        report "Direccion fuera de rango en el fichero de la memoria"
                        severity failure;
                    memo(address) <= datum(31 downto 24);
                    memo(address+1) <= datum(23 downto 16);
                    memo(address+2) <= datum(15 downto 8);
                    memo(address+3) <= datum(7 downto 0);
                    address:= address+4;
            end loop;
            
            -- por ultimo cerramos el archivo y actualizamos el flag de memoria cargada
             file_close (bin_file);
             -- para que no se ejecute más esta rama del if correspondiente a la inicialización de la memoria
             init_memory := false; 
        
       elsif (rising_edge(clk)) then
             address := CONV_INTEGER(Addr(30 downto 0));
             if (wr_memory = '1') then
                memo(address) <= DataIn(31 downto 24);
                memo(address+1) <= DataIn(23 downto 16);
                memo(address+2) <= DataIn(15 downto 8);
                memo(address+3) <= DataIn(7 downto 0);
                
             elsif (rd_memory = '1')then
                aux(31 downto 24) <= memo(address);   
                aux(23 downto 16) <= memo(address+1);
                aux(15 downto 8) <= memo(address+2);
                aux(7 downto 0) <= memo(address+3);
             end if;
             
       end if;
    end process;

--  ======================
--  === Procesos que modelan máquina de estados utilizada para generar los 6 ciclos de reloj)
--  === involucrados en la lectura y escritura de la memoria principal coreespondiente a memoria de Datos
--  === LOS CICLOS EN UNA MEMORIA REAL HARÍAN CON QUE SE DETALLA A CONTINUACIÓN

--      ciclo 1 -> procesa dirección de fila en en el bus de direcciones
--      ciclo 2 -> procesa activación RAS# (Row Access Strobe)
--      ciclo 3 -> procesa dirección de columna en el bus de direcciones
--      ciclo 4 -> procesa activación CAS# (Column Access Strobe)
--      ciclo 5 -> latencia de búsqueda de palabra
--      ciclo 6 -> ciclo de transmisión por bus de datos

--  === lA MAQUINA DE ESTADOS MODELADA A CONTINUACIÓN, SOLO GENERA LOS 6 CICLOS PARA 
--  === FUNCIONAR EN LA SIMULACION COMO UNA MEMORIA REAL, PERO SE ACCEDE DE MAMERA 
--  === MÁS SIMPLE A LA ESTRUCTURA CON EL CONTENIDO DE DATOS
    
    process (clk, reset) 
    begin
        if (reset='1') then
            curr_st <= init_st;
            count_time <= (others => '0');
        elsif (falling_edge(clk)) then
            count_time <= next_count_time;
            curr_st <= next_st;
        end if;
    end process;
    
    
    state_machine: process (curr_st, RdStb, WrStb, count_time)
    begin
    
       case (curr_st) is
        
            when init_st =>
            -- cuando se activa WrStb o RdStb se procesa dirección de fila 
            -- en el bus de direcciones (ciclo 1)
                            Rdy <= '1';
                            next_count_time <= count_time;
                            next_st <= curr_st;
                            rd_memory <= '0';
                            wr_memory <= '0';
                            if (RdStb='1'or WrStb='1') then
                                Rdy <= '0';
                                next_count_time <= count_time + 1;
                                next_st <= time_st1;
                            end if;
           when time_st1 =>
            -- activación RAS# (ciclo 2)
                            Rdy <= '0';
                            next_count_time <= count_time + 1;
                            rd_memory <= '0';
                            wr_memory <= '0';
                            next_st <= time_st2;
                            
           when time_st2 =>
           -- procesa dirección de columna en bus de direcciones 
           -- y activación CAS# (ciclos 3 y 4)
                            Rdy <= '0';
                            next_count_time <= count_time + 1;
                            next_st <= curr_st;
                            rd_memory <= '0';
                            wr_memory <= '0';
                            if (count_time="011") then
                                next_st <= time_st3;
                            end if;    

           when time_st3 =>
           --  latencia de búsqueda de palabra y
           --  ciclo de transmisión por bus de datos  (ciclos 5 y 6)
                            Rdy <= '0';
                            next_count_time <= count_time + 1;
                            next_st <= curr_st;
                            rd_memory <= '0';
                            wr_memory <= '0';
                            if (count_time="101") then
                                next_count_time <= (others => '0');
                                Rdy <= '1';
                                rd_memory <= RdStb;
                                wr_memory <= WrStb;
                                next_st <= init_st;
                            end if;
           when others =>
                            Rdy <= '1';
                            next_count_time <= (others => '0');
                            next_st <= init_st;
                            rd_memory <= '0';
                            wr_memory <= '0';
        end case;
    end process;

   
    DataOut <= aux;	 


end mem_arch;
