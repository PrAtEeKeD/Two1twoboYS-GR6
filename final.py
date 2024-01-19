
import PyPDF2
from PIL import Image
import io

pdf_name = input("Enter the name of the PDF to be converted: ")
pdf_reader = PyPDF2.PdfReader(pdf_name)

# Info data of the PDF
info_data = pdf_reader.metadata
print("The Information about the PDF:\n", info_data)

# The number of pages in the PDF
length = len(pdf_reader.pages)
print("The number of pages in the PDF:", length)

# Layout of the PDF
layout = pdf_reader.page_layout
print("The layout of the PDF is:", layout)

# Extracting text from a specific page
num_in = input("Enter the page number to be accessed: ")
num = int(num_in)
page = pdf_reader.pages[num - 1]  # Adjusting for 0-based index
text = page.extract_text()
print(f"Text from page {num}:\n{text}")

# Extracting text from all pages
all_text = ""
for page_number in range(pdf_reader.numPages):
    page = pdf_reader.getPage(page_number)
    all_text += page.extractText()

# Extracting images from the PDF
output_folder = 'output_folder'  # Replace with the desired output folder
for page_number in range(pdf_reader.numPages):
    page = pdf_reader.getPage(page_number)
    image_list = page.getImageList()

    for img_index, img in enumerate(image_list):
        xref = img[0]
        base_image = pdf_reader.extractImage(xref)
        image_bytes = base_image["image"]
        image = Image.open(io.BytesIO(image_bytes))
        image.save(f"{output_folder}/page{page_number + 1}_img{img_index + 1}.png", "PNG")

