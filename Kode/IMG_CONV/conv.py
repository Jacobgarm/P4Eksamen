from PIL import Image

mode = 'L' # 1 for B/W, L for grayscale

def diff(img):
    print(img.height)
    edgeIm =Image.new('1', (img.width-1, img.height-1))
    pixels = img.load()
    for i in range(0, img.width-1):
        for j in range(0, img.height-1):
            #if len(set(pixels[i+x,j+y] > 100 for x in range(0,2) for y in range(0,2))) == 1:
            vals = [pixels[i+x,j+y] for x in range(0,2) for y in range(0,2)]
            if max(vals) - min(vals) < 20:
                edgeIm.putpixel((i,j), 1)
            else:
                edgeIm.putpixel((i,j), 0)
    edgeIm.show()
    edgeIm.save('diff.png','png')

with Image.open(input('Enter filename: ') or "rick.png") as img:
    width = int(input('Width: '))
    height = int(input('Height: '))
    img.thumbnail((width,height))
    bwimg = img.convert(mode)
    diff(bwimg)
    bites = bytes(bwimg.getdata())
    print(width.to_bytes(1, 'little'))
    bites = bwimg.width.to_bytes(1, 'little') + bwimg.height.to_bytes(1, 'little') + bites
    print(bites)
    bwimg.save('bw.png', 'png')
    f = open('bytes.bwb', 'wb')
    f.write(bites)
    f.close()


