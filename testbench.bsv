import multiplier   :: *;

module mkTest (Empty);
Multiplier m <- mkMult;

Reg #(Bit #(5)) rg_y <- mkReg (0);

rule rl_go(rg_y > 2 || rg_y == 0);
	m.get_inp(16'b1100,16'b1110);
	rg_y <= rg_y + 1;
endrule

rule rl_finish (rg_y < 2 && rg_y != 0);
	let z = m.send_out ();
	$display ("Product = %d", z);
	let k = m.send_d();
	rg_y <= rg_y + 1;
	$display ("d = %d", k);
endrule
endmodule: mkTest
