import rpc
import time
import json
import os
import sys

#disable std.err output.
class MyStdError(object):
	def write(self,*arg):
		pass
oldstderr=sys.stderr
sys.stderr=MyStdError()
		
show_active=0

path_users='users.json'
path_actives='actives.json'
path_history='history.json'

svr=rpc.RpcSvr(ip='0.0.0.0')

def encrypt(s):
	import base64
	s=s.encode()
	s=base64.a85encode(base64.b85encode(s))
	return s.decode()

def decrypt(s):
	import base64
	s=s.encode()
	s=base64.b85decode(base64.a85decode(s))
	return s.decode()


users=dict()
actives=dict()
history=list()

try:
	users=json.load(open(path_users,'r'))
except:
	pass
try:
	actives=json.load(open(path_actives,'r'))
except:
	pass
try:
	for x in open(path_history,'r'):
		history.append(json.loads(x))
except:
	pass

	
def save_users():
	json.dump(users,open(path_users,'w'))

def save_actives():
	json.dump(actives,open(path_actives,'w'))

def save_history(piece):
	open(path_history,'a').write(json.dumps(piece)+'\n')

def is_leader(leader,name):
	while name in users:
		if name==leader:
			return True
		name=users[name][2]
	return False

def login(un,pw):
	un=decrypt(un)
	pw=decrypt(pw)
	#print(un,pw)
	if un not in users:
		return ('无此用户！',)
	if users[un][0]!=pw:
		return ('密码错误！',)
	dep=users[un][1]
	leader=users[un][2]
	if show_active:
		print(un+' login.')
	return un,dep,leader#name,department,leader

def get_history(token):
	if token=='admin':
		return history
	names={x for x in users if is_leader(token,x)}
	return [x for x in history if x[0] in names]


def submit(token,piece,no):
	if token not in users:
		return '无此用户'
	if piece in actives.values():
		return 'ok'
	if no not in actives:
		no=str(time.time())
	actives[no]=piece
	save_actives()
	return 'ok'

def do_back(token,no):
	if token not in users:
		return '无此用户'
	if no in actives:
		piece=actives[no]
		piece[-1]=time.strftime('%Y.%m.%d %H:%M')
		actives.pop(no)
		history.append(piece)
		save_actives()
		save_history(piece)
	return 'ok'

def do_delete(token,no):
	if token not in users:
		return '无此用户'
	if no in actives:
		actives.pop(no)
		save_actives()
	return 'ok'

def change_pwd(name,po,pn):
	if name not in users:
		return '无此用户'
	if users[name][0]==po:
		users[name][0]=pn
		save_users()
		return 'ok'
	else:
		return '原密码不正确'

def get_actives(token):
	values=list(actives.values())
	if token in ['admin','刘昌军']:
		return values

	names={x for x in users if is_leader(token,x)}
	return [x for x in values if x[0] in names]

	if show_active:
		print(token+' refresh.')
	return ret

svr.reg_fun(change_pwd)
svr.reg_fun(do_back)
svr.reg_fun(do_delete)
svr.reg_fun(submit)
svr.reg_fun(get_actives)
svr.reg_fun(get_history)
svr.reg_fun(login)
svr.run(0)
