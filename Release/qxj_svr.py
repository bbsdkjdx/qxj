import rpc
import time
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


def add_user(nick,passwd,name,department):
	pass

def login(un,pw):
	un=decrypt(un)
	pw=decrypt(pw)
	print(un,pw)
	if un not in users:
		return ('无此用户！',)
	if users[un][0]!=pw:
		return ('密码错误！',)
	dep=users[un][1]
	leader=users[un][2]
	return un,dep,leader#name,department,leader

def get_history(token):
	return [x+[n] for n,x in enumerate(history) if x[0]==token or x[1]==token]


def submit(token,piece,no):
	if token not in users:
		return '无此用户'
	if no not in actives:
		no=str(time.time())
	actives[no]=piece
	return 'ok'

def do_back(token,no):
	print('back:'+token+no)
	if token not in users:
		return '无此用户'
	if no in actives:
		piece=actives[no]
		piece[-1]=time.strftime('%Y.%m.%d %H:%M')
		actives.pop(no)
		history.append(piece)
	return 'ok'

def change_pwd(name,po,pn):
	if name not in users:
		return '无此用户'
	if users[name][0]==po:
		users[name][0]=pn
		return 'ok'
	else:
		return '原密码不正确'

def get_actives(token):
	ret=[]
	for x in actives:
		pc=actives[x]
		if pc[0]==token or pc[1]==token:
			ret.append(pc+[x])
	print(ret)
	return ret

svr.reg_fun(change_pwd)
svr.reg_fun(do_back)
svr.reg_fun(submit)
svr.reg_fun(get_actives)
svr.reg_fun(login)
svr.run(0)