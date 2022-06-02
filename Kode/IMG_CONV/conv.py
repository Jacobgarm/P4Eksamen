from PIL import Image

mode = 'L' # 1 for B/W, L for grayscale
edge = True # Whether or not to make an edge colored version

def diff(img):
    # Make a new image, 1 pixel smaller, for edge coloring
    edgeIm =Image.new('1', (img.width-1, img.height-1))
    pixels = img.load()
    for i in range(0, img.width-1):
        for j in range(0, img.height-1):
            #Get the value of for pixels around a corner
            vals = [pixels[i+x,j+y] for x in range(0,2) for y in range(0,2)]
            # If the lightest and darkest pixels differ by more than 40, it is an edge
            if max(vals) - min(vals) < 40:
                edgeIm.putpixel((i,j), 1)
            else:
                edgeIm.putpixel((i,j), 0)
    edgeIm.save('diff.png','png')

#Open file and get inputs
with Image.open(input('Enter filename: ') or "rick.png") as img:
    print(f"W: {img.width}  H: {img.height}")
    width = int(input('Width: '))
    height = int(input('Height: '))
    #Convert to smaller size
    img.thumbnail((width,height))
    #Convert to image mode
    bwimg = img.convert(mode)
    #Make an edge version
    if edge:
        diff(bwimg)
    #Get the bytes for the image
    bites = bytes(bwimg.getdata())
    #Add header bytes with height and width
    bites = bwimg.width.to_bytes(1, 'little') + bwimg.height.to_bytes(1, 'little') + bites
    #Save to png
    bwimg.save('bw.png', 'png')
    #Save to bwb
    f = open('bytes.bwb', 'wb')
    f.write(bites)
    f.close()


