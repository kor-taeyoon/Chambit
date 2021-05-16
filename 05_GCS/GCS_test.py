import sys
import urllib.request
from xml.etree.ElementTree import tostring
from PyQt5 import QtSerialPort
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtSerialPort import *
from PyQt5 import uic
import serial

# Global variables
form_class = uic.loadUiType("GCS_test.ui")[0]
lnt = 961192.0000000002
lat = 1961815.9999999255
zoom = 9
ser = 0

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
        self.btn_stop.pressed.connect(self.func_btn_stop)

        self.temp_btn_refresher.pressed.connect(self.LoadSoxMap)
        self.temp_send.pressed.connect(self.sendtest)

        self.btn_port_refresher.pressed.connect(self.port_refresh)
        self.table_port.cellDoubleClicked.connect(self.connect_test)
        self.table_port.setEditTriggers(QAbstractItemView.NoEditTriggers)

        self.btn_stream.pressed.connect(self.stream_start)


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



    def port_refresh(self):
        self.table_port.clearContents()
        available = QtSerialPort.QSerialPortInfo().availablePorts()
        cur_row = 0
        for x in available:
            self.table_port.setItem(cur_row, 0, QTableWidgetItem(str(x.portName())))
            self.table_port.setItem(cur_row, 1, QTableWidgetItem(str(x.description())))
            self.table_port.setItem(cur_row, 2, QTableWidgetItem(str(x.isBusy())))
            self.table_port.setItem(cur_row, 3, QTableWidgetItem(str(x.isValid())))
            cur_row+=1

    def connect_test(self):
        global ser
        if type(ser) == int:
            ser = serial.Serial(self.table_port.currentItem().text(), 9600)
            return
        ser.close()
        ser = serial.Serial(self.table_port.currentItem().text(), 9600)

    def sendtest(self):
        if type(ser) == int:
            return
        op = 'f'
        op = op.encode('utf-8')
        ser.write(op)
        
    

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
    
    def func_btn_stop(self):
        if(self.btn_autopilot.isChecked()):
            self.btn_autopilot.toggle()
            self.btn_manualpilot.toggle()
            self.btn_forward.setEnabled(True)
            self.btn_backward.setEnabled(True)
            self.btn_left.setEnabled(True)
            self.btn_right.setEnabled(True)
        #Send Emergency Stop Signal
    

    def stream_start(self):
        self.web_stream.load(QUrl("192.168.0.10:8090/?action=stream"))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindow = WindowClass()
    myWindow.show()
    app.exec_()

