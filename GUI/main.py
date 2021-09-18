# This Python file uses the following encoding: utf-8
import sys
import os
import io
import PyQt5
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
import time
import serial
import form


class MainWindow(QMainWindow, form.Ui_MainWindow):
    def __init__(self):
        super(self.__class__, self).__init__()
        self.setupUi(self)
        self.url = QUrl('file:///home/pi/Desktop/NewFolder4/map.html')
        self.map.clicked.connect(self.OpenMap)
        self.ledgreen = LedIndicator()
        self.ledred = LedIndicator()
        self.ledyellow = LedIndicator()
        self.ledred.on_color_1 = QColor(255, 0, 0)
        self.ledred.on_color_2 = QColor(192, 0, 0)
        self.ledred.off_color_1 = QColor(28, 0, 0)
        self.ledred.off_color_2 = QColor(156, 0, 0)
        self.ledyellow.on_color_1 = QColor(255, 255, 0)
        self.ledyellow.on_color_2 = QColor(192, 192, 0)
        self.ledyellow.off_color_1 = QColor(28, 28, 0)
        self.ledyellow.off_color_2 = QColor(156, 156, 0)
        self.trafficlights.addWidget(self.ledred)
        self.trafficlights.addWidget(self.ledyellow)
        self.trafficlights.addWidget(self.ledgreen)
        self.ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=2)
        self.timer = QTimer()
        self.timer.start(1000)
        self.timer.timeout.connect(self.Traffic)


    def OpenMap(self):
        QDesktopServices.openUrl(self.url)


    def Traffic(self):
        if (self.ser.in_waiting > 0):
            self.data = self.ser.readline().decode('utf-8').rstrip()
            self.x = self.data.split()
            self.intersection.setText(self.x[0])
            self.distance.setText(self.x[1])
            self.time.setText(self.x[3])
            if (self.x[2] == "Green"):
                self.ledgreen.setChecked(True)
                self.ledyellow.setChecked(False)
                self.ledred.setChecked(False)
            elif (self.x[2] == "Yellow"):
                self.ledgreen.setChecked(False)
                self.ledyellow.setChecked(True)
                self.ledred.setChecked(False)
            else:
                self.ledgreen.setChecked(False)
                self.ledyellow.setChecked(False)
                self.ledred.setChecked(True)
            #self.ser.flush()
            #self.timer.start(1000)


class LedIndicator(QAbstractButton):
    scaledSize = 1000.0
    def __init__(self, parent=None):
        QAbstractButton.__init__(self, parent)
        self.setMinimumSize(120, 120)
        self.setCheckable(True)
        self.setDisabled(True)
        # Green
        self.on_color_1 = QColor(0, 255, 0)
        self.on_color_2 = QColor(0, 192, 0)
        self.off_color_1 = QColor(0, 28, 0)
        self.off_color_2 = QColor(0, 156, 0)

    def resizeEvent(self, QResizeEvent):
        self.update()

    def paintEvent(self, QPaintEvent):
        realSize = min(self.width(), self.height())
        painter = QPainter(self)
        pen = QPen(Qt.black)
        pen.setWidth(1)
        painter.setRenderHint(QPainter.Antialiasing)
        painter.translate(self.width() / 2, self.height() / 2)
        painter.scale(realSize / self.scaledSize, realSize / self.scaledSize)
        gradient = QRadialGradient(QPointF(-500, -500), 1500, QPointF(-500, -500))
        gradient.setColorAt(0, QColor(224, 224, 224))
        gradient.setColorAt(1, QColor(28, 28, 28))
        painter.setPen(pen)
        painter.setBrush(QBrush(gradient))
        painter.drawEllipse(QPointF(0, 0), 500, 500)
        gradient = QRadialGradient(QPointF(500, 500), 1500, QPointF(500, 500))
        gradient.setColorAt(0, QColor(224, 224, 224))
        gradient.setColorAt(1, QColor(28, 28, 28))
        painter.setPen(pen)
        painter.setBrush(QBrush(gradient))
        painter.drawEllipse(QPointF(0, 0), 450, 450)
        painter.setPen(pen)
        if self.isChecked():
            gradient = QRadialGradient(QPointF(-500, -500), 1500, QPointF(-500, -500))
            gradient.setColorAt(0, self.on_color_1)
            gradient.setColorAt(1, self.on_color_2)
        else:
            gradient = QRadialGradient(QPointF(500, 500), 1500, QPointF(500, 500))
            gradient.setColorAt(0, self.off_color_1)
            gradient.setColorAt(1, self.off_color_2)
        painter.setBrush(gradient)
        painter.drawEllipse(QPointF(0, 0), 400, 400)
    @pyqtProperty(QColor)
    def onColor1(self):
        return self.on_color_1
    @onColor1.setter
    def onColor1(self, color):
        self.on_color_1 = color
    @pyqtProperty(QColor)
    def onColor2(self):
        return self.on_color_2
    @onColor2.setter
    def onColor2(self, color):
        self.on_color_2 = color
    @pyqtProperty(QColor)
    def offColor1(self):
        return self.off_color_1
    @offColor1.setter
    def offColor1(self, color):
        self.off_color_1 = color
    @pyqtProperty(QColor)
    def offColor2(self):
        return self.off_color_2
    @offColor2.setter
    def offColor2(self, color):
        self.off_color_2 = color



if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = MainWindow()
    widget.show()
    sys.exit(app.exec_())
