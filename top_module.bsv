package mac;

import multiplier_exp   :: *;
import multiplier   :: *;

interface Ifc;
	method Action getA(Bit#(16) a);
	method Action getB(Bit#(16) b);
	method Action getC(Bit#(32) c);
	method Action getS(Bit#(1) s);
	method Bit#(32) sendout_mac();
endinterface: Ifc

module topModule (Ifc);
	Reg#(Bit#(16)) A <- mkReg(0);
	Reg#(Bit#(16)) B <- mkReg(0);
	Reg#(Bit#(32)) C <- mkReg(0);
	Reg#(Bit#(1)) S <- mkReg(0);
	Reg#(Bit#(32)) mac_out <- mkReg(0);
	
	Reg#(Bool) gotA <- mkReg(false);
	Reg#(Bool) gotB <- mkReg(false);
	Reg#(Bool) gotC <- mkReg(false);
	Reg#(Bool) validMAC <- mkReg(false);
	
	Ifc_multiplier mac_fp <- mkMult_exp;
	Multiplier mac_int <- mkMult;	
	
	Bit#(16) A_int32;
	Bit#(16) B_int32;
	Bit#(32) C_int32;
	
	Bit#(16) A_fp32;
	Bit#(16) B_fp32;
	Bit#(32) C_fp32;
	
	rule rl_mux_input (got_A && got_B && got_C && got_S);
		if(S ==1) begin
			A_int32  <= A;
			B_int32  <= B;
			C_int32  <= C;
			mac_int.get_inp(A_int32,B_int32,C_int32);
			validMAC <= true;
		end
		else begin
			A_fp32   <= A;
			B_fp32   <= B;
			C_fp32   <= C;
			mac_fp.get_input(A_fp32,B_fp32,C_fp32);
			validMAC <= true;
		end
	endrule: rl_mux_input
	
	method Action getA(Bit#(16) a) if(!got_A);
		A        <= a;
		got_A    <= true;
		validMAC <= false;
	endmodule
	
	method Action getB(Bit#(16) B) if(!got_B);
		B        <= b;
		got_B    <= true;
		validMAC <= false;
	endmodule
	
	method Action getC(Bit#(32) C) if(!got_C);
		C        <= c;
		got_C    <= true;
		validMAC <= false;
	endmodule
	
	method Action getS(Bit#(1) S) if(!got_S);
		S        <= s;
		got_S    <= true;
		validMAC <= false;
	endmodule
	
	method Bit#(32) sendout_mac() if(validMAC == true);
		if(S == 1)begin
			return mac_int.send_out();
		end
		else begin
			return mac_fp.send_output();
		end
		got_A <= false;
		got_B <= false;
		got_C <= false;
		got_S <= false;
	endmethod

endmodule: topModule
endpackage: mac
