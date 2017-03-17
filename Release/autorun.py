﻿import ctypes,json
import __main__
import rpc
svr_ip='127.0.0.1'
login_port=8000
cln=rpc.RpcClient(svr_ip,login_port)
token=''
history=[]
def can_run():
	mutex=ctypes.windll.kernel32.CreateMutexW(0,0,'huancuiguotuqingxiaojia')
	if mutex==0:
		return 0
	if ctypes.windll.kernel32.GetLastError()==183:
		return 0
	return 1


def show_menu(x, y, li):
    __main__.exe_fun__['block_message'](1)
    menu = ctypes.windll.user32.CreatePopupMenu()
    for n in range(len(li)):
        ctypes.windll.user32.AppendMenuW(menu, 0x10, n+1, li[n])
    hwn=__main__.exe_fun__['get_main_hwnd']()
    ctypes.windll.user32.SetForegroundWindow(hwn)
    select = ctypes.windll.user32.TrackPopupMenuEx(menu, 0x1a3, x, y, hwn, 0)
    ctypes.windll.user32.DestroyMenu(menu)
    __main__.exe_fun__['block_message'](0)
    if select==0:
        return ''
    return li[select-1]

def on_tray_rbtnup(x,y):
    pos=ctypes.c_uint32*2
    pos=pos()
    ctypes.windll.user32.GetCursorPos(ctypes.byref(pos))
    sel=show_menu(pos[0],pos[1],['主窗口','退出'])
    __main__.exe_fun__['block_message'](0)
    try:
        if sel=='主窗口':
            __main__.exe_fun__['show_window'](1)
            return
        if sel=='退出':
            __main__.exe_fun__['quit_app']()
            return
    except:
        pass

def on_cb_chg(x,y):
    pass
    #msgbox('on clipboard change')

import winsound
def on_timer(x,y):
	pass
    #winsound.Beep(x*500,200)
    #msgbox('on timer'+str(x))

def on_tray_ldbclk(x,y):
    __main__.exe_fun__['show_window'](1)

def on_destroy_window(x,y):
    pass#msgbox('on destroy window.')

def do_login(x,y):
	try:
		import binascii
		x=ctypes.c_wchar_p(x).value
		y=ctypes.c_wchar_p(y).value
		#y=str(binascii.crc32(y.encode('utf-8')))################error!!
		ex=encrypt(x)
		ey=encrypt(y)
		ret=cln.login(ex,ey)
		if len(ret)==3:
			__main__.stack__[:3]=ret
			__main__.__c2p2c__=3
			global token
			token=x
			json.dump((ex,ey),open('login.json','w'))
		else:
			__main__.stack__[0]=ret[0]
			__main__.__c2p2c__=1
	except:
		__main__.__c2p2c__=0
		__main__.stack__[0]='服务器连接错误！'


order=['待您审批','待领导审批','已批准','已销假','未批准']

def refresh_history(x,y):
	global history
	try:
		history=cln.get_history(token)
		__main__.stack__[0]=''
	except:
		__main__.stack__[0]='offline'
		return
	for x in history:
		if x[8]!='':
			sta='已销假'
		else:
			if x[6]=='':
				sta='待领导审批' if x[0]==token else '待您审批'
			else:
				sta='已批准' if x[6]=='是' else '未批准'
		x.append(sta)
	history.sort(key=lambda x:order.index(x[-1]))

	for n,x in enumerate(history):
		__main__.exe_fun__['append_history'](n,x[0],x[1],x[2],x[-1],x[-2])#-1 is sta,-2 is server history number.

def get_history_detail(x,y):
	L=len(history[0])
	__main__.stack__[:L]=history[x]
	#__main__.stack__[2]=ctime_atoi(__main__.stack__[2])
	#__main__.stack__[3]=ctime_atoi(__main__.stack__[3])

def get_log_info(x,y):
	info=json.load(open('login.json','r'))
	__main__.stack__[0]=decrypt(info[0])
	__main__.stack__[1]=decrypt(info[1])

def submit(x,y):
	token=__main__.stack__[0]
	piece=__main__.stack__[1:10]
	no=__main__.stack__[10]
	#piece[2]=ctime_itoa(piece[2])
	#piece[3]=ctime_itoa(piece[3])
	cln.submit(token,piece,no)

def change_pwd(x,y):
	un,po,pa=__main__.stack__[:3]
	__main__.stack__[0]=cln.change_pwd(un,po,pa)



def do_back(x,y):
	__main__.stack__[0]=cln.do_back(token,x)

def init_dialog(x,y):
	__main__.py_fun__['on_timer'] =on_timer
	__main__.py_fun__['on_destroy_window'] =on_destroy_window
	__main__.py_fun__['on_tray_ldbclk'] =on_tray_ldbclk
	__main__.py_fun__['on_tray_rbtnup']=on_tray_rbtnup
	__main__.py_fun__['on_tray_rdbclk']=on_tray_rbtnup
	__main__.py_fun__['on_clipboard_change']=on_cb_chg
	__main__.py_fun__['login']=do_login
	__main__.py_fun__['refresh_history']=refresh_history
	__main__.py_fun__['submit']=submit
	__main__.py_fun__['get_log_info']=get_log_info
	__main__.py_fun__['do_back']=do_back
	__main__.py_fun__['change_pwd']=change_pwd
	__main__.py_fun__['get_history_detail']=get_history_detail
__main__.py_fun__['on_init_dialog']=init_dialog	

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
