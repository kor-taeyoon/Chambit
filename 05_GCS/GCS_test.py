import sys
import urllib.request
import time
import threading
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
lat = 37.619583
lnt = 127.058854
zoom = 16
ser = 0

class WindowClass(QMainWindow, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        
        #controlling group
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
        
        self.btn_gps_refresh.pressed.connect(self.func_btn_gps_refresh)
        self.btn_gps_refresh.setCheckable(True)
        self.btn_gps_up.pressed.connect(self.func_btn_gps_up)
        self.btn_gps_down.pressed.connect(self.func_btn_gps_down)
        self.btn_gps_left.pressed.connect(self.func_btn_gps_left)
        self.btn_gps_right.pressed.connect(self.func_btn_gps_right)

        # tmp for develop
        self.temp_send.pressed.connect(self.sendtest)

        # serial port table
        self.btn_port_refresher.pressed.connect(self.port_refresh)
        self.table_port.cellDoubleClicked.connect(self.connect_test)
        self.table_port.setEditTriggers(QAbstractItemView.NoEditTriggers)

        # webviews
        self.btn_stream.pressed.connect(self.web_stream_start)

        self.web_gps_refresh()


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
            self.btn_autopilot.toggle()
            return
        self.btn_manualpilot.toggle()
        self.btn_forward.setEnabled(False)
        self.btn_backward.setEnabled(False)
        self.btn_left.setEnabled(False)
        self.btn_right.setEnabled(False)

    def func_btn_manualpilot(self):
        if(self.btn_manualpilot.isChecked()):
            self.btn_manualpilot.toggle()
            return
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




    def func_btn_gps_refresh(self):
        if(self.btn_gps_refresh.isChecked()):
            self.btn_gps_up.setEnabled(True)
            self.btn_gps_down.setEnabled(True)
            self.btn_gps_left.setEnabled(True)
            self.btn_gps_right.setEnabled(True)
        else:
            self.btn_gps_up.setEnabled(False)
            self.btn_gps_down.setEnabled(False)
            self.btn_gps_left.setEnabled(False)
            self.btn_gps_right.setEnabled(False)


    def func_btn_gps_up(self):
        global lat
        print("forward go")
        lat+=0.001
        self.web_gps_refresh()

    def func_btn_gps_down(self):
        global lat
        print("backward go")
        lat-=0.001
        self.web_gps_refresh()

    def func_btn_gps_left(self):
        global lnt
        print("left go")
        lnt-=0.001
        self.web_gps_refresh()
    
    def func_btn_gps_right(self):
        global lnt
        print("right go")
        lnt+=0.001
        self.web_gps_refresh()
        





    def web_gps_refresh(self):
        global lat, lnt, zoom
        urlString = "https://maps.googleapis.com/maps/api/staticmap?center="+str(lat)+","+str(lnt)+"&zoom="+str(zoom)+"&size=640x470&scale=1&maptype=hybrid&key=AIzaSyABk_xoTQbteDX7TmSvQD4zYcoQGXFNPIs"
        imageFromWeb = urllib.request.urlopen(urlString).read()
        self.qPixmapWebVar = QPixmap()
        self.qPixmapWebVar.loadFromData(imageFromWeb)
        self.qPixmapWebVar = self.qPixmapWebVar.scaledToWidth(640)
        self.image_gps.setPixmap(self.qPixmapWebVar)

    def web_gps_refresh_loop(self):
        global auto, lat, lnt, zoom
        while(1):
            if self.btn_gps_refresh.isChecked():
                self.web_gps_refresh()
                lat+=0.0002
                lnt+=0.0002
                time.sleep(1)


    def web_stream_start(self):
        self.web_stream.load(QUrl("192.168.0.25:8090/?action=stream"))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindow = WindowClass()
    myWindow.show()
    thread = threading.Thread(target=myWindow.web_gps_refresh_loop, daemon=True)
    thread.start()
    app.exec_()


