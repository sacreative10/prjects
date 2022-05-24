import os



























































from time import sleep
import time
from pynput.keyboard import Controller, Key
import pyautogui
import pyte

keyboard = Controller()


sleep(2)

# simulate alt+tab
pyautogui.hotkey("alt", "tab")

sleep(2)

starttime = time.process_time()
counter = 0
for i in range(1, 1338):
    # ctrl+v
    keyboard.press("v")
    sleep(0.1)
    # press enter
keyboard.press(Key.enter)
