import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)

led_pin = 32

GPIO.setup(led_pin, GPIO.OUT)

pwm_led = GPIO.PWM(led_pin, 100)  # 100 Hz frequency
pwm_led.start(0)

try:
    while True:
        for i in range(0, 101, 5):
            pwm_led.ChangeDutyCycle(i)
            time.sleep(0.1)
        for i in range(100, -1, -5):
            pwm_led.ChangeDutyCycle(i)
            time.sleep(0.1)
except KeyboardInterrupt:
    pwm_led.stop()
    GPIO.cleanup()

