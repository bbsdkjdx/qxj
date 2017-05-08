import win32tools
import ctypes
import sys
import rpc
import binascii
import socket
import os
import time
#socket.setdefaulttimeout(2)
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
	try:
		files=get_file_needs()
		down_load(files)
		return 1 if files else 0
	except:
		return 0


try:
	wnd=int(sys.argv[-1])
	pid=win32tools.wnd2pid(wnd)
	fn=win32tools.pid2fn(pid)
	fn=fn[fn.rfind('\\')+1:]
	if do_upgrade():
		ctypes.windll.user32.SendMessageW(wnd,44444,0,0)
		while ctypes.windll.user32.IsWindow(wnd):
			time.sleep(1)
		with open(fn,'wb') as fw:
			fw.write(open('main','rb').read())
		ctypes.windll.kernel32.WinExec(fn.encode('gb2312'),1)
except:
	pass
