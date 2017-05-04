import win32tools
import ctypes
import sys
import rpc
import binascii
import socket
import os

socket.setdefaulttimeout(1)
cln=rpc.RpcClient('10.176.236.230',9000)
#cln=rpc.RpcClient('127.0.0.1',9000)

def get_file_needs():
	fileneeds=[]
	newinfo=cln.get_info()
	for fn in newinfo:
		try:
			dat=open(fn,'rb').read()
		except:
			dat=b''
		crc=binascii.crc32(dat)
		if str(crc)!=newinfo[fn]:
			fileneeds.append(fn)
	return fileneeds

def down_load(files):
	for fn in files:
		try:
			dat=cln.get_data(fn).data
			open(fn,'wb').write(dat)
		except:
			pass

def do_upgrade():
	files=get_file_needs()
	down_load(files)
	return 1 if files else 0