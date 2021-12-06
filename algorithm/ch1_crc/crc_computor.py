import pycrc
import os
import crcmod

# pycrc 和 crcmod
if __name__ == '__main__':
	print('*'*10 + ' test start ' + '*'*10)
	str1 = '123465789'
	crc32_func = crcmod.mkCrcFun(0x104C110DB7, initCrc=0, xorOut=0xFFFFFFFF)
	#print(hex(crc32_func(str1.encode()))	
	print('*'*10 + ' test end ' + '*'*10)
