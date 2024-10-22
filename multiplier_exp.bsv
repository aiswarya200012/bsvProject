interface Ifc_multiplier;
	method Action get_input(Bit#(16) a, Bit#(16) b, Bit#(32) c);
	method Bit#(32) send_output();
endinterface

function Bit#(2) full_adder(Bit#(1) a, Bit#(1) b, Bit#(1) c);
	Bit #(1) sum;
	Bit #(1) carry;	
	sum = a ^ b ^ c;
	carry = a&b | b&c | c&a;
	return {sum,carry};
endfunction: full_adder

function Bit#(33) adder_32 (Bit#(32)inp1,Bit#(32)inp2);
	Bit #(33) result;
	Bit #(5) temp;
	Bit #(1) carry;
	
	temp          = adder_4(inp1[3:0],inp2[3:0],0);
	result[3:0]   = temp[3:0];
	carry         = temp[4];
	
	temp          = adder_4(inp1[7:4],inp2[7:4],carry);
	result[7:4]   = temp[3:0];
	carry         = temp[4];
	
	temp          = adder_4(inp1[11:8],inp2[11:8],carry);
	result[11:8]  = temp[3:0];
	carry         = temp[4];
	
	temp          = adder_4(inp1[15:12],inp2[15:12],carry);
	result[15:12] = temp[3:0];
	carry         = temp[4];
	
	temp          = adder_4(inp1[19:16],inp2[19:16],carry);
	result[19:16] = temp[3:0];
	carry         = temp[4];
	
	temp          = adder_4(inp1[23:20],inp2[23:20],carry);
	result[23:20] = temp[3:0];
	carry         = temp[4];
	
	temp          = adder_4(inp1[27:24],inp2[27:24],carry);
	result[27:24] = temp[3:0];
	carry         = temp[4];
	
	temp          = adder_4(inp1[31:28],inp2[31:28],carry);
	result[31:28] = temp[3:0];
	result[32] = temp[4];
	
	return result;
	
endfunction: adder_32

function Bit#(5) adder_4(Bit#(4) a, Bit#(4) b, Bit#(1) c);
	Bit #(5) result;
	Bit #(2) temp;
	Bit #(1) carry;
	
	temp      = full_adder(a[0],b[0],c);
	result[0] = temp[1];
	carry     = temp[0];
	
	temp      = full_adder(a[1],b[1],carry);
	result[1] = temp[1];
	carry     = temp[0];
	
	temp      = full_adder(a[2],b[2],carry);
	result[2] = temp[1];
	carry     = temp[0];

	temp      = full_adder(a[3],b[3],carry);
	result[3] = temp[1];
	result[4] = temp[0];
	
	return result;
	
endfunction: adder_4

function Bit#(8) adder_8 (Bit#(8)inp1,Bit#(8)inp2);
	Bit #(8) result;
	Bit #(5) temp;
	Bit #(1) carry;
	
	temp        = adder_4(inp1[3:0],inp2[3:0],0);
	result[3:0] = temp[3:0];
	carry       = temp[4];
	
	temp        = adder_4(inp1[7:4],inp2[7:4],carry);
	result[7:4] = temp[3:0];
	
	return result;
	
endfunction: adder_8

function Bit#(16) adder_16 (Bit#(16)inp1,Bit#(16)inp2);
	Bit #(16) result;
	Bit #(5) temp;
	Bit #(1) carry;
	
	temp        = adder_4(inp1[3:0],inp2[3:0],0);
	result[3:0] = temp[3:0];
	carry       = temp[4];
	
	temp        = adder_4(inp1[7:4],inp2[7:4],carry);
	result[7:4] = temp[3:0];
	carry       = temp[4];
	
	temp          = adder_4(inp1[11:8],inp2[11:8],carry);
	result[11:8]  = temp[3:0];
	carry         = temp[4];
	
	temp          = adder_4(inp1[15:12],inp2[15:12],carry);
	result[15:12] = temp[3:0];
	
	return result;
	
endfunction: adder_16

// function for addition 
function Result exponent_add(Bit#(24) inp_mantissaA, Bit#(24) inp_mantissaB, Bit#(8) inp_exponenta,Bit#(8) inp_exponentb, Bit#(1) inp_signa, Bit#(1) inp_signb);
	Bit#(32) mantissaG;
	Bit#(32) mantissaS;
	Bit#(32) mantissa;
	Bit#(23) mantissa_temp;
	Bit#(8) exponentG;
	Bit#(8) exponentS;
	Bit#(8) exponent_temp;
	Bit#(1) signG;
	Bit#(1) signS;
	Bit#(1) sign_temp;
	Bit#(33) mantissa1;
	
	Result out;

	if (inp_exponenta > inp_exponentb) begin
		mantissaG = {inp_mantissaA, 8'b0};
		mantissaS = {inp_mantissaB, 8'b0};
		exponentG = inp_exponenta;
		exponentS = inp_exponentb;
		signG	  = inp_signa;
		signS	  = inp_signb;
	end
	else begin
		mantissaG = {inp_mantissaB, 8'b0};
		mantissaS = {inp_mantissaA, 8'b0};
		exponentG = inp_exponentb;
		exponentS = inp_exponenta;
		signG	  = inp_signb;
		signS	  = inp_signa;
	end
	
	//convert exponents to same power
	Bit#(8) count = 0;
	while(exponentG != exponentS && count < 32)begin
		exponentS = exponentS + 1;
		mantissaS = mantissaS >> 1;
		count     = count + 1;
	end

	exponent_temp = exponentG;
	
	// compare signs for addition/subtraction of mantissa
	if      (signG == 0 && signS == 0) begin
		mantissa1  = adder_32(mantissaS , mantissaG);
		sign_temp = 1'b0;
	end
	else begin
		mantissa1  = adder_32(mantissaS , mantissaG);
		sign_temp = 1'b1;
	end
	/*
	else if (signG == 0 && signS == 1)begin
		mantissa1 = mantissaG - mantissaS;
		sign_temp = 1'b0;
	end
	else begin
		mantissa1  = mantissaG - mantissaS;
		sign_temp = 1'b1;
	end
	*/
	
	// Limit shifts and ensure termination
    Bit #(8) shift_count = 0;
    
    if(mantissa1[32] == 1)
    begin
    	mantissa = mantissa1[32:1];
	exponent_temp = exponent_temp  + 1;
    end
    else
    begin
    	mantissa = mantissa1[31:0];
	while(mantissa[31] == 0 &&  shift_count<32)
		begin
			mantissa      = mantissa << 1;
			exponent_temp = exponent_temp  - 1;
			shift_count   = shift_count + 1;
		end
	
	end	
	// round off
	Bit#(2) gr = mantissa[7:6];
	Bit#(1) s  = mantissa[5] | mantissa[4] | mantissa[3] | mantissa[2] | mantissa[1] | mantissa[0];
	
	mantissa_temp = mantissa[30:8];
	
	// if GRS = 100, next bit == 1 round off, else round down
	if (gr[0]==0 && s==0 && gr[1] == 1)begin
		if (mantissa[8] == 0)begin
			mantissa_temp = mantissa_temp;
		end
		else if (mantissa[8] == 1)begin
			mantissa_temp = mantissa_temp + 1;
		end
	end
	// if GRS = 0XX, round down
	else if (gr[1] == 0) begin
		mantissa_temp = mantissa_temp;
	end
	// if GRS = 101, 110, 111, round off
	else begin
		mantissa_temp = mantissa_temp + 1;
	end
	
	
	out.sign_val 	 = sign_temp;
	out.mantissa_val = mantissa_temp;
	out.exponent_val = exponent_temp;
	
	return out;
	
endfunction: exponent_add


function Result exponent_cal(Bit#(8) mantissaB, Bit#(16) d, Bit#(24) mantissaC, Bit#(8) inp_exponenta,Bit#(8) inp_exponentb,Bit#(8) inp_exponentc, Bit#(1) signA, Bit#(1) signB, Bit#(1) signC);

	Bit#(16) product = 0;
	Bit#(8) inp_exponent = inp_exponenta + inp_exponentb;
	Bit#(24) mantissa_temp;
	Result mac_out;
	Result out;
	
	// mantissa multiplication
	while(mantissaB != 0) begin
		if (mantissaB[0] == 1) begin
			product = adder_16(product , d);
		end
		d         = d << 1'b1; // Shift d left
		mantissaB = mantissaB >> 1'b1; // Shift inp_B right
	end
	
	if(product[15] == 1'b1) begin
		out.mantissa_val = {product[14:0],8'd0};
		out.exponent_val = inp_exponent+1;		
	end
	else if (product[14] == 1) begin
		out.exponent_val = inp_exponent;
		out.mantissa_val = {product[13:0],9'd0};
	end
	else begin
		// Limit shifts and ensure termination
    	Bit #(8) shift_count = 0;
		while(product[14] == 0 &&  shift_count<16)
			begin
					product      = product << 1;
					inp_exponent = inp_exponent  - 1;
					shift_count  = shift_count + 1;
			end
		
		out.mantissa_val = {product[13:0],9'd0};
		out.exponent_val = inp_exponent;
	end
	out.sign_val     = signA^signB;
	out.exponent_val = out.exponent_val-127;
    mantissa_temp    = {1'b1, out.mantissa_val};
    mac_out          = exponent_add(mantissa_temp,mantissaC,out.exponent_val,inp_exponentc,out.sign_val,signC);
	
	return mac_out;

endfunction: exponent_cal
	
	
typedef struct {
	Bit #(1) sign_val;
	Bit #(23) mantissa_val;
	Bit #(8) exponent_val;
	}Result deriving (Bits,Eq);
	
(* synthesize *)
// MODULE
module mkMult_exp(Ifc_multiplier);
	// REGISTER
	//Wire#(Bit#(16)) product <- mkWire();
	Reg#(Bit#(16)) d <- mkReg(0);
	
	Reg#(Bit#(8)) mantissaA <- mkReg(0);
	Reg#(Bit#(8)) mantissaB <- mkReg(0);
	Reg#(Bit#(24)) mantissaC <- mkReg(0);
	//Bit#(16) product1 = 0;

	Reg#(Bit#(16)) product <- mkReg(0);
	
	Reg#(Bit#(8)) exponentA <- mkReg(0);
	Reg#(Bit#(8)) exponentB <- mkReg(0);
	Reg#(Bit#(8)) exponentC <- mkReg(0);
	
	Reg#(Bit#(8)) exponent <- mkReg(0);
	Reg#(Bit#(16)) mantissa <- mkReg(0);
	
	Reg#(Bit#(3)) state <- mkReg(0);
	Reg#(Bit#(1)) temp <- mkReg(0);
	
	Reg#(Bit#(1)) signA <- mkReg(0);
	Reg#(Bit#(1)) signB <- mkReg(0);
	Reg#(Bit#(1)) signC <- mkReg(0);
	
	Reg#(Bit#(16)) i <- mkReg(0);
	
	Reg#(Result) value <- mkReg(unpack(0));
	
	
	

	// RULE for computing the product
	rule rl_compute (state == 1);
		value <= exponent_cal(mantissaB,d,mantissaC,exponentA,exponentB,exponentC,signA,signB,signC);
		state <= 2;
	endrule: rl_compute


	
	// METHOD to receive inputs
	method Action get_input(Bit#(16) a, Bit#(16) b, Bit#(32) c) if(state == 0);
		mantissaA <= {1,a[6:0]};
		mantissaB <= {1,b[6:0]};
		exponentA <= a[14:7];
		exponentB <= b[14:7];
		mantissaC <= {1,c[22:0]};
		exponentC <= c[30:23];
		signA     <= a[15];
		signB     <= b[15];
		signC     <= c[31];
		d         <= {8'b0,1,a[6:0]};
		state     <= 1;
	endmethod
	
	// METHOD to send product
	method Bit#(32) send_output() if(state == 2);
			return {value.sign_val, value.exponent_val, value.mantissa_val};
			//return 1;
	endmethod
	
	
endmodule: mkMult_exp
