import multiplier_exp   :: *;

module mkTest_exp (Empty);
Ifc_multiplier m <- mkMult_exp;


Reg #(Bit #(5)) rg_y <- mkReg (0);


rule rl_go(rg_y >= 16 || rg_y == 0);
	$display ("Product ");
	m.get_input(16'b0100000100101100,16'b0101010011100101,32'b01000001110010101100001010010000);
	$display ("* %d",rg_y);
	//m.get_inp(63536,1);
	rg_y <= rg_y + 1;
	$display ("* %d",rg_y);
endrule

rule rl_finish (rg_y < 16 && rg_y != 0);
	$display ("$ ");
	let z = m.send_output();
	$display ("Product = %b", z);
	$display ("Product = %d", z);
	rg_y <= rg_y + 1;
endrule
endmodule: mkTest_exp


