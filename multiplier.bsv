interface Multiplier;
  method Action get_inp(Bit#(16) a, Bit#(16) b);
  method Bit#(32) send_out();
  method Bit#(32) send_d();
endinterface

(* synthesize *)
// MODULE
module mkMult(Multiplier);
	// REGISTER
	Reg#(Bit#(16)) inp_A <- mkReg(0);
	Reg#(Bit#(16)) inp_B <- mkReg(0);
	Reg#(Bit#(32)) product <- mkReg(0);
	Reg#(Bit#(32)) d <- mkReg(0);
	
	Reg#(Bit#(1)) state <- mkReg(0);

	// RULE for computing the product
	rule rl_compute (state == 1);
		if(inp_B != 0) begin
			if (inp_B[0] == 1) begin
				product <= product + d;
			end
			d <= d << 1; // Shift d left
			inp_B <= inp_B >> 1; // Shift inp_B right
		end
		else begin
			state <= 0;
		end
	endrule: rl_compute



	// METHOD to receive inputs
	method Action get_inp(Bit#(16) a, Bit#(16) b) if(state == 0);
		inp_A <= a;
		inp_B <= b;
		d <= signExtend(a);
		state<= 1;
	endmethod
	
	// METHOD to send product
	method Bit#(32) send_out() if(inp_B == 0);
			return product;
	endmethod
	
	// METHOD to send d
	method Bit#(32) send_d() if(inp_B == 0);
		return d;
	endmethod

endmodule: mkMult

