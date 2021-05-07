import time

import RPi.GPIO as GPIO

#
# This scripts tests the LEDs and the button.
#
# require modules
#  - python-dev + python-rpi.gpio (apt)
#    or for development fakeRPiGPIO (pip)
#

# Default settings

BLUE_LED = 35  # GPIO 19
RED_LED = 38  # GPIO 20
YELLOW_LED = 36  # GPIO 16
GREEN_LED = 31  # GPIO 06
INPUT_BUTTON = 37  # GPIO 26

BOOT_INTERVAL = 2  # in seconds
TEST_INTERVAL = 0.5  # in seconds

# Classes


# Functions


# Starting program
print "LEDTest started - for stopping please press CRTL-c"
print " - BLUE LED:", BLUE_LED
print " - RED LED:", RED_LED
print " - YELLOW LED:", YELLOW_LED
print " - GREEN LED:", GREEN_LED
print " - INPUT BUTTON:", INPUT_BUTTON

try:
    # Setup GPIO layout
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(BLUE_LED, GPIO.OUT)  # as output
    GPIO.setup(RED_LED, GPIO.OUT)  # as output
    GPIO.setup(YELLOW_LED, GPIO.OUT)  # as output
    GPIO.setup(GREEN_LED, GPIO.OUT)  # as output
    GPIO.setup(INPUT_BUTTON, GPIO.IN)  # as input

    # Activate on booting
    GPIO.output(BLUE_LED, GPIO.HIGH)
    GPIO.output(RED_LED, GPIO.HIGH)
    GPIO.output(YELLOW_LED, GPIO.HIGH)
    GPIO.output(GREEN_LED, GPIO.HIGH)
    time.sleep(BOOT_INTERVAL)

    state = False
    leds = [BLUE_LED, RED_LED, YELLOW_LED, GREEN_LED]
    names = ["BLUE_LED", "RED_LED", "YELLOW_LED", "GREEN_LED"]

    GPIO.output(BLUE_LED, GPIO.LOW)
    GPIO.output(RED_LED, GPIO.LOW)
    GPIO.output(YELLOW_LED, GPIO.LOW)
    GPIO.output(GREEN_LED, GPIO.LOW)

    i = 0
    length = len(leds)
    # Running test loop
    while True:
        # Toggle LEDs

        led = leds[i]
        name = names[i]

        if state:
            print "Turn off LED ", name
            GPIO.output(led, GPIO.LOW)
            state = False

            i = i + 1
            if i >= length:
                i = 0

        else:
            print "Turn on LED ", name
            GPIO.output(led, GPIO.HIGH)
            state = True

        # print "Input is", GPIO.input(INPUT_BUTTON)
        if GPIO.input(INPUT_BUTTON) == GPIO.HIGH:
            print "Button on PIN ", INPUT_BUTTON, " pressed"

        # wait for next update
        time.sleep(TEST_INTERVAL)

except KeyboardInterrupt:
    print "Strg-C called - LEDTest stopping"
    # Release GPIO ports
    GPIO.cleanup()
