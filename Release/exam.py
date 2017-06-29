# -*- coding: utf-8 -*-

import win32com.client
import os
import time
import ctypes
# ie.ReadyState==4 #ready
# elm=ieapp.Document.getElementById("srch1")
# elm.value=
# elm.click()
# ieapp.Document.body.innerHTML
# ieapp.Quit()


def trace(node, li):
    for x in li:
        node = node.childNodes[x]
    return node


def work(un, pw):
    ieapp = win32com.client.Dispatch("InternetExplorer.Application")
    ieapp.Visible = True
    ieapp.Navigate(r"http://123.232.119.108:8083/xzzf/background/login.html")

    while ieapp.ReadyState != 4:
        time.sleep(0.2)
    doc = ieapp.Document
    node = trace(doc.body, [0, 7, 0, 1, 0, 0])
    usr = trace(node, [0, 1, 0])
    pwd = trace(node, [1, 1, 0])
    submit = trace(node, [2, 1, 0])
    usr.value = un
    pwd.value = pw
    submit.click()
    #time.sleep(1)
    #hwnd=ctypes.windll.user32.GetForegroundWindow()
    #ctypes.windll.user32.MessageBoxW(hwnd,'请点击“日前维护->模拟考试”进入考试！','请销假客户端',0)