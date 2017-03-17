import win32tools
import ctypes
import sys
import rpc
import binascii

cln=rpc.RpcClient('10.176.236.230',9000)

pid=int(sys.argv[1])
exefn=win32tools.pid2fn(pid)


fileneeds=[]

newinfo=cln.get_info()
for fn in newinfo:
	fnr=exefn if fn=='main' else fn
	try:
		dat=open(fnr,'rb').read()
	except:
		dat=b''
	crc=binascii.crc32(dat)
	if str(crc)!=newinfo[fn]:
		fileneeds.append(fn)


if 'main' in fileneeds:
	win32tools.killpid(pid)

for fn in fileneeds:
	fnw=exefn if fn=='main' else fn
	try:
		dat=cln.get_data(fn).data
		open(fnw,'wb').write(dat)
	except:
		pass

if 'main' in fileneeds:
	win32tools.shell_execute(exefn)
