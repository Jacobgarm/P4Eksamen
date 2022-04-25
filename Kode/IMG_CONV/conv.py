from PIL import Image

with Image.open(input('Enter filename: ')) as img:
    width = int(input('Width: '))
    height = int(input('Height: '))
    img.thumbnail((width,height))
    bwimg = img.convert('1')
    bites = bytes(bwimg.getdata())
    print(width.to_bytes(1, 'little'))
    bites = width.to_bytes(1, 'little') + height.to_bytes(1, 'little') + bites
    print(bites)
    bwimg.save('bw.png', 'png')
    f = open('bytes.bwb', 'wb')
    f.write(bites)
    f.close()