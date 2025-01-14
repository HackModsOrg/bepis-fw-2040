from machine import I2C, Pin, PWM, ADC
from time import sleep

i2c = I2C(1, sda=Pin(18), scl=Pin(23))
print(i2c.scan())
print([hex(a) for a in i2c.scan()])

"""
print(list(map(hex, i2c.readfrom_mem(0x22, 0, 0x1f))))
i2c.writeto_mem(0x22, 1, bytes([0]))
print(list(map(hex, i2c.readfrom_mem(0x22, 0, 0x1f))))
"""

pp = Pin(15, Pin.OUT, None)
#pp.value(True)
#pp.value(False)

erst = Pin(17, Pin.OUT)
erst.off()
sleep(0.1)
erst.on()

"""
i2c.writeto_mem(0x22, 0x00, bytes([0xf8])) #iodira
i2c.writeto_mem(0x22, 0x14, bytes([0x4])) #olata - set usb mux to default, set fusb mux to default, disable charging
sleep(0.5)
i2c.writeto_mem(0x22, 0x14, bytes([0x0])) #olata - re-enable charging
"""

p = PWM(pp)
p.freq(2048)

p.duty_u16(512)
sleep(1)
p.duty_u16(0)

bl = PWM(Pin(24))
bl2 = PWM(Pin(25))

bl.freq(1000)
bl2.freq(1000)

bl.duty_u16(65536//2)
bl2.duty_u16(65536//2)

vb = ADC(26)

def get_vbat():
    val = vb.read_u16()
    return val/19859*2

print(get_vbat())

def test_shorts():
    r = [14, 13, 12, 11, 10, 9, 8]
    c = [1, 2, 3, 7, 6, 5, 4]
    o = [18, 23, 22]
    #o = [18, 23, 22, 28, 29]
    p = r+c+o
    pins = [Pin(x, Pin.IN, Pin.PULL_UP) for x in p]

    r_n = ["ROW"+str(i) for i in range(len(r))]
    c_n = ["COL"+str(i) for i in range(len(c))]
    o_n = ["TP_SDA", "TP_SCL", "TP_MOTION"]
    #o_n = ["TP_SDA", "TP_SCL", "TP_MOTION", "PI_SDA", "PI_SCL"]
    p_n = r_n + c_n + o_n

    while True:
        for _ in range(1000000):
            shorted = []
            for i, pin1 in enumerate(pins):
                pin1.init(Pin.OUT)
                pin1.value(False)
                for j, pin2 in enumerate(pins):
                    if i == j:
                        continue
                    if not pin2.value():
                        shorted.append((i, j))
                pin1.init(Pin.IN, Pin.PULL_UP)
            if shorted:
                # see if everything is shorted to everything hehe
                print(_, ",")
                if len(shorted) < len(p)*(len(p)-1) // 2:
                    # just a few shorted, gotta list those
                    for i, j in shorted:
                        print("n: {} ({}) shorted to {} ({})".format(p_n[i], p[i], p_n[j], p[j]))
                else:
                    # most of them shorted, we list exceptions instead
                    l = []
                    for i, j in shorted: # unsophisticated flattening
                        if i not in l: l.append(i)
                        if j not in l: l.append(j)
                    for i, pin in enumerate(p):
                        if i not in l:
                            print("m: {} ({}) not connected".format(p_n[i], pin))
                    #print(shorted)
            sleep(0.05)



#test_shorts()
