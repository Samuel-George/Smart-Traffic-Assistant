import time

def traffic(status):
    a_file = open("traffic.txt", "w")
    a_file.truncate()
    a_file.write(status + ' light')
    a_file.close()


stop_light = 1

while True:
    #x = input("Enter value: ")
    if stop_light == 30:
        stop_light = 0
    elif stop_light < 10:
        traffic('Green')
        stop_light += 1
        time.sleep(1)
    elif stop_light < 20:
        traffic('Yellow')
        stop_light += 1
        time.sleep(1)
    elif stop_light < 30:
        traffic("Red")
        stop_light += 1
        time.sleep(1)
    else:
        stop_light = 0