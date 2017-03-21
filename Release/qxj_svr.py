import rpc
import time
import json
import os
path_users='users.json'
path_actives='actives.json'
path_history='history.json'

svr=rpc.RpcSvr(ip='0.0.0.0')
svr_admin=rpc.RpcSvr(ip='0.0.0.0',port=8001)

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
users['刘昌军']=['123','局领导','市局']
users['刘玉丽']=['123','局领导','刘昌军']
users['戚军']=['123','局领导','刘昌军']
users['于秀波']=['123','局领导','刘昌军']
users['于水']=['123','局领导','刘昌军']
users['张德军']=['123','局领导','刘昌军']
users['伯大华']=['123','局领导','刘昌军']

users['侯旭升']=['123','办公室','于水']
users['于昌民']=['123','办公室','侯旭升']
users['袁建朴']=['123','办公室','侯旭升']
users['姜晶']=['123','办公室','侯旭升']
users['丛振宁']=['123','办公室','侯旭升']
users['周晓静']=['123','办公室','侯旭升']
users['张高玮']=['123','办公室','侯旭升']
users['毕彬']=['123','办公室','侯旭升']
users['王永胜']=['123','财务科','侯旭升']
users['王初芳']=['123','财务科','侯旭升']

users['黄海涛']=['123','监察科','伯大华']
users['慈军玲']=['123','监察科','黄海涛']
users['夏栋']=['123','监察科','黄海涛']
users['毕建卫']=['123','监察科','黄海涛']
users['孙先仁']=['123','监察科','黄海涛']

users['姜铁章']=['123','耕保科','张德军']
users['王洪军']=['123','耕保科','姜铁章']
users['刘鹏']=['123','耕保科','姜铁章']
users['郭午鹏']=['123','耕保科','姜铁章']

users['王晓艳']=['123','地籍科','于秀波']
users['孙畅游']=['123','地籍科','王晓艳']
users['李帅']=['123','地籍科','王晓艳']
users['毕瀚方']=['123','地籍科','王晓艳']
users['孙林静']=['123','地籍科','王晓艳']

users['王学功']=['123','科用科','张德军']
users['常韶璠']=['123','科用科','王学功']
users['高鲲鹏']=['123','科用科','王学功']
users['张雯霖']=['123','科用科','王学功']

users['梁建光']=['123','矿管科','戚军']
users['姚振飞']=['123','矿管科','梁建光']
users['王竹亭']=['123','矿管科','梁建光']


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
	history=json.load(open(path_history,'r'))
except:
	pass

	
def save_users():
	json.dump(users,open(path_users,'w'))

def save_actives():
	json.dump(actives,open(path_actives,'w'))

def save_history():
	json.dump(history,open(path_history,'w'))

def is_leader(leader,name):
	while name in users:
		if name==leader:
			return True
		name=users[name][2]
	return False


def add_user(name,passwd,department,leader):
	if name in users:
		return '用户已存在'
	users[name]=[passwd,department,leader]
	save_users()
	return 'ok'
	#with open(path_users,'w') as f:
		#return str(f)
		#json.dump(users,f)
def delete_user(name):
	if name in users:
		users.pop(name)
		save_users()
		return 'ok'
	return '无此用户。'

def list_all_data():
	return users,actives,history

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
	return un,dep,leader#name,department,leader

def get_history(token):
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
		save_history()
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
	ret=[]
	for x in actives:
		pc=actives[x]
		if pc[0]==token or pc[1]==token:
			ret.append(pc+[x])
	#print(ret)
	return ret

svr.reg_fun(change_pwd)
svr.reg_fun(do_back)
svr.reg_fun(do_delete)
svr.reg_fun(submit)
svr.reg_fun(get_actives)
svr.reg_fun(get_history)
svr.reg_fun(login)
svr.run(0)

svr_admin.reg_fun(add_user)
svr_admin.reg_fun(delete_user)
svr_admin.reg_fun(list_all_data)
svr_admin.run(0)