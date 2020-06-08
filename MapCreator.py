from PIL import Image

filename = input('Inserire nome file(no estensione): ')
im = Image.open(filename+".png")
file = open(filename+".ts", "w+")
pix = im.load()
x = int(im.width)
y = int(im.height)
i=0
j=0

blackt = (0, 0, 0, 255)
whitet = (255, 255, 255, 255)
spawnt = (255, 0, 0, 255)
loadt = (0, 0, 255, 255)
enemyt = (0, 255, 255, 255)
finalt = (0, 255, 0, 255)
treasuret = (255, 255, 0, 255)
black = (0, 0, 0)
white = (255, 255, 255)
spawn = (255, 0, 0)
load = (0, 0, 255)
enemy = (0, 255, 255)
final = (0, 255, 0)
treasure = (255, 255, 0)

for j in range(y):
    for i in range(x):
        if pix[i, j] == blackt | black:
            file.write('*')
        elif pix[i, j] == whitet | white:
            file.write('0')
        elif pix[i, j] == spawnt | spawn:
            file.write('S')
        elif pix[i, j] == loadt | load:
            file.write('L')
        elif pix[i, j] == finalt | final:
            file.write('F')
        elif pix[i, j] == enemyt | enemy:
            file.write('E')
        elif pix[i, j] == treasuret | treasure:
            file.write('T')
        else:
            file.write('?')
    file.write('\n')

