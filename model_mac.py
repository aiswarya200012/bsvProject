# model for IEEE 754 
		  
import cocotb
from cocotb_coverage.coverage import *
import numpy as np

mac_coverage = coverage_section(
    CoverPoint('top.get_input_a', vname='get_input_a', bins = list([0b0100001001100101,
0b0100010001100011,
0b0101000010111100])),
    CoverPoint('top.get_input_b', vname='get_input_b', bins = list([0b0100101100111110,
0b0100011110111110,
0b0101001111101110])),
    CoverPoint('top.get_input_c', vname='get_input_c', bins = list([0b01001111100110111010010111100100,
0b01000001001100000010010011011110,
0b01001100011101011100001010010000])),
    CoverPoint('top.EN_get_input', vname='EN_get_input', bins = list(range(1,2))),
    CoverCross('top.cross_cover', items = ['top.get_input_a', 'top.get_input_b', 'top.get_input_c'])
)

import numpy as np
import struct

def bfloat16_to_float32(bfloat16: int) -> np.float32:
	"""Convert bfloat16 integer to float32 without using built-in functions."""
	# Extract the sign (1 bit), exponent (8 bits), and mantissa (7 bits)
	sign = (bfloat16 >> 15) & 0x01  # Get the sign bit
	exponent = (bfloat16 >> 7) & 0xFF  # Get the exponent (8 bits)
	mantissa = bfloat16 & 0x7F  # Get the mantissa (7 bits)
	
	# Construct the float32 representation
	# For float32: 1 bit sign, 8 bits exponent, 23 bits mantissa
	float32_bits = ((sign << 31) | (exponent << 23) | (mantissa << 16))
	
	# Convert bits to float using struct
	# float32_bytes = float32_bits.to_bytes(4, byteorder='big')
	float32_value = ieee754_to_decimal(float32_bits)
	
	return float32_value

def float32_to_bits(float_value: float) -> int:
	"""Convert float32 to its bit representation as an integer."""
	return struct.unpack('>I', struct.pack('>f', float_value))[0]

def bits_to_float32(bit_representation: int) -> float:
	"""Convert an integer bit representation back to float32."""
	return struct.unpack('>f', struct.pack('>I', bit_representation))[0]

def decimal_to_ieee754(value: float) -> int:
	"""Convert a decimal float to its IEEE 754 (32-bit) representation as an integer."""
	if value == 0.0:
		return 0  # Special case for zero

	# Determine the sign bit
	sign = 0 if value >= 0 else 1
	value = abs(value)

	# Get the integer and fractional parts
	integer_part = int(value)
	fractional_part = value - integer_part

	# Convert integer part to binary
	integer_bits = ''
	if integer_part > 0:
		while integer_part > 0:
			integer_bits = str(integer_part % 2) + integer_bits
			integer_part //= 2

	# Convert fractional part to binary
	fractional_bits = ''
	while fractional_part > 0 and len(fractional_bits) < 23:  # Limit to 23 bits
		fractional_part *= 2
		bit = int(fractional_part)
		fractional_bits += str(bit)
		fractional_part -= bit

	# Combine integer and fractional parts
	if integer_bits == '':
		# If there is no integer part, find first '1' in fractional part
		first_one_index = fractional_bits.find('1')
		if first_one_index == -1:
			# Value is 0
			return 0
		exponent = - (first_one_index + 1)  # Adjust exponent
		mantissa_bits = fractional_bits[first_one_index + 1:]  # Get bits after first '1'
	else:
		exponent = len(integer_bits) - 1  # Position of the first '1' in integer part
		mantissa_bits = integer_bits[1:] + fractional_bits  # Skip the leading '1'

	# Normalize mantissa to 23 bits
	mantissa_bits = mantissa_bits[:23]  # Only take the first 23 bits
	mantissa = int(mantissa_bits.ljust(23, '0'), 2)  # Pad to 23 bits

	# Calculate the biased exponent
	biased_exponent = exponent + 127

	# Pack sign, exponent, and mantissa into a 32-bit integer
	ieee754_bits = (sign << 31) | (biased_exponent << 23) | mantissa

	return ieee754_bits
    
def ieee754_to_decimal(ieee754_bits: int) -> float:
	"""Convert IEEE 754 (32-bit) integer representation to decimal float."""
	# Extract the sign, exponent, and mantissa
	sign = (ieee754_bits >> 31) & 0x01
	exponent = (ieee754_bits >> 23) & 0xFF
	mantissa = ieee754_bits & 0x7FFFFF  # Get the last 23 bits
	# Calculate the decimal value
	if exponent == 0:  # Handle subnormal numbers
		value = (-1) ** sign * (mantissa / (1 << 23)) * (2 ** -126)
	elif exponent == 255:  # Handle special cases (infinity or NaN)
		if mantissa == 0:
			return float('inf') if sign == 0 else float('-inf')
		else:
			return float('nan')
	else:
		# Normalized case
		mantissa_value = 1 + mantissa / (1 << 23)  # Add the implicit leading 1
		exponent_value = exponent - 127
		value = (-1) ** sign * mantissa_value * (2 ** exponent_value)
	return value  
	  
@mac_coverage
def model_mac(get_input_a: int, EN_get_input: int, get_input_b: int, get_input_c: int) -> int:
	if(EN_get_input):	
		"""Perform MAC operation with input bits and return output as bits."""
		# Convert bfloat16 inputs a and b to float32
		A_float = bfloat16_to_float32(get_input_a)
		B_float = bfloat16_to_float32(get_input_b)

		# Convert c from its bit representation to float32
		C_float = bits_to_float32(get_input_c)

		
		# Perform the MAC operation: C + (A * B)
		result_float =  C_float + (A_float * B_float)
		

		# Convert the result back to bit representation
		result_bits = float32_to_bits(result_float)
		
		return result_bits
	return 0

	
