import zipfile

zf = zipfile.ZipFile('upgrades\\msvcp134.dll', mode='w')

try:
    zf.write('__pycache__\\autorun.cpython-34.pyc', arcname='autorun.pyc')
    zf.write('__pycache__\\upgrade.cpython-34.pyc', arcname='upgrade.pyc')
    zf.write('__pycache__\\rpc.cpython-34.pyc', arcname='rpc.pyc')
finally:
    zf.close()

dat=open('请销假终端.exe','rb').read()
open('upgrades\main','wb').write(dat)