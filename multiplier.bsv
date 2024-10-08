interface Multiplier;
  method Action get_inp(Bit#(8) a, Bit#(8) b);
  method Bit#(16) send_out();
  method Bit#(16) send_d();
endinterface

function Bit#(16) adder_16 (Bit#(16)inp1,Bit#(16)inp2);
	Bit #(16) result;
	Bit #(5) temp;
	Bit #(1) carry;
	
	temp = adder_4(inp1[3:0],inp2[3:0],0);
	result[3:0] = temp[3:0];
	carry = temp[4];
	
	temp = adder_4(inp1[7:4],inp2[7:4],carry);
	result[7:4] = temp[3:0];
	carry = temp[4];
	
	temp = adder_4(inp1[11:8],inp2[11:8],carry);
	result[11:8] = temp[3:0];
	carry = temp[4];
	
	temp = adder_4(inp1[15:12],inp2[15:12],carry);
	result[15:12] = temp[3:0];
	
	return result;
	
endfunction: adder_16

function Bit#(2) full_adder(Bit#(1) a, Bit#(1) b, Bit#(1) c);
	Bit #(1) sum;
	Bit #(1) carry;	
	sum = a ^ b ^ c;
	carry = a&b | b&c | c&a;
	return {sum,carry};
endfunction: full_adder

function Bit#(5) adder_4(Bit#(4) a, Bit#(4) b, Bit#(1) c);
	Bit #(5) result;
	Bit #(2) temp;
	Bit #(1) carry;
	
	temp = full_adder(a[0],b[0],c);
	result[0] = temp[1];
	carry = temp[0];
	
	temp = full_adder(a[1],b[1],carry);
	result[1] = temp[1];
	carry = temp[0];
	
	temp = full_adder(a[2],b[2],carry);
	result[2] = temp[1];
	carry = temp[0];

	temp = full_adder(a[3],b[3],carry);
	result[3] = temp[1];
	result[4] = temp[0];
	
	return result;
	
endfunction: adder_4


(* synthesize *)
// MODULE
module mkMult(Multiplier);
	// REGISTER
	Reg#(Bit#(16)) inp_A <- mkReg(0);
	Reg#(Bit#(16)) inp_B <- mkReg(0);
	Reg#(Bit#(16)) product <- mkReg(0);
	Reg#(Bit#(16)) d <- mkReg(0);
	
	Reg#(Bit#(1)) state <- mkReg(0);

	// RULE for computing the product
	rule rl_compute (state == 1);
		if(inp_B != 0) begin
			if (inp_B[0] == 1) begin
				product <= adder_16(product , d);
			end
			d <= d << 1'b1; // Shift d left
			inp_B <= inp_B >> 1'b1; // Shift inp_B right
		end
	endrule: rl_compute



	// METHOD to receive inputs
	method Action get_inp(Bit#(8) a, Bit#(8) b) if(state == 0);
		inp_A <= signExtend(a);
		inp_B <= signExtend(b);
		d <= signExtend(a);
		state<= 1;
	endmethod
	
	// METHOD to send product
	method Bit#(16) send_out() if(inp_B == 0);
			return product;
	endmethod
	
	// METHOD to send d
	method Bit#(16) send_d() if(inp_B == 0);
		return d;
	endmethod

endmodule: mkMult

