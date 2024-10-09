// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop.h"
#include "Vtop__Syms.h"

#include "verilated_dpi.h"

//==========

void Vtop::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtop::eval\n"); );
    Vtop__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/shakti/bluespec_demo_examples/mac/verilog/mkMult.v", 36, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vtop::_eval_initial_loop(Vtop__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/shakti/bluespec_demo_examples/mac/verilog/mkMult.v", 36, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vtop::_combo__TOP__2(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_combo__TOP__2\n"); );
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkMult__DOT__CLK = vlTOPp->CLK;
    vlTOPp->mkMult__DOT__RST_N = vlTOPp->RST_N;
    vlTOPp->mkMult__DOT__get_inp_a = vlTOPp->get_inp_a;
    vlTOPp->mkMult__DOT__get_inp_b = vlTOPp->get_inp_b;
    vlTOPp->mkMult__DOT__get_inp_c = vlTOPp->get_inp_c;
    vlTOPp->mkMult__DOT__EN_get_inp = vlTOPp->EN_get_inp;
    vlTOPp->mkMult__DOT__WILL_FIRE_get_inp = vlTOPp->EN_get_inp;
}

VL_INLINE_OPT void Vtop::_sequent__TOP__4(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__4\n"); );
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkMult__DOT__inp_C_EN) {
            vlTOPp->mkMult__DOT__inp_C = vlTOPp->mkMult__DOT__inp_C_D_IN;
        }
    } else {
        vlTOPp->mkMult__DOT__inp_C = 0U;
    }
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkMult__DOT__result_EN) {
            vlTOPp->mkMult__DOT__result = vlTOPp->mkMult__DOT__result_D_IN;
        }
    } else {
        vlTOPp->mkMult__DOT__result = 0U;
    }
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkMult__DOT__state_EN) {
            vlTOPp->mkMult__DOT__state = vlTOPp->mkMult__DOT__state_D_IN;
        }
    } else {
        vlTOPp->mkMult__DOT__state = 0U;
    }
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkMult__DOT__inp_B_EN) {
            vlTOPp->mkMult__DOT__inp_B = vlTOPp->mkMult__DOT__inp_B_D_IN;
        }
    } else {
        vlTOPp->mkMult__DOT__inp_B = 0U;
    }
    if (vlTOPp->RST_N) {
        if (vlTOPp->mkMult__DOT__inp_A_EN) {
            vlTOPp->mkMult__DOT__inp_A = vlTOPp->mkMult__DOT__inp_A_D_IN;
        }
    } else {
        vlTOPp->mkMult__DOT__inp_A = 0U;
    }
    vlTOPp->mkMult__DOT__send_out = vlTOPp->mkMult__DOT__result;
    vlTOPp->mkMult__DOT__CAN_FIRE_get_inp = (0U == (IData)(vlTOPp->mkMult__DOT__state));
    vlTOPp->mkMult__DOT__RDY_get_inp = (0U == (IData)(vlTOPp->mkMult__DOT__state));
    vlTOPp->mkMult__DOT__RDY_send_out = (2U == (IData)(vlTOPp->mkMult__DOT__state));
    vlTOPp->mkMult__DOT__CAN_FIRE_RL_rl_compute = (1U 
                                                   == (IData)(vlTOPp->mkMult__DOT__state));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9 
        = ((1U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__inp_A) : 0U);
    vlTOPp->send_out = vlTOPp->mkMult__DOT__send_out;
    vlTOPp->RDY_get_inp = vlTOPp->mkMult__DOT__RDY_get_inp;
    vlTOPp->RDY_send_out = vlTOPp->mkMult__DOT__RDY_send_out;
    vlTOPp->mkMult__DOT__result_EN = vlTOPp->mkMult__DOT__CAN_FIRE_RL_rl_compute;
    vlTOPp->mkMult__DOT__WILL_FIRE_RL_rl_compute = vlTOPp->mkMult__DOT__CAN_FIRE_RL_rl_compute;
    vlTOPp->mkMult__DOT__x___05Fh10105 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 6U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh10188 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 5U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh10271 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 4U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh10667 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xbU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xaU)));
    vlTOPp->mkMult__DOT__x___05Fh10793 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xaU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh10876 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 9U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh10959 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 8U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh11354 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xeU)));
    vlTOPp->mkMult__DOT__x___05Fh11480 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xdU)));
    vlTOPp->mkMult__DOT__x___05Fh11563 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xcU)));
    vlTOPp->mkMult__DOT__x___05Fh11646 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xbU)));
    vlTOPp->mkMult__DOT__x___05Fh6412 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                >> 3U) 
                                               ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                  >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh9440 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                >> 2U) 
                                               ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                  >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh9979 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                >> 7U) 
                                               ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                  >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh11752 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xdU)));
    vlTOPp->mkMult__DOT__x___05Fh11737 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xcU)));
    vlTOPp->mkMult__DOT__x___05Fh11722 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xbU)));
    vlTOPp->mkMult__DOT__x___05Fh11080 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xbU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xaU)));
    vlTOPp->mkMult__DOT__x___05Fh11065 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 0xaU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh11050 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 9U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh11035 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 8U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh10392 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 7U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh10377 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 6U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh10362 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 5U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh10347 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                 >> 4U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh9707 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                >> 3U) 
                                               & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                  >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh9692 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                >> 2U) 
                                               & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                  >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh6282 = (1U & (
                                                   ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                                    >> 1U) 
                                                   & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__y___05Fh9691 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh6282) 
                                         & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                            >> 2U));
    vlTOPp->mkMult__DOT__y___05Fh9693 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                          >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh6282));
    vlTOPp->mkMult__DOT__x___05Fh9690 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh9692) 
                                         | (IData)(vlTOPp->mkMult__DOT__y___05Fh9693));
    vlTOPp->mkMult__DOT__carry___05Fh6285 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh9690) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh9691));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh6200 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh6412) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh6285)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh9440) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh6282)) 
                     << 2U) | ((2U & ((0xfffffffeU 
                                       & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9)) 
                                      ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                         << 1U))) | 
                               (1U & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9)))));
    vlTOPp->mkMult__DOT__y___05Fh9706 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh6285) 
                                         & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                            >> 3U));
    vlTOPp->mkMult__DOT__y___05Fh9708 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                          >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh6285));
    vlTOPp->mkMult__DOT__x___05Fh9705 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh9707) 
                                         | (IData)(vlTOPp->mkMult__DOT__y___05Fh9708));
    vlTOPp->mkMult__DOT__carry___05Fh6100 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh9705) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh9706));
    vlTOPp->mkMult__DOT__y___05Fh10346 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh6100) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 4U));
    vlTOPp->mkMult__DOT__y___05Fh10348 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh6100));
    vlTOPp->mkMult__DOT__x___05Fh10345 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh10347) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh10348));
    vlTOPp->mkMult__DOT__carry___05Fh9846 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh10345) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh10346));
    vlTOPp->mkMult__DOT__y___05Fh10361 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh9846) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 5U));
    vlTOPp->mkMult__DOT__y___05Fh10363 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 4U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh9846));
    vlTOPp->mkMult__DOT__x___05Fh10360 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh10362) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh10363));
    vlTOPp->mkMult__DOT__carry___05Fh9849 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh10360) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh10361));
    vlTOPp->mkMult__DOT__y___05Fh10376 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh9849) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 6U));
    vlTOPp->mkMult__DOT__y___05Fh10378 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 5U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh9849));
    vlTOPp->mkMult__DOT__x___05Fh10375 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh10377) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh10378));
    vlTOPp->mkMult__DOT__carry___05Fh9852 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh10375) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh10376));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh6170 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh9979) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh9852)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh10105) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh9849)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh10188) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh9846)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh10271) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh6100)))));
    vlTOPp->mkMult__DOT__y___05Fh10391 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh9852) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 7U));
    vlTOPp->mkMult__DOT__y___05Fh10393 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 6U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh9852));
    vlTOPp->mkMult__DOT__x___05Fh10390 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh10392) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh10393));
    vlTOPp->mkMult__DOT__carry___05Fh6102 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh10390) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh10391));
    vlTOPp->mkMult__DOT__y___05Fh11034 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh6102) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 8U));
    vlTOPp->mkMult__DOT__y___05Fh11036 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 7U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh6102));
    vlTOPp->mkMult__DOT__x___05Fh11033 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11035) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh11036));
    vlTOPp->mkMult__DOT__carry___05Fh10534 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11033) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh11034));
    vlTOPp->mkMult__DOT__y___05Fh11049 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh10534) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 9U));
    vlTOPp->mkMult__DOT__y___05Fh11051 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 8U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh10534));
    vlTOPp->mkMult__DOT__x___05Fh11048 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11050) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh11051));
    vlTOPp->mkMult__DOT__carry___05Fh10537 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11048) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh11049));
    vlTOPp->mkMult__DOT__y___05Fh11064 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh10537) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 0xaU));
    vlTOPp->mkMult__DOT__y___05Fh11066 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 9U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh10537));
    vlTOPp->mkMult__DOT__x___05Fh11063 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11065) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh11066));
    vlTOPp->mkMult__DOT__carry___05Fh10540 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11063) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh11064));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh6140 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh10667) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh10540)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh10793) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh10537)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh10876) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh10534)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh10959) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh6102)))));
    vlTOPp->mkMult__DOT__y___05Fh11079 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh10540) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 0xbU));
    vlTOPp->mkMult__DOT__y___05Fh11081 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 0xaU) 
                                          & (IData)(vlTOPp->mkMult__DOT__carry___05Fh10540));
    vlTOPp->mkMult__DOT__x___05Fh11078 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11080) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh11081));
    vlTOPp->mkMult__DOT__carry___05Fh6104 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11078) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh11079));
    vlTOPp->mkMult__DOT__y___05Fh11721 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh6104) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh11723 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 0xbU) 
                                          & (IData)(vlTOPp->mkMult__DOT__carry___05Fh6104));
    vlTOPp->mkMult__DOT__x___05Fh11720 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11722) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh11723));
    vlTOPp->mkMult__DOT__carry___05Fh11221 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11720) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh11721));
    vlTOPp->mkMult__DOT__y___05Fh11736 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh11221) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh11738 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 0xcU) 
                                          & (IData)(vlTOPp->mkMult__DOT__carry___05Fh11221));
    vlTOPp->mkMult__DOT__x___05Fh11735 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11737) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh11738));
    vlTOPp->mkMult__DOT__carry___05Fh11224 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11735) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh11736));
    vlTOPp->mkMult__DOT__y___05Fh11751 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh11224) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh11753 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 0xdU) 
                                          & (IData)(vlTOPp->mkMult__DOT__carry___05Fh11224));
    vlTOPp->mkMult__DOT__x___05Fh11750 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11752) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh11753));
    vlTOPp->mkMult__DOT__carry___05Fh11227 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh11750) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh11751));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh6110 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh11354) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh11227)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh11480) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh11224)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh11563) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh11221)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh11646) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh6104)))));
    vlTOPp->mkMult__DOT__product___05Fh6093 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh6110) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh6140) 
                                                   << 8U) 
                                                  | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh6170) 
                                                      << 4U) 
                                                     | (IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh6200))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149 
        = ((2U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh6093)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9));
    vlTOPp->mkMult__DOT__x___05Fh11954 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 2U) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh12493 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 7U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh12619 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 6U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh12702 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 5U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh12785 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 4U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh13181 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xbU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh13307 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xaU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh13390 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 9U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh13473 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 8U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh13868 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xdU)));
    vlTOPp->mkMult__DOT__x___05Fh13994 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xcU)));
    vlTOPp->mkMult__DOT__x___05Fh14077 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xbU)));
    vlTOPp->mkMult__DOT__x___05Fh14160 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xaU)));
    vlTOPp->mkMult__DOT__x___05Fh6025 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                >> 3U) 
                                               ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                  >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh14266 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xcU)));
    vlTOPp->mkMult__DOT__x___05Fh14251 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xbU)));
    vlTOPp->mkMult__DOT__x___05Fh14236 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xaU)));
    vlTOPp->mkMult__DOT__x___05Fh13594 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xbU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh13579 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 0xaU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh13564 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 9U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh13549 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 8U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh12906 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 7U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh12891 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 6U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh12876 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 5U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh12861 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 4U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh12221 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                 >> 3U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh5898 = (1U & (
                                                   ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                                    >> 2U) 
                                                   & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh5813 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh6025) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh5898)) 
          << 3U) | (((IData)(vlTOPp->mkMult__DOT__x___05Fh11954) 
                     << 2U) | (3U & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149))));
    vlTOPp->mkMult__DOT__y___05Fh12220 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh5898) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 3U));
    vlTOPp->mkMult__DOT__y___05Fh12222 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh5898));
    vlTOPp->mkMult__DOT__x___05Fh12219 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh12221) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh12222));
    vlTOPp->mkMult__DOT__carry___05Fh5713 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh12219) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh12220));
    vlTOPp->mkMult__DOT__y___05Fh12860 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh5713) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 4U));
    vlTOPp->mkMult__DOT__y___05Fh12862 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh5713));
    vlTOPp->mkMult__DOT__x___05Fh12859 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh12861) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh12862));
    vlTOPp->mkMult__DOT__carry___05Fh12360 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh12859) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh12860));
    vlTOPp->mkMult__DOT__y___05Fh12875 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh12360) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 5U));
    vlTOPp->mkMult__DOT__y___05Fh12877 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh12360));
    vlTOPp->mkMult__DOT__x___05Fh12874 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh12876) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh12877));
    vlTOPp->mkMult__DOT__carry___05Fh12363 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh12874) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh12875));
    vlTOPp->mkMult__DOT__y___05Fh12890 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh12363) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 6U));
    vlTOPp->mkMult__DOT__y___05Fh12892 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 4U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh12363));
    vlTOPp->mkMult__DOT__x___05Fh12889 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh12891) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh12892));
    vlTOPp->mkMult__DOT__carry___05Fh12366 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh12889) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh12890));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh5783 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh12493) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh12366)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh12619) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh12363)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh12702) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh12360)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh12785) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh5713)))));
    vlTOPp->mkMult__DOT__y___05Fh12905 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh12366) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 7U));
    vlTOPp->mkMult__DOT__y___05Fh12907 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 5U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh12366));
    vlTOPp->mkMult__DOT__x___05Fh12904 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh12906) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh12907));
    vlTOPp->mkMult__DOT__carry___05Fh5715 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh12904) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh12905));
    vlTOPp->mkMult__DOT__y___05Fh13548 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh5715) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 8U));
    vlTOPp->mkMult__DOT__y___05Fh13550 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 6U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh5715));
    vlTOPp->mkMult__DOT__x___05Fh13547 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh13549) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh13550));
    vlTOPp->mkMult__DOT__carry___05Fh13048 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh13547) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh13548));
    vlTOPp->mkMult__DOT__y___05Fh13563 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh13048) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 9U));
    vlTOPp->mkMult__DOT__y___05Fh13565 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 7U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh13048));
    vlTOPp->mkMult__DOT__x___05Fh13562 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh13564) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh13565));
    vlTOPp->mkMult__DOT__carry___05Fh13051 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh13562) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh13563));
    vlTOPp->mkMult__DOT__y___05Fh13578 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh13051) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 0xaU));
    vlTOPp->mkMult__DOT__y___05Fh13580 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 8U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh13051));
    vlTOPp->mkMult__DOT__x___05Fh13577 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh13579) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh13580));
    vlTOPp->mkMult__DOT__carry___05Fh13054 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh13577) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh13578));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh5753 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh13181) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh13054)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh13307) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh13051)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh13390) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh13048)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh13473) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh5715)))));
    vlTOPp->mkMult__DOT__y___05Fh13593 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh13054) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 0xbU));
    vlTOPp->mkMult__DOT__y___05Fh13595 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 9U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh13054));
    vlTOPp->mkMult__DOT__x___05Fh13592 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh13594) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh13595));
    vlTOPp->mkMult__DOT__carry___05Fh5717 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh13592) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh13593));
    vlTOPp->mkMult__DOT__y___05Fh14235 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh5717) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh14237 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 0xaU) 
                                          & (IData)(vlTOPp->mkMult__DOT__carry___05Fh5717));
    vlTOPp->mkMult__DOT__x___05Fh14234 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh14236) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh14237));
    vlTOPp->mkMult__DOT__carry___05Fh13735 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh14234) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh14235));
    vlTOPp->mkMult__DOT__y___05Fh14250 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh13735) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh14252 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 0xbU) 
                                          & (IData)(vlTOPp->mkMult__DOT__carry___05Fh13735));
    vlTOPp->mkMult__DOT__x___05Fh14249 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh14251) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh14252));
    vlTOPp->mkMult__DOT__carry___05Fh13738 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh14249) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh14250));
    vlTOPp->mkMult__DOT__y___05Fh14265 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh13738) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh14267 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 0xcU) 
                                          & (IData)(vlTOPp->mkMult__DOT__carry___05Fh13738));
    vlTOPp->mkMult__DOT__x___05Fh14264 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh14266) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh14267));
    vlTOPp->mkMult__DOT__carry___05Fh13741 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh14264) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh14265));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh5723 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh13868) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh13741)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh13994) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh13738)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh14077) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh13735)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh14160) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh5717)))));
    vlTOPp->mkMult__DOT__product___05Fh5706 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh5723) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh5753) 
                                                   << 8U) 
                                                  | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh5783) 
                                                      << 4U) 
                                                     | (IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh5813))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265 
        = ((4U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh5706)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149));
    vlTOPp->mkMult__DOT__x___05Fh15007 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 7U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh15133 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 6U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh15216 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 5U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh15299 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 4U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh15695 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xbU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh15821 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xaU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh15904 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 9U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh15987 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 8U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh16382 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xcU)));
    vlTOPp->mkMult__DOT__x___05Fh16508 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xbU)));
    vlTOPp->mkMult__DOT__x___05Fh16591 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xaU)));
    vlTOPp->mkMult__DOT__x___05Fh16674 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh5638 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                >> 3U) 
                                               ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh16780 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xbU)));
    vlTOPp->mkMult__DOT__x___05Fh16765 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xaU)));
    vlTOPp->mkMult__DOT__x___05Fh16750 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh16108 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xbU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh16093 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 0xaU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh16078 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 9U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh16063 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 8U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh15420 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 7U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh15405 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 6U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh15390 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 5U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh15375 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                 >> 4U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh5326 = (1U & (
                                                   ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                                    >> 3U) 
                                                   & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh5426 = 
        (((IData)(vlTOPp->mkMult__DOT__x___05Fh5638) 
          << 3U) | (7U & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265)));
    vlTOPp->mkMult__DOT__y___05Fh15374 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh5326) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 4U));
    vlTOPp->mkMult__DOT__y___05Fh15376 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh5326));
    vlTOPp->mkMult__DOT__x___05Fh15373 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh15375) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh15376));
    vlTOPp->mkMult__DOT__carry___05Fh14874 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh15373) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh15374));
    vlTOPp->mkMult__DOT__y___05Fh15389 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh14874) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 5U));
    vlTOPp->mkMult__DOT__y___05Fh15391 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh14874));
    vlTOPp->mkMult__DOT__x___05Fh15388 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh15390) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh15391));
    vlTOPp->mkMult__DOT__carry___05Fh14877 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh15388) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh15389));
    vlTOPp->mkMult__DOT__y___05Fh15404 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh14877) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 6U));
    vlTOPp->mkMult__DOT__y___05Fh15406 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh14877));
    vlTOPp->mkMult__DOT__x___05Fh15403 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh15405) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh15406));
    vlTOPp->mkMult__DOT__carry___05Fh14880 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh15403) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh15404));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh5396 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh15007) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh14880)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh15133) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh14877)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh15216) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh14874)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh15299) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh5326)))));
    vlTOPp->mkMult__DOT__y___05Fh15419 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh14880) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 7U));
    vlTOPp->mkMult__DOT__y___05Fh15421 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 4U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh14880));
    vlTOPp->mkMult__DOT__x___05Fh15418 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh15420) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh15421));
    vlTOPp->mkMult__DOT__carry___05Fh5328 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh15418) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh15419));
    vlTOPp->mkMult__DOT__y___05Fh16062 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh5328) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 8U));
    vlTOPp->mkMult__DOT__y___05Fh16064 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 5U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh5328));
    vlTOPp->mkMult__DOT__x___05Fh16061 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16063) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh16064));
    vlTOPp->mkMult__DOT__carry___05Fh15562 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16061) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh16062));
    vlTOPp->mkMult__DOT__y___05Fh16077 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh15562) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 9U));
    vlTOPp->mkMult__DOT__y___05Fh16079 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 6U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh15562));
    vlTOPp->mkMult__DOT__x___05Fh16076 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16078) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh16079));
    vlTOPp->mkMult__DOT__carry___05Fh15565 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16076) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh16077));
    vlTOPp->mkMult__DOT__y___05Fh16092 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh15565) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 0xaU));
    vlTOPp->mkMult__DOT__y___05Fh16094 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 7U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh15565));
    vlTOPp->mkMult__DOT__x___05Fh16091 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16093) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh16094));
    vlTOPp->mkMult__DOT__carry___05Fh15568 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16091) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh16092));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh5366 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh15695) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh15568)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh15821) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh15565)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh15904) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh15562)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh15987) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh5328)))));
    vlTOPp->mkMult__DOT__y___05Fh16107 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh15568) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 0xbU));
    vlTOPp->mkMult__DOT__y___05Fh16109 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 8U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh15568));
    vlTOPp->mkMult__DOT__x___05Fh16106 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16108) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh16109));
    vlTOPp->mkMult__DOT__carry___05Fh5330 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16106) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh16107));
    vlTOPp->mkMult__DOT__y___05Fh16749 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh5330) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh16751 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 9U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh5330));
    vlTOPp->mkMult__DOT__x___05Fh16748 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16750) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh16751));
    vlTOPp->mkMult__DOT__carry___05Fh16249 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16748) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh16749));
    vlTOPp->mkMult__DOT__y___05Fh16764 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh16249) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh16766 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 0xaU) 
                                          & (IData)(vlTOPp->mkMult__DOT__carry___05Fh16249));
    vlTOPp->mkMult__DOT__x___05Fh16763 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16765) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh16766));
    vlTOPp->mkMult__DOT__carry___05Fh16252 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16763) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh16764));
    vlTOPp->mkMult__DOT__y___05Fh16779 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh16252) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh16781 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 0xbU) 
                                          & (IData)(vlTOPp->mkMult__DOT__carry___05Fh16252));
    vlTOPp->mkMult__DOT__x___05Fh16778 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16780) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh16781));
    vlTOPp->mkMult__DOT__carry___05Fh16255 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh16778) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh16779));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh5336 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh16382) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh16255)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh16508) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh16252)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh16591) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh16249)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh16674) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh5330)))));
    vlTOPp->mkMult__DOT__product___05Fh5319 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh5336) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh5366) 
                                                   << 8U) 
                                                  | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh5396) 
                                                      << 4U) 
                                                     | (IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh5426))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373 
        = ((8U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh5319)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265));
    vlTOPp->mkMult__DOT__x___05Fh17521 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 7U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh17647 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 6U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh17730 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 5U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh17813 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 4U) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh18209 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xbU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh18335 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xaU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh18418 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 9U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh18501 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 8U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh18896 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xbU)));
    vlTOPp->mkMult__DOT__x___05Fh19022 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xaU)));
    vlTOPp->mkMult__DOT__x___05Fh19105 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh19188 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh19294 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xaU)));
    vlTOPp->mkMult__DOT__x___05Fh19279 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh19264 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh18622 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xbU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh18607 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 0xaU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh18592 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 9U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh18577 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 8U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh17934 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 7U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh17919 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 6U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh17904 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                 >> 5U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh17388 = (1U & 
                                              (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                                >> 4U) 
                                               & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__y___05Fh17903 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh17388) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                             >> 5U));
    vlTOPp->mkMult__DOT__y___05Fh17905 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh17388));
    vlTOPp->mkMult__DOT__x___05Fh17902 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh17904) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh17905));
    vlTOPp->mkMult__DOT__carry___05Fh17391 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh17902) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh17903));
    vlTOPp->mkMult__DOT__y___05Fh17918 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh17391) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                             >> 6U));
    vlTOPp->mkMult__DOT__y___05Fh17920 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh17391));
    vlTOPp->mkMult__DOT__x___05Fh17917 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh17919) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh17920));
    vlTOPp->mkMult__DOT__carry___05Fh17394 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh17917) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh17918));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh5009 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh17521) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh17394)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh17647) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh17391)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh17730) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh17388)) 
                                << 1U) | (IData)(vlTOPp->mkMult__DOT__x___05Fh17813))));
    vlTOPp->mkMult__DOT__y___05Fh17933 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh17394) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                             >> 7U));
    vlTOPp->mkMult__DOT__y___05Fh17935 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh17394));
    vlTOPp->mkMult__DOT__x___05Fh17932 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh17934) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh17935));
    vlTOPp->mkMult__DOT__carry___05Fh4941 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh17932) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh17933));
    vlTOPp->mkMult__DOT__y___05Fh18576 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh4941) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                             >> 8U));
    vlTOPp->mkMult__DOT__y___05Fh18578 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 4U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh4941));
    vlTOPp->mkMult__DOT__x___05Fh18575 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh18577) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh18578));
    vlTOPp->mkMult__DOT__carry___05Fh18076 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh18575) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh18576));
    vlTOPp->mkMult__DOT__y___05Fh18591 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh18076) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                             >> 9U));
    vlTOPp->mkMult__DOT__y___05Fh18593 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 5U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh18076));
    vlTOPp->mkMult__DOT__x___05Fh18590 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh18592) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh18593));
    vlTOPp->mkMult__DOT__carry___05Fh18079 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh18590) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh18591));
    vlTOPp->mkMult__DOT__y___05Fh18606 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh18079) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                             >> 0xaU));
    vlTOPp->mkMult__DOT__y___05Fh18608 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 6U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh18079));
    vlTOPp->mkMult__DOT__x___05Fh18605 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh18607) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh18608));
    vlTOPp->mkMult__DOT__carry___05Fh18082 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh18605) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh18606));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh4979 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh18209) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh18082)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh18335) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh18079)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh18418) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh18076)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh18501) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh4941)))));
    vlTOPp->mkMult__DOT__y___05Fh18621 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh18082) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                             >> 0xbU));
    vlTOPp->mkMult__DOT__y___05Fh18623 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 7U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh18082));
    vlTOPp->mkMult__DOT__x___05Fh18620 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh18622) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh18623));
    vlTOPp->mkMult__DOT__carry___05Fh4943 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh18620) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh18621));
    vlTOPp->mkMult__DOT__y___05Fh19263 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh4943) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh19265 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 8U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh4943));
    vlTOPp->mkMult__DOT__x___05Fh19262 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh19264) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh19265));
    vlTOPp->mkMult__DOT__carry___05Fh18763 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh19262) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh19263));
    vlTOPp->mkMult__DOT__y___05Fh19278 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh18763) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh19280 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 9U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh18763));
    vlTOPp->mkMult__DOT__x___05Fh19277 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh19279) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh19280));
    vlTOPp->mkMult__DOT__carry___05Fh18766 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh19277) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh19278));
    vlTOPp->mkMult__DOT__y___05Fh19293 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh18766) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh19295 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 0xaU) 
                                          & (IData)(vlTOPp->mkMult__DOT__carry___05Fh18766));
    vlTOPp->mkMult__DOT__x___05Fh19292 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh19294) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh19295));
    vlTOPp->mkMult__DOT__carry___05Fh18769 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh19292) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh19293));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh4949 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh18896) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh18769)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh19022) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh18766)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh19105) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh18763)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh19188) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh4943)))));
    vlTOPp->mkMult__DOT__product___05Fh4932 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh4949) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh4979) 
                                                   << 8U) 
                                                  | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh5009) 
                                                      << 4U) 
                                                     | (0xfU 
                                                        & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373)))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472 
        = ((0x10U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh4932)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373));
    vlTOPp->mkMult__DOT__x___05Fh20035 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 7U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh20161 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 6U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh20244 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 5U) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh20723 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xbU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh20849 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xaU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh20932 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 9U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh21015 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 8U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh21410 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 0xaU)));
    vlTOPp->mkMult__DOT__x___05Fh21536 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh21619 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh21702 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh21808 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh21793 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh21778 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh21136 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xbU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh21121 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 0xaU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh21106 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 9U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh21091 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 8U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh20448 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 7U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh20433 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                 >> 6U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh19905 = (1U & 
                                              (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                >> 5U) 
                                               & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__y___05Fh20432 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh19905) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                             >> 6U));
    vlTOPp->mkMult__DOT__y___05Fh20434 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh19905));
    vlTOPp->mkMult__DOT__x___05Fh20431 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh20433) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh20434));
    vlTOPp->mkMult__DOT__carry___05Fh19908 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh20431) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh20432));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh4622 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh20035) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh19908)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh20161) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh19905)) 
                     << 2U) | (((IData)(vlTOPp->mkMult__DOT__x___05Fh20244) 
                                << 1U) | (1U & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                                >> 4U)))));
    vlTOPp->mkMult__DOT__y___05Fh20447 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh19908) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                             >> 7U));
    vlTOPp->mkMult__DOT__y___05Fh20449 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh19908));
    vlTOPp->mkMult__DOT__x___05Fh20446 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh20448) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh20449));
    vlTOPp->mkMult__DOT__carry___05Fh4554 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh20446) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh20447));
    vlTOPp->mkMult__DOT__y___05Fh21090 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh4554) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                             >> 8U));
    vlTOPp->mkMult__DOT__y___05Fh21092 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh4554));
    vlTOPp->mkMult__DOT__x___05Fh21089 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21091) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh21092));
    vlTOPp->mkMult__DOT__carry___05Fh20590 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21089) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh21090));
    vlTOPp->mkMult__DOT__y___05Fh21105 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh20590) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                             >> 9U));
    vlTOPp->mkMult__DOT__y___05Fh21107 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 4U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh20590));
    vlTOPp->mkMult__DOT__x___05Fh21104 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21106) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh21107));
    vlTOPp->mkMult__DOT__carry___05Fh20593 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21104) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh21105));
    vlTOPp->mkMult__DOT__y___05Fh21120 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh20593) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                             >> 0xaU));
    vlTOPp->mkMult__DOT__y___05Fh21122 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 5U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh20593));
    vlTOPp->mkMult__DOT__x___05Fh21119 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21121) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh21122));
    vlTOPp->mkMult__DOT__carry___05Fh20596 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21119) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh21120));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh4592 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh20723) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh20596)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh20849) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh20593)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh20932) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh20590)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh21015) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh4554)))));
    vlTOPp->mkMult__DOT__y___05Fh21135 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh20596) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                             >> 0xbU));
    vlTOPp->mkMult__DOT__y___05Fh21137 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 6U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh20596));
    vlTOPp->mkMult__DOT__x___05Fh21134 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21136) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh21137));
    vlTOPp->mkMult__DOT__carry___05Fh4556 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21134) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh21135));
    vlTOPp->mkMult__DOT__y___05Fh21777 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh4556) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh21779 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 7U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh4556));
    vlTOPp->mkMult__DOT__x___05Fh21776 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21778) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh21779));
    vlTOPp->mkMult__DOT__carry___05Fh21277 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21776) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh21777));
    vlTOPp->mkMult__DOT__y___05Fh21792 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh21277) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh21794 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 8U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh21277));
    vlTOPp->mkMult__DOT__x___05Fh21791 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21793) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh21794));
    vlTOPp->mkMult__DOT__carry___05Fh21280 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21791) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh21792));
    vlTOPp->mkMult__DOT__y___05Fh21807 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh21280) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh21809 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 9U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh21280));
    vlTOPp->mkMult__DOT__x___05Fh21806 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21808) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh21809));
    vlTOPp->mkMult__DOT__carry___05Fh21283 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh21806) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh21807));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh4562 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh21410) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh21283)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh21536) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh21280)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh21619) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh21277)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh21702) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh4556)))));
    vlTOPp->mkMult__DOT__product___05Fh4545 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh4562) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh4592) 
                                                   << 8U) 
                                                  | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh4622) 
                                                      << 4U) 
                                                     | (0xfU 
                                                        & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472)))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564 
        = ((0x20U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh4545)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472));
    vlTOPp->mkMult__DOT__x___05Fh22549 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 7U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh22675 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 6U) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh23237 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xbU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh23363 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xaU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh23446 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 9U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh23529 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 8U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh23924 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 9U)));
    vlTOPp->mkMult__DOT__x___05Fh24050 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh24133 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh24216 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh24322 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh24307 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh24292 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh23650 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xbU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh23635 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 0xaU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh23620 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 9U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh23605 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 8U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh22962 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                 >> 7U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh22422 = (1U & 
                                              (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                                >> 6U) 
                                               & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh4235 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh22549) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh22422)) 
          << 3U) | (((IData)(vlTOPp->mkMult__DOT__x___05Fh22675) 
                     << 2U) | (3U & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                     >> 4U))));
    vlTOPp->mkMult__DOT__y___05Fh22961 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh22422) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                             >> 7U));
    vlTOPp->mkMult__DOT__y___05Fh22963 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh22422));
    vlTOPp->mkMult__DOT__x___05Fh22960 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh22962) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh22963));
    vlTOPp->mkMult__DOT__carry___05Fh4167 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh22960) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh22961));
    vlTOPp->mkMult__DOT__y___05Fh23604 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh4167) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                             >> 8U));
    vlTOPp->mkMult__DOT__y___05Fh23606 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh4167));
    vlTOPp->mkMult__DOT__x___05Fh23603 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh23605) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh23606));
    vlTOPp->mkMult__DOT__carry___05Fh23104 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh23603) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh23604));
    vlTOPp->mkMult__DOT__y___05Fh23619 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh23104) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                             >> 9U));
    vlTOPp->mkMult__DOT__y___05Fh23621 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh23104));
    vlTOPp->mkMult__DOT__x___05Fh23618 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh23620) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh23621));
    vlTOPp->mkMult__DOT__carry___05Fh23107 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh23618) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh23619));
    vlTOPp->mkMult__DOT__y___05Fh23634 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh23107) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                             >> 0xaU));
    vlTOPp->mkMult__DOT__y___05Fh23636 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 4U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh23107));
    vlTOPp->mkMult__DOT__x___05Fh23633 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh23635) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh23636));
    vlTOPp->mkMult__DOT__carry___05Fh23110 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh23633) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh23634));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh4205 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh23237) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh23110)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh23363) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh23107)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh23446) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh23104)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh23529) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh4167)))));
    vlTOPp->mkMult__DOT__y___05Fh23649 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh23110) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                             >> 0xbU));
    vlTOPp->mkMult__DOT__y___05Fh23651 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 5U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh23110));
    vlTOPp->mkMult__DOT__x___05Fh23648 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh23650) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh23651));
    vlTOPp->mkMult__DOT__carry___05Fh4169 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh23648) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh23649));
    vlTOPp->mkMult__DOT__y___05Fh24291 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh4169) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh24293 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 6U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh4169));
    vlTOPp->mkMult__DOT__x___05Fh24290 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh24292) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh24293));
    vlTOPp->mkMult__DOT__carry___05Fh23791 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh24290) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh24291));
    vlTOPp->mkMult__DOT__y___05Fh24306 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh23791) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh24308 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 7U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh23791));
    vlTOPp->mkMult__DOT__x___05Fh24305 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh24307) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh24308));
    vlTOPp->mkMult__DOT__carry___05Fh23794 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh24305) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh24306));
    vlTOPp->mkMult__DOT__y___05Fh24321 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh23794) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh24323 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 8U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh23794));
    vlTOPp->mkMult__DOT__x___05Fh24320 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh24322) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh24323));
    vlTOPp->mkMult__DOT__carry___05Fh23797 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh24320) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh24321));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh4175 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh23924) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh23797)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh24050) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh23794)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh24133) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh23791)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh24216) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh4169)))));
    vlTOPp->mkMult__DOT__product___05Fh4158 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh4175) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh4205) 
                                                   << 8U) 
                                                  | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh4235) 
                                                      << 4U) 
                                                     | (0xfU 
                                                        & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564)))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647 
        = ((0x40U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh4158)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564));
    vlTOPp->mkMult__DOT__x___05Fh25063 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 7U) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh25751 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xbU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh25877 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xaU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh25960 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 9U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh26043 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 8U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh26438 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 8U)));
    vlTOPp->mkMult__DOT__x___05Fh26564 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh26647 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh26730 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh26836 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh26821 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh26806 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh26164 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xbU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh26149 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 0xaU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh26134 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 9U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh26119 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                 >> 8U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh3780 = (1U & (
                                                   ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                                    >> 7U) 
                                                   & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__y___05Fh26118 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh3780) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                             >> 8U));
    vlTOPp->mkMult__DOT__y___05Fh26120 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh3780));
    vlTOPp->mkMult__DOT__x___05Fh26117 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26119) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh26120));
    vlTOPp->mkMult__DOT__carry___05Fh25618 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26117) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh26118));
    vlTOPp->mkMult__DOT__y___05Fh26133 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh25618) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                             >> 9U));
    vlTOPp->mkMult__DOT__y___05Fh26135 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh25618));
    vlTOPp->mkMult__DOT__x___05Fh26132 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26134) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh26135));
    vlTOPp->mkMult__DOT__carry___05Fh25621 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26132) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh26133));
    vlTOPp->mkMult__DOT__y___05Fh26148 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh25621) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                             >> 0xaU));
    vlTOPp->mkMult__DOT__y___05Fh26150 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh25621));
    vlTOPp->mkMult__DOT__x___05Fh26147 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26149) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh26150));
    vlTOPp->mkMult__DOT__carry___05Fh25624 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26147) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh26148));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh3818 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh25751) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh25624)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh25877) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh25621)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh25960) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh25618)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh26043) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh3780)))));
    vlTOPp->mkMult__DOT__y___05Fh26163 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh25624) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                             >> 0xbU));
    vlTOPp->mkMult__DOT__y___05Fh26165 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 4U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh25624));
    vlTOPp->mkMult__DOT__x___05Fh26162 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26164) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh26165));
    vlTOPp->mkMult__DOT__carry___05Fh3782 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26162) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh26163));
    vlTOPp->mkMult__DOT__y___05Fh26805 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh3782) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh26807 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 5U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh3782));
    vlTOPp->mkMult__DOT__x___05Fh26804 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26806) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh26807));
    vlTOPp->mkMult__DOT__carry___05Fh26305 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26804) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh26805));
    vlTOPp->mkMult__DOT__y___05Fh26820 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh26305) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh26822 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 6U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh26305));
    vlTOPp->mkMult__DOT__x___05Fh26819 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26821) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh26822));
    vlTOPp->mkMult__DOT__carry___05Fh26308 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26819) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh26820));
    vlTOPp->mkMult__DOT__y___05Fh26835 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh26308) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh26837 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 7U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh26308));
    vlTOPp->mkMult__DOT__x___05Fh26834 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26836) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh26837));
    vlTOPp->mkMult__DOT__carry___05Fh26311 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh26834) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh26835));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh3788 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh26438) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh26311)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh26564) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh26308)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh26647) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh26305)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh26730) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh3782)))));
    vlTOPp->mkMult__DOT__product___05Fh3771 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh3788) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh3818) 
                                                   << 8U) 
                                                  | (((IData)(vlTOPp->mkMult__DOT__x___05Fh25063) 
                                                      << 7U) 
                                                     | (0x7fU 
                                                        & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647)))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720 
        = ((0x80U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh3771)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647));
    vlTOPp->mkMult__DOT__x___05Fh28265 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xbU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh28391 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xaU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh28474 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 9U) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh28557 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 8U) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh28952 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 7U)));
    vlTOPp->mkMult__DOT__x___05Fh29078 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh29161 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh29244 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh29350 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh29335 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh29320 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh28678 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xbU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh28663 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 0xaU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh28648 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                 >> 9U) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh28132 = (1U & 
                                              (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                                >> 8U) 
                                               & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__y___05Fh28647 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh28132) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                             >> 9U));
    vlTOPp->mkMult__DOT__y___05Fh28649 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh28132));
    vlTOPp->mkMult__DOT__x___05Fh28646 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh28648) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh28649));
    vlTOPp->mkMult__DOT__carry___05Fh28135 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh28646) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh28647));
    vlTOPp->mkMult__DOT__y___05Fh28662 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh28135) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                             >> 0xaU));
    vlTOPp->mkMult__DOT__y___05Fh28664 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh28135));
    vlTOPp->mkMult__DOT__x___05Fh28661 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh28663) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh28664));
    vlTOPp->mkMult__DOT__carry___05Fh28138 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh28661) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh28662));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh3431 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh28265) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh28138)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh28391) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh28135)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh28474) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh28132)) 
                                << 1U) | (IData)(vlTOPp->mkMult__DOT__x___05Fh28557))));
    vlTOPp->mkMult__DOT__y___05Fh28677 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh28138) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                             >> 0xbU));
    vlTOPp->mkMult__DOT__y___05Fh28679 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh28138));
    vlTOPp->mkMult__DOT__x___05Fh28676 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh28678) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh28679));
    vlTOPp->mkMult__DOT__carry___05Fh3395 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh28676) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh28677));
    vlTOPp->mkMult__DOT__y___05Fh29319 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh3395) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh29321 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 4U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh3395));
    vlTOPp->mkMult__DOT__x___05Fh29318 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh29320) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh29321));
    vlTOPp->mkMult__DOT__carry___05Fh28819 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh29318) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh29319));
    vlTOPp->mkMult__DOT__y___05Fh29334 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh28819) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh29336 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 5U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh28819));
    vlTOPp->mkMult__DOT__x___05Fh29333 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh29335) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh29336));
    vlTOPp->mkMult__DOT__carry___05Fh28822 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh29333) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh29334));
    vlTOPp->mkMult__DOT__y___05Fh29349 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh28822) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh29351 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 6U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh28822));
    vlTOPp->mkMult__DOT__x___05Fh29348 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh29350) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh29351));
    vlTOPp->mkMult__DOT__carry___05Fh28825 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh29348) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh29349));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh3401 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh28952) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh28825)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh29078) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh28822)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh29161) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh28819)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh29244) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh3395)))));
    vlTOPp->mkMult__DOT__product___05Fh3384 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh3401) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh3431) 
                                                   << 8U) 
                                                  | (0xffU 
                                                     & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784 
        = ((0x100U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh3384)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720));
    vlTOPp->mkMult__DOT__x___05Fh30779 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xbU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh30905 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xaU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh30988 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 9U) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh31466 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 6U)));
    vlTOPp->mkMult__DOT__x___05Fh31592 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh31675 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh31758 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh31864 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh31849 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh31834 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh31192 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xbU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh31177 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                 >> 0xaU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh30649 = (1U & 
                                              (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                >> 9U) 
                                               & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__y___05Fh31176 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh30649) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                             >> 0xaU));
    vlTOPp->mkMult__DOT__y___05Fh31178 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh30649));
    vlTOPp->mkMult__DOT__x___05Fh31175 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh31177) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh31178));
    vlTOPp->mkMult__DOT__carry___05Fh30652 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh31175) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh31176));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh3044 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh30779) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh30652)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh30905) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh30649)) 
                     << 2U) | (((IData)(vlTOPp->mkMult__DOT__x___05Fh30988) 
                                << 1U) | (1U & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                                >> 8U)))));
    vlTOPp->mkMult__DOT__y___05Fh31191 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh30652) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                             >> 0xbU));
    vlTOPp->mkMult__DOT__y___05Fh31193 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh30652));
    vlTOPp->mkMult__DOT__x___05Fh31190 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh31192) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh31193));
    vlTOPp->mkMult__DOT__carry___05Fh3008 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh31190) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh31191));
    vlTOPp->mkMult__DOT__y___05Fh31833 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh3008) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh31835 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh3008));
    vlTOPp->mkMult__DOT__x___05Fh31832 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh31834) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh31835));
    vlTOPp->mkMult__DOT__carry___05Fh31333 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh31832) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh31833));
    vlTOPp->mkMult__DOT__y___05Fh31848 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh31333) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh31850 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 4U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh31333));
    vlTOPp->mkMult__DOT__x___05Fh31847 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh31849) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh31850));
    vlTOPp->mkMult__DOT__carry___05Fh31336 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh31847) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh31848));
    vlTOPp->mkMult__DOT__y___05Fh31863 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh31336) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh31865 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 5U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh31336));
    vlTOPp->mkMult__DOT__x___05Fh31862 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh31864) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh31865));
    vlTOPp->mkMult__DOT__carry___05Fh31339 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh31862) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh31863));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh3014 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh31466) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh31339)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh31592) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh31336)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh31675) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh31333)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh31758) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh3008)))));
    vlTOPp->mkMult__DOT__product___05Fh2997 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh3014) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh3044) 
                                                   << 8U) 
                                                  | (0xffU 
                                                     & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841 
        = ((0x200U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh2997)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784));
    vlTOPp->mkMult__DOT__x___05Fh33293 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                 >> 0xbU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh33419 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                 >> 0xaU) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh33980 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 5U)));
    vlTOPp->mkMult__DOT__x___05Fh34106 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh34189 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh34272 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh34378 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh34363 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh34348 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh33706 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                 >> 0xbU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh33166 = (1U & 
                                              (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                                >> 0xaU) 
                                               & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh2657 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh33293) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh33166)) 
          << 3U) | (((IData)(vlTOPp->mkMult__DOT__x___05Fh33419) 
                     << 2U) | (3U & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                     >> 8U))));
    vlTOPp->mkMult__DOT__y___05Fh33705 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh33166) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                             >> 0xbU));
    vlTOPp->mkMult__DOT__y___05Fh33707 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh33166));
    vlTOPp->mkMult__DOT__x___05Fh33704 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh33706) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh33707));
    vlTOPp->mkMult__DOT__carry___05Fh2621 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh33704) 
                                             | (IData)(vlTOPp->mkMult__DOT__y___05Fh33705));
    vlTOPp->mkMult__DOT__y___05Fh34347 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh2621) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh34349 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh2621));
    vlTOPp->mkMult__DOT__x___05Fh34346 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh34348) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh34349));
    vlTOPp->mkMult__DOT__carry___05Fh33847 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh34346) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh34347));
    vlTOPp->mkMult__DOT__y___05Fh34362 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh33847) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh34364 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh33847));
    vlTOPp->mkMult__DOT__x___05Fh34361 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh34363) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh34364));
    vlTOPp->mkMult__DOT__carry___05Fh33850 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh34361) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh34362));
    vlTOPp->mkMult__DOT__y___05Fh34377 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh33850) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh34379 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 4U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh33850));
    vlTOPp->mkMult__DOT__x___05Fh34376 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh34378) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh34379));
    vlTOPp->mkMult__DOT__carry___05Fh33853 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh34376) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh34377));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh2627 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh33980) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh33853)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh34106) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh33850)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh34189) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh33847)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh34272) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh2621)))));
    vlTOPp->mkMult__DOT__product___05Fh2610 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh2627) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh2657) 
                                                   << 8U) 
                                                  | (0xffU 
                                                     & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889 
        = ((0x400U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh2610)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841));
    vlTOPp->mkMult__DOT__x___05Fh35807 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                                 >> 0xbU) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh36494 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 4U)));
    vlTOPp->mkMult__DOT__x___05Fh36620 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh36703 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh36786 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                                 >> 0xcU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh36892 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh36877 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh36862 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                                 >> 0xcU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh2234 = (1U & (
                                                   ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                                    >> 0xbU) 
                                                   & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__y___05Fh36861 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh2234) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                             >> 0xcU));
    vlTOPp->mkMult__DOT__y___05Fh36863 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh2234));
    vlTOPp->mkMult__DOT__x___05Fh36860 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh36862) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh36863));
    vlTOPp->mkMult__DOT__carry___05Fh36361 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh36860) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh36861));
    vlTOPp->mkMult__DOT__y___05Fh36876 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh36361) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh36878 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh36361));
    vlTOPp->mkMult__DOT__x___05Fh36875 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh36877) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh36878));
    vlTOPp->mkMult__DOT__carry___05Fh36364 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh36875) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh36876));
    vlTOPp->mkMult__DOT__y___05Fh36891 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh36364) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh36893 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 3U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh36364));
    vlTOPp->mkMult__DOT__x___05Fh36890 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh36892) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh36893));
    vlTOPp->mkMult__DOT__carry___05Fh36367 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh36890) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh36891));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh2240 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh36494) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh36367)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh36620) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh36364)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh36703) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh36361)) 
                                << 1U) | ((IData)(vlTOPp->mkMult__DOT__x___05Fh36786) 
                                          ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh2234)))));
    vlTOPp->mkMult__DOT__product___05Fh2223 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh2240) 
                                                << 0xcU) 
                                               | (((IData)(vlTOPp->mkMult__DOT__x___05Fh35807) 
                                                   << 0xbU) 
                                                  | (0x7ffU 
                                                     & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889))));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927 
        = ((0x800U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh2223)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889));
    vlTOPp->mkMult__DOT__x___05Fh39008 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 3U)));
    vlTOPp->mkMult__DOT__x___05Fh39134 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh39217 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927) 
                                                 >> 0xdU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh39300 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927) 
                                                 >> 0xcU) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh39406 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh39391 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927) 
                                                 >> 0xdU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh38875 = (1U & 
                                              (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927) 
                                                >> 0xcU) 
                                               & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__y___05Fh39390 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh38875) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927) 
                                             >> 0xdU));
    vlTOPp->mkMult__DOT__y___05Fh39392 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh38875));
    vlTOPp->mkMult__DOT__x___05Fh39389 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh39391) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh39392));
    vlTOPp->mkMult__DOT__carry___05Fh38878 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh39389) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh39390));
    vlTOPp->mkMult__DOT__y___05Fh39405 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh38878) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh39407 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 2U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh38878));
    vlTOPp->mkMult__DOT__x___05Fh39404 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh39406) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh39407));
    vlTOPp->mkMult__DOT__carry___05Fh38881 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh39404) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh39405));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh1853 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh39008) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh38881)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh39134) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh38878)) 
                     << 2U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh39217) 
                                 ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh38875)) 
                                << 1U) | (IData)(vlTOPp->mkMult__DOT__x___05Fh39300))));
    vlTOPp->mkMult__DOT__product___05Fh1836 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh1853) 
                                                << 0xcU) 
                                               | (0xfffU 
                                                  & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927)));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957 
        = ((0x1000U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh1836)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927));
    vlTOPp->mkMult__DOT__x___05Fh41522 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 2U)));
    vlTOPp->mkMult__DOT__x___05Fh41648 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957) 
                                                 >> 0xeU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh41731 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957) 
                                                 >> 0xdU) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh41920 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957) 
                                                 >> 0xeU) 
                                                & ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__carry___05Fh41392 = (1U & 
                                              (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957) 
                                                >> 0xdU) 
                                               & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__y___05Fh41919 = ((IData)(vlTOPp->mkMult__DOT__carry___05Fh41392) 
                                          & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957) 
                                             >> 0xeU));
    vlTOPp->mkMult__DOT__y___05Fh41921 = (((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                           >> 1U) & (IData)(vlTOPp->mkMult__DOT__carry___05Fh41392));
    vlTOPp->mkMult__DOT__x___05Fh41918 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh41920) 
                                          | (IData)(vlTOPp->mkMult__DOT__y___05Fh41921));
    vlTOPp->mkMult__DOT__carry___05Fh41395 = ((IData)(vlTOPp->mkMult__DOT__x___05Fh41918) 
                                              | (IData)(vlTOPp->mkMult__DOT__y___05Fh41919));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh1466 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh41522) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh41395)) 
          << 3U) | ((((IData)(vlTOPp->mkMult__DOT__x___05Fh41648) 
                      ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh41392)) 
                     << 2U) | (((IData)(vlTOPp->mkMult__DOT__x___05Fh41731) 
                                << 1U) | (1U & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957) 
                                                >> 0xcU)))));
    vlTOPp->mkMult__DOT__product___05Fh1449 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh1466) 
                                                << 0xcU) 
                                               | (0xfffU 
                                                  & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957)));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_13_60_THEN_IF_inp_B_BIT_12_30_THE_ETC___05F_d980 
        = ((0x2000U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh1449)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957));
    vlTOPp->mkMult__DOT__carry___05Fh43909 = (1U & 
                                              (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_13_60_THEN_IF_inp_B_BIT_12_30_THE_ETC___05F_d980) 
                                                >> 0xeU) 
                                               & (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__x___05Fh44036 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_13_60_THEN_IF_inp_B_BIT_12_30_THE_ETC___05F_d980) 
                                                 >> 0xfU) 
                                                ^ ((IData)(vlTOPp->mkMult__DOT__inp_A) 
                                                   >> 1U)));
    vlTOPp->mkMult__DOT__x___05Fh44162 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_13_60_THEN_IF_inp_B_BIT_12_30_THE_ETC___05F_d980) 
                                                 >> 0xeU) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__spliced_bits___05Fh1079 = 
        ((((IData)(vlTOPp->mkMult__DOT__x___05Fh44036) 
           ^ (IData)(vlTOPp->mkMult__DOT__carry___05Fh43909)) 
          << 3U) | (((IData)(vlTOPp->mkMult__DOT__x___05Fh44162) 
                     << 2U) | (3U & ((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_13_60_THEN_IF_inp_B_BIT_12_30_THE_ETC___05F_d980) 
                                     >> 0xcU))));
    vlTOPp->mkMult__DOT__product___05Fh1062 = (((IData)(vlTOPp->mkMult__DOT__spliced_bits___05Fh1079) 
                                                << 0xcU) 
                                               | (0xfffU 
                                                  & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_13_60_THEN_IF_inp_B_BIT_12_30_THE_ETC___05F_d980)));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_14_82_THEN_IF_inp_B_BIT_13_60_THE_ETC___05F_d993 
        = ((0x4000U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? (IData)(vlTOPp->mkMult__DOT__product___05Fh1062)
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_13_60_THEN_IF_inp_B_BIT_12_30_THE_ETC___05F_d980));
    vlTOPp->mkMult__DOT__x___05Fh46550 = (1U & (((IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_14_82_THEN_IF_inp_B_BIT_13_60_THE_ETC___05F_d993) 
                                                 >> 0xfU) 
                                                ^ (IData)(vlTOPp->mkMult__DOT__inp_A)));
    vlTOPp->mkMult__DOT__product___05Fh671 = (((IData)(vlTOPp->mkMult__DOT__x___05Fh46550) 
                                               << 0xfU) 
                                              | (0x7fffU 
                                                 & (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_14_82_THEN_IF_inp_B_BIT_13_60_THE_ETC___05F_d993)));
    vlTOPp->mkMult__DOT__IF_inp_B_BIT_15_81_THEN_IF_inp_B_BIT_15_81_THE_ETC___05F_d999 
        = ((0x8000U & (IData)(vlTOPp->mkMult__DOT__inp_B))
            ? ((0x8000U & (IData)(vlTOPp->mkMult__DOT__inp_B))
                ? (IData)(vlTOPp->mkMult__DOT__product___05Fh671)
                : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_14_82_THEN_IF_inp_B_BIT_13_60_THE_ETC___05F_d993))
            : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_14_82_THEN_IF_inp_B_BIT_13_60_THE_ETC___05F_d993));
    vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_13_28_EQ_0_29_THEN_IF_inp___05FETC___05F_d1001 
        = ((0U == (7U & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                         >> 0xdU))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_12_30_THEN_IF_inp_B_BIT_11_92_THE_ETC___05F_d957)
            : ((0U == (3U & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                             >> 0xeU))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_13_60_THEN_IF_inp_B_BIT_12_30_THE_ETC___05F_d980)
                : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_15_81_THEN_IF_inp_B_BIT_15_81_THE_ETC___05F_d999)));
    vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_11_42_EQ_0_43_THEN_IF_inp___05FETC___05F_d1003 
        = ((0U == (0x1fU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                            >> 0xbU))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_10_44_THEN_IF_inp_B_BIT_9_87_THEN_ETC___05F_d889)
            : ((0U == (0xfU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                               >> 0xcU))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_11_92_THEN_IF_inp_B_BIT_10_44_THE_ETC___05F_d927)
                : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_13_28_EQ_0_29_THEN_IF_inp___05FETC___05F_d1001)));
    vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_9_21_EQ_0_22_THEN_IF_inp_B_ETC___05F_d1005 
        = ((0U == (0x7fU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                            >> 9U))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_8_23_THEN_IF_inp_B_BIT_7_50_THEN___05FETC___05F_d784)
            : ((0U == (0x3fU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                                >> 0xaU))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_9_87_THEN_IF_inp_B_BIT_8_23_THEN___05FETC___05F_d841)
                : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_11_42_EQ_0_43_THEN_IF_inp___05FETC___05F_d1003)));
    vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_7_65_EQ_0_66_THEN_IF_inp_B_ETC___05F_d1007 
        = ((0U == (0x1ffU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                             >> 7U))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_6_67_THEN_IF_inp_B_BIT_5_75_THEN___05FETC___05F_d647)
            : ((0U == (0xffU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                                >> 8U))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_7_50_THEN_IF_inp_B_BIT_6_67_THEN___05FETC___05F_d720)
                : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_9_21_EQ_0_22_THEN_IF_inp_B_ETC___05F_d1005)));
    vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_5_74_EQ_0_75_THEN_IF_inp_B_ETC___05F_d1009 
        = ((0U == (0x7ffU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                             >> 5U))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_4_76_THEN_IF_inp_B_BIT_3_68_THEN___05FETC___05F_d472)
            : ((0U == (0x3ffU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                                 >> 6U))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_5_75_THEN_IF_inp_B_BIT_4_76_THEN___05FETC___05F_d564)
                : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_7_65_EQ_0_66_THEN_IF_inp_B_ETC___05F_d1007)));
    vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_3_50_EQ_0_51_THEN_IF_inp_B_ETC___05F_d1011 
        = ((0U == (0x1fffU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                              >> 3U))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_2_52_THEN_IF_inp_B_BIT_1_2_THEN_I_ETC___05F_d265)
            : ((0U == (0xfffU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                                 >> 4U))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_3_68_THEN_IF_inp_B_BIT_2_52_THEN___05FETC___05F_d373)
                : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_5_74_EQ_0_75_THEN_IF_inp_B_ETC___05F_d1009)));
    vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_1_EQ_0_THEN_IF_inp_B_BIT_0_ETC___05F_d1013 
        = ((0U == (0x7fffU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                              >> 1U))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_0_THEN_inp_A_ELSE_0___05F_d9)
            : ((0U == (0x3fffU & ((IData)(vlTOPp->mkMult__DOT__inp_B) 
                                  >> 2U))) ? (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BIT_1_2_THEN_IF_inp_B_BIT_0_THEN_inp___05FETC___05F_d149)
                : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_3_50_EQ_0_51_THEN_IF_inp_B_ETC___05F_d1011)));
    vlTOPp->mkMult__DOT__x___05Fh243 = ((0U == (IData)(vlTOPp->mkMult__DOT__inp_B))
                                         ? (IData)(vlTOPp->mkMult__DOT__inp_B)
                                         : (IData)(vlTOPp->mkMult__DOT__IF_inp_B_BITS_15_TO_1_EQ_0_THEN_IF_inp_B_BIT_0_ETC___05F_d1013));
    vlTOPp->mkMult__DOT__product_temp___05Fh239 = (
                                                   (0xffff0000U 
                                                    & ((- (IData)(
                                                                  (1U 
                                                                   & ((IData)(vlTOPp->mkMult__DOT__x___05Fh243) 
                                                                      >> 0xfU)))) 
                                                       << 0x10U)) 
                                                   | (IData)(vlTOPp->mkMult__DOT__x___05Fh243));
    vlTOPp->mkMult__DOT__result_D_IN = (vlTOPp->mkMult__DOT__product_temp___05Fh239 
                                        + vlTOPp->mkMult__DOT__inp_C);
}

