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

pid=int(sys.argv[1])
exefn=win32tools.pid2fn(pid)


fileneeds=[]
filermv=[]

newinfo=cln.get_info()
for fn in newinfo:
	fnr=exefn if fn=='main' else fn
	if newinfo[fn]=='0':
		filermv.append(fnr)
		continue
	try:
		dat=open(fnr,'rb').read()
	except:
		dat=b''
	crc=binascii.crc32(dat)
	if str(crc)!=newinfo[fn]:
		fileneeds.append(fn)

if fileneeds:
	win32tools.killpid(pid)

for fn in filermv:
	try:
		os.remove(fn)
	except:
		pass
		

for fn in fileneeds:
	fnw=exefn if fn=='main' else fn
	try:
		dat=cln.get_data(fn).data
		open(fnw,'wb').write(dat)
	except:
		pass

if fileneeds:
	win32tools.shell_execute(exefn)
