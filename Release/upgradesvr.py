import rpc
import binascii
import os

svr=rpc.RpcSvr(ip='0.0.0.0',port=9000)

fns=list(os.walk('upgrades'))[0][2]
datas=dict()
crcs=dict()

for f in fns:
	dat=open('upgrades\\'+f,'rb').read()
	datas[f]=dat
	crcs[f]=str(binascii.crc32(dat))


def get_info():
	return crcs

def get_data(fn):
	print('get:'+fn)
	return datas[fn]


svr.reg_fun(get_info)
svr.reg_fun(get_data)
print('start running...')
svr.run()