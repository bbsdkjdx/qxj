import rpc
import binascii
import os
import time

svr=rpc.RpcSvr(ip='0.0.0.0',port=9001)

last_title=dict()

def log_info(info):
	print(info)
	name,title,exefn=info.split('\t')
	if title!=last_title.get(name,''):
		last_title[name]=title
		stm=time.strftime('%Y-%m-%d %H:%M')
		s='\t'.join([stm,name,title,exefn])
		open('monitor.txt','a').write(s+'\n')


svr.reg_fun(log_info)
print('monitor running...')
svr.run()