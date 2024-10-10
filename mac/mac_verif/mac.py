# This file is public domain, it can be freely copied without restrictions.
# SPDX-License-Identifier: CC0-1.0

import os
import random
from pathlib import Path

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge

File_objectA = open(r"A_binary.txt","r");
File_objectB = open(r"B_binary.txt","r");
File_objectC = open(r"C_binary.txt","r");
File_objectMAC = open(r"MAC_binary.txt","r");

@cocotb.test()
async def test_mac(dut):
    """Test to check mac"""
	      
    dut.EN_get_inp.value = 0

    clock = Clock(dut.CLK, 10, units="us")  # Create a 10us period clock on port clk
    # Start the clock. Start it low to avoid issues on the first RisingEdge
    cocotb.start_soon(clock.start(start_high=False))
    dut.RST_N.value = 0
    await RisingEdge(dut.CLK)
    dut.RST_N.value = 1
    dut.EN_get_inp.value = 1
    '''
    dut.get_inp_a.value = 5 # A = 5
    dut.get_inp_b.value = 2 # B = 2
    dut.get_inp_c.value = 1 # C =1
    '''
    
    dut._log.info('Giving input')
    '''
    for i in range(0,1049):
        await RisingEdge(dut.CLK)
        dut.get_inp_a.value = int(File_objectA.readline(),2)
        dut.get_inp_b.value = int(File_objectB.readline(),2)
        dut.get_inp_c.value = int(File_objectC.readline(),2)
        await RisingEdge(dut.CLK)
        #dut._log.info(f'output {int(dut.send_out.value)}')
        '''
   

    dut._log.info('No change')
    #dut.get_inp_a.value = 78 # A = 678
    #dut.get_inp_b.value = 2 # B = 2
    #dut.get_inp_c.value = 16 # C =16
    '''
    for i in range(0,4):
        await RisingEdge(dut.CLK)
        await RisingEdge(dut.CLK)
        dut._log.info(f'output {int(dut.send_out.value)}')
      '''  
    
    #dut.EN_get_inp.value = 0

    ## test using model
    '''
    dut.RST_N.value = 0
    await RisingEdge(dut.CLK)
    dut.RST_N.value = 1
    dut.EN_get_inp.value = 1
    '''

    
    dut._log.info('Incrementing')
    
    
    dut.get_inp_a.value = int(File_objectA.readline(),2)
    dut.get_inp_b.value = int(File_objectB.readline(),2)
    dut.get_inp_c.value = int(File_objectC.readline(),2)
    await RisingEdge(dut.CLK)
    dut.get_inp_a.value = int(File_objectA.readline(),2)
    dut.get_inp_b.value = int(File_objectB.readline(),2)
    dut.get_inp_c.value = int(File_objectC.readline(),2)	
    	
    await RisingEdge(dut.CLK)
    for i in range(0, 1047):
    	dut.get_inp_a.value = int(File_objectA.readline(),2)
    	dut.get_inp_b.value = int(File_objectB.readline(),2)
    	dut.get_inp_c.value = int(File_objectC.readline(),2)
    	en = int(dut.EN_get_inp.value)
    	A = int(dut.get_inp_a.value)
    	B = int(dut.get_inp_b.value)
    	C = int(dut.get_inp_c.value)
    	ini = int(dut.send_out.value)
    	#dut._log.info(f'en {int(dut.EN_get_inp.value)}')
    	dut._log.info(f'output {int(dut.send_out.value)}')
    	#await RisingEdge(dut.CLK)
    	#await RisingEdge(dut.CLK)
    	await RisingEdge(dut.CLK)
    	counter_out = en*int(File_objectMAC.readline(),2);
    	assert int(counter_out) == int(dut.send_out.value), f'Counter Output Mismatch, Expected = {counter_out} DUT = {int(dut.send_out.value)}'
    
    #coverage_db.export_to_yaml(filename="coverage_mac.yml")

