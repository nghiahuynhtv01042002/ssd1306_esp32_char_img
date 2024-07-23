import cv2
import numpy as np

def resize_and_convert_to_bitmap(image_path):
    # Load image
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

    # Resize image to 128x64
    resized_img = cv2.resize(img, (128, 64), interpolation=cv2.INTER_AREA)

    # Convert to binary (black and white)
    _, binary_img = cv2.threshold(resized_img, 128, 255, cv2.THRESH_BINARY)

    # Create a bitmap (1-bit per pixel)
    bitmap = []
    for y in range(0, 64, 8):
        for x in range(128):
            byte = 0
            for bit in range(8):
                if binary_img[y + bit, x] == 255:
                    byte |= (1 << bit)
            bitmap.append(byte)
    
    return bitmap

def save_bitmap_as_c_array(bitmap, output_file):
    with open(output_file, 'w') as f:
        # f.write("const uint8_t bitmap[{}] = {{\n".format(len(bitmap)))
        f.write("const char bitmap[{}] = {{\n".format(len(bitmap)))

        for i, byte in enumerate(bitmap):
            if i % 16 == 0:
                f.write("    ")
            f.write("0x{:02X}".format(byte))
            if i < len(bitmap) - 1:
                f.write(", ")
            if (i + 1) % 16 == 0:
                f.write("\n")
        f.write("\n};\n")

# Example usage
image_path = 'esplogo.png'
output_file = 'bitmap2.c'
bitmap = resize_and_convert_to_bitmap(image_path)
save_bitmap_as_c_array(bitmap, output_file)
