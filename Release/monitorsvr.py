import rpc
import binascii
import os

svr=rpc.RpcSvr(ip='0.0.0.0',port=9001)

def log_info(info):
	print(info)


svr.reg_fun(log_info)
print('monitor running...')
svr.run()