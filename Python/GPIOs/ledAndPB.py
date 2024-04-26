import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)

button_pin = 11
led_pin = 18

GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(led_pin, GPIO.OUT)

try:
    while True:
        if GPIO.input(button_pin) == GPIO.LOW:
            time.sleep(0.5)
            if GPIO.input(button_pin) == GPIO.LOW:
                GPIO.output(led_pin, GPIO.HIGH)
        else:
            GPIO.output(led_pin, GPIO.LOW)
except KeyboardInterrupt:
    GPIO.cleanup()

