import sys
import urllib.request
from xml.etree.ElementTree import tostring
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic

form_class = uic.loadUiType("GCS_test.ui")[0]
lnt = 961192.0000000002
lat = 1961815.9999999255
zoom = 9

class WindowClass(QMainWindow, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        
        self.btn_autopilot.pressed.connect(self.func_btn_autopilot)
        self.btn_autopilot.setCheckable(True)
        self.btn_manualpilot.pressed.connect(self.func_btn_manualpilot)
        self.btn_manualpilot.setCheckable(True)
        self.btn_manualpilot.toggle()

        self.btn_forward.pressed.connect(self.func_btn_forward)
        self.btn_forward.released.connect(self.func_btn_forward_)
        self.btn_backward.pressed.connect(self.func_btn_backward)
        self.btn_backward.released.connect(self.func_btn_backward_)
        self.btn_left.pressed.connect(self.func_btn_left)
        self.btn_left.released.connect(self.func_btn_left_)
        self.btn_right.pressed.connect(self.func_btn_right)
        self.btn_right.released.connect(self.func_btn_right_)

        self.temp_btn_refresher.clicked.connect(self.LoadSoxMap)


    def LoadSoxMap(self):
        global lnt, lat
        urlString = "http://make-random.com/MakeRandom/getMapImage.do?lnt="+str(lnt)+"&lat="+str(lat)+"&zoom="+str(zoom)+"&w=640&h=480&map=naver"        
        imageFromWeb = urllib.request.urlopen(urlString).read()
        self.qPixmapWebVar = QPixmap()
        self.qPixmapWebVar.loadFromData(imageFromWeb)
        self.qPixmapWebVar = self.qPixmapWebVar.scaledToWidth(640)
        self.image_gps.setPixmap(self.qPixmapWebVar)

        lnt+=200
        lat+=200

    def func_btn_autopilot(self):
        if(self.btn_autopilot.isChecked()):
            print("manualpilot mode")
            self.btn_manualpilot.toggle()
            self.btn_forward.setEnabled(True)
            self.btn_backward.setEnabled(True)
            self.btn_left.setEnabled(True)
            self.btn_right.setEnabled(True)
            return

        print("autopilot mode")
        self.btn_manualpilot.toggle()
        self.btn_forward.setEnabled(False)
        self.btn_backward.setEnabled(False)
        self.btn_left.setEnabled(False)
        self.btn_right.setEnabled(False)


    def func_btn_manualpilot(self):
        if(self.btn_manualpilot.isChecked()):
            print("autopilot mode")
            self.btn_autopilot.toggle()
            self.btn_forward.setEnabled(False)
            self.btn_backward.setEnabled(False)
            self.btn_left.setEnabled(False)
            self.btn_right.setEnabled(False)
            return

        print("manualpilot mode")
        self.btn_autopilot.toggle()
        self.btn_forward.setEnabled(True)
        self.btn_backward.setEnabled(True)
        self.btn_left.setEnabled(True)
        self.btn_right.setEnabled(True)

    
    def func_btn_forward(self):
        print("forward go")

    def func_btn_forward_(self):
        print("forward stop")

    def func_btn_backward(self):
        print("backward go")

    def func_btn_backward_(self):
        print("backward stop")

    def func_btn_left(self):
        print("left go")

    def func_btn_left_(self):
        print("left stop")
    
    def func_btn_right(self):
        print("right go")
        
    def func_btn_right_(self):
        print("right stop")

    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindow = WindowClass()
    myWindow.show()
    app.exec_()

