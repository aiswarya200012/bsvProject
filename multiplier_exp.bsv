interface Ifc_multiplier;
	method Action get_input(Bit#(16) a,Bit#(16) b);
	method Bit#(32) send_output();
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
module mkMult_exp(Ifc_multiplier);
	// REGISTER
	Wire#(Bit#(16)) product <- mkWire();
	Reg#(Bit#(16)) d <- mkReg(0);
	
	Reg#(Bit#(8)) mantissaA <- mkReg(0);
	Reg#(Bit#(8)) mantissaB <- mkReg(0);
	
	Reg#(Bit#(16)) product1 <- mkReg(0);
	Reg#(Bit#(16)) productx <- mkReg(0);
	
	Reg#(Bit#(8)) exponentA <- mkReg(0);
	Reg#(Bit#(8)) exponentB <- mkReg(0);
	
	Reg#(Bit#(8)) exponent <- mkReg(0);
	Reg#(Bit#(23)) mantissa <- mkReg(0);
	
	Reg#(Bit#(3)) state <- mkReg(0);
	Reg#(Bit#(1)) temp <- mkReg(0);
	
	Reg#(Bit#(1)) signA <- mkReg(0);
	Reg#(Bit#(1)) signB <- mkReg(0);
	
	// RULE for computing the product
	rule rl_compute (state == 1);
		if(mantissaB != 0) begin
			if (mantissaB[0] == 1) begin
				product1 <= adder_16(product1 , d);
			end
			d <= d << 1'b1; // Shift d left
			mantissaB <= mantissaB >> 1'b1; // Shift inp_B right
		end
		else begin
			product <= product1;
			state<=2;
		end
	endrule: rl_compute

	rule exponent_calc (state == 2);
	if(product1[15]==1)begin
		exponent <= exponentA + exponentB + 1;
		mantissa <= zeroExtend(product1[14:0]);
		state <= 4;
	end
	else if (product1[14] == 1) begin
		exponent <= exponentA + exponentB;
		mantissa <= zeroExtend(product1[13:0]);
		state <= 4;
	end
	else begin
		state <= 3;
		temp <= 1;
	end

	endrule: exponent_calc


	rule compare (state == 3); 
	if (temp == 1)begin
		productx <= product1;
		exponent <= exponentA + exponentB;
		temp <= 0;
		end
	else begin
		if(productx[14] == 0 && productx != 0)begin
			productx <= productx << 1;
			exponent <= exponent - 1;
		end
		else begin
			mantissa <= zeroExtend(productx);
			state <= 4;
		end
	end
	endrule : compare
	
	
	// METHOD to receive inputs
	method Action get_input(Bit#(16) a,Bit#(16) b) if(state == 0);
		mantissaA <= {1,a[6:0]};
		mantissaB <= {1,b[6:0]};
		exponentA <= a[14:7];
		exponentB <= b[14:7];
		signA <= a[15];
		signB <= b[15];
		d <= zeroExtend(mantissaA);
		state<= 1;
	endmethod
	
	// METHOD to send product
	method Bit#(32) send_output() if(state == 4);
			return {signA^signB, exponent, mantissa};
			//return 1;
	endmethod
	
endmodule: mkMult_exp