VL_INLINE_OPT void Vtop::_combo__TOP__5(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_combo__TOP__5\n"); );
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->mkMult__DOT__inp_C_EN = vlTOPp->EN_get_inp;
    vlTOPp->mkMult__DOT__inp_C_D_IN = vlTOPp->get_inp_c;
    if (vlTOPp->EN_get_inp) {
        vlTOPp->mkMult__DOT__state_D_IN = 1U;
        vlTOPp->mkMult__DOT__inp_B_EN = 1U;
    } else {
        vlTOPp->mkMult__DOT__state_D_IN = 2U;
        vlTOPp->mkMult__DOT__inp_B_EN = 0U;
    }
    vlTOPp->mkMult__DOT__inp_B_D_IN = ((0xff00U & (
                                                   (- (IData)(
                                                              (1U 
                                                               & ((IData)(vlTOPp->get_inp_b) 
                                                                  >> 7U)))) 
                                                   << 8U)) 
                                       | (IData)(vlTOPp->get_inp_b));
    vlTOPp->mkMult__DOT__inp_A_EN = vlTOPp->EN_get_inp;
    vlTOPp->mkMult__DOT__inp_A_D_IN = ((0xff00U & (
                                                   (- (IData)(
                                                              (1U 
                                                               & ((IData)(vlTOPp->get_inp_a) 
                                                                  >> 7U)))) 
                                                   << 8U)) 
                                       | (IData)(vlTOPp->get_inp_a));
    vlTOPp->mkMult__DOT__state_EN = ((IData)(vlTOPp->EN_get_inp) 
                                     | (IData)(vlTOPp->mkMult__DOT__WILL_FIRE_RL_rl_compute));
}

void Vtop::_eval(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval\n"); );
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    if (((IData)(vlTOPp->CLK) & (~ (IData)(vlTOPp->__Vclklast__TOP__CLK)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    vlTOPp->_combo__TOP__5(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__CLK = vlTOPp->CLK;
}

VL_INLINE_OPT QData Vtop::_change_request(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_change_request\n"); );
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vtop::_change_request_1(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_change_request_1\n"); );
    Vtop* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vtop::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((CLK & 0xfeU))) {
        Verilated::overWidthError("CLK");}
    if (VL_UNLIKELY((RST_N & 0xfeU))) {
        Verilated::overWidthError("RST_N");}
    if (VL_UNLIKELY((EN_get_inp & 0xfeU))) {
        Verilated::overWidthError("EN_get_inp");}
}
#endif  // VL_DEBUG
